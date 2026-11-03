// DIAG R14. Prints the fault and the top frames to stderr on a fatal signal. Steam's crash handler and the
// Frida gadget swallow some crashes without writing an .ips, so this is the only record.
//
// R16a. After the report the process must exit. Until R16 the handler restored SIG_DFL and returned, so the
// faulting instruction ran again and took the default action. In the Phase 6 sessions that froze the game: no
// thread logged anything after the report, and the player had to close it from the launcher. The default action hands the
// crash to the process crash reporters (Steam's handler, ReportCrash), which suspend the process while they dump it.
// The report is already on stderr, so the handler now ends the process itself with _exit(128 + signal), no crash
// report. CODEWARE_R16A_CRASHMODE=raise switches back to "SIG_DFL and re-raise" (used once to measure the freeze).
//
// Frames come from the frame-pointer chain (Apple arm64 keeps it). Each address prints as image+offset.
// The handler uses snprintf and write only. It is a diagnostic for a process that is already dying.

#include "MacR13.hpp"
#include "MacR15.hpp"

#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mach-o/dyld.h>
#include <mach-o/loader.h>
#include <mach/mach.h>
#include <mach/mach_vm.h>
#include <pthread.h>
#include <sys/ucontext.h>
#include <unistd.h>

namespace
{
// 0 = _exit after the report (default), 1 = restore SIG_DFL and re-raise. Set once in InstallCrashDiag.
volatile sig_atomic_t g_raiseMode = 0;

void Emit(const char* aText)
{
    const auto len = std::strlen(aText);
    (void)!write(STDERR_FILENO, aText, len);
}

// Finds the image that holds aAddress. Prints "name+0xoff" into aOut.
void Describe(uintptr_t aAddress, char* aOut, size_t aSize)
{
    const uint32_t count = _dyld_image_count();
    for (uint32_t i = 0; i < count; ++i)
    {
        const auto* header = reinterpret_cast<const mach_header_64*>(_dyld_get_image_header(i));
        if (!header)
        {
            continue;
        }
        const intptr_t slide = _dyld_get_image_vmaddr_slide(i);
        auto* cmd = reinterpret_cast<const load_command*>(header + 1);
        for (uint32_t c = 0; c < header->ncmds; ++c)
        {
            if (cmd->cmd == LC_SEGMENT_64)
            {
                const auto* seg = reinterpret_cast<const segment_command_64*>(cmd);
                const auto start = static_cast<uintptr_t>(seg->vmaddr) + static_cast<uintptr_t>(slide);
                if (aAddress >= start && aAddress < start + seg->vmsize)
                {
                    const char* name = _dyld_get_image_name(i);
                    const char* base = name ? std::strrchr(name, '/') : nullptr;
                    base = base ? base + 1 : (name ? name : "?");
                    std::snprintf(aOut, aSize, "%s+0x%lx", base,
                                  static_cast<unsigned long>(aAddress - (reinterpret_cast<uintptr_t>(header))));
                    return;
                }
            }
            cmd = reinterpret_cast<const load_command*>(reinterpret_cast<const uint8_t*>(cmd) + cmd->cmdsize);
        }
    }
    std::snprintf(aOut, aSize, "?");
}

// DIAG R79. The reports below read memory through the kernel, so a bad pointer gives an error instead of a second fault.
bool SafeRead(uintptr_t aAddress, void* aOut, size_t aSize)
{
    mach_vm_size_t got = 0;
    const auto kr = mach_vm_read_overwrite(mach_task_self(), aAddress, aSize, reinterpret_cast<mach_vm_address_t>(aOut), &got);
    return kr == KERN_SUCCESS && got == aSize;
}

template<typename T>
T Load(uintptr_t aAddress, bool& aOk)
{
    T value{};
    if (!SafeRead(aAddress, &value, sizeof(T)))
    {
        aOk = false;
    }
    return value;
}

// The game's image header, the base the reports print offsets from.
uintptr_t GameBase()
{
    const uint32_t count = _dyld_image_count();
    for (uint32_t i = 0; i < count; ++i)
    {
        const char* name = _dyld_get_image_name(i);
        const char* base = name ? std::strrchr(name, '/') : nullptr;
        if (base && std::strcmp(base + 1, "Cyberpunk2077") == 0)
        {
            return reinterpret_cast<uintptr_t>(_dyld_get_image_header(i));
        }
    }
    return 0;
}

// Prints aSize bytes at aAddress, 32 per line, each line labelled with its offset from aOrigin.
void HexDump(const char* aLabel, uintptr_t aAddress, size_t aSize, uintptr_t aOrigin)
{
    char line[256];
    uint8_t bytes[32];
    for (size_t done = 0; done < aSize; done += sizeof(bytes))
    {
        const size_t n = (aSize - done) < sizeof(bytes) ? (aSize - done) : sizeof(bytes);
        int len = std::snprintf(line, sizeof(line), "[crash] hex %s +0x%lx:", aLabel,
                                static_cast<unsigned long>(aAddress + done - aOrigin));
        if (!SafeRead(aAddress + done, bytes, n))
        {
            std::snprintf(line + len, sizeof(line) - len, " (unreadable)\n");
            Emit(line);
            return;
        }
        for (size_t i = 0; i < n; ++i)
        {
            len += std::snprintf(line + len, sizeof(line) - len, " %02x", bytes[i]);
        }
        std::snprintf(line + len, sizeof(line) - len, "\n");
        Emit(line);
    }
}

void DumpRegisters(const arm_thread_state64_t& aState)
{
    char line[256];
    for (int r = 0; r < 29; r += 4)
    {
        int len = std::snprintf(line, sizeof(line), "[crash] regs");
        for (int k = r; k < r + 4 && k < 29; ++k)
        {
            len += std::snprintf(line + len, sizeof(line) - len, " x%d=0x%llx", k,
                                 static_cast<unsigned long long>(aState.__x[k]));
        }
        std::snprintf(line + len, sizeof(line) - len, "\n");
        Emit(line);
    }
}

// DIAG R79. The new-SDK crash stops in the game's DynArray grow trap (+0x28878) because worldInstancedMeshNode's Serialize
// (+0x1b1d9a8) read a bad count from the package stream while the extractor (+0x120aff4) loaded a resource. This names the resource and
// the object and dumps the bytes the stream was reading, to compare them with the file. Game 2.5 Mac build 5814786:
//   DynArray_Realloc (+0x28674) saves its caller's x19..x26 at fp-0x08..fp-0x40.
//   Serialize keeps the stream in x19 and the node in x20 (lists at +0x60, +0x70, +0x80, version byte +0x90) and saves its caller's
//   x19..x22 at fp-0x08..fp-0x20.
//   The extractor (returns into it at +0x120b1bc): x23 the extractor (objects +0x38, count +0x44), x27 the object index, x28 the export
//   entry (0x18 bytes, data offset at +0xc), x21 the ResourceSerializerRequest (path at +0x28); sp+0x8 the base offset and sp+0x18 the
//   package header (export table at +0x30), fp = sp+0x70; it saves the job's x20 (the ResourceSerializerContext) at fp-0x10.
//   The stream is the game's memory reader (vtable +0x78fd490): data +0x20, size +0x28, position +0x2c.
void DumpDynArrayGrowTrap(const arm_thread_state64_t& aState)
{
    const uintptr_t game = GameBase();
    const uintptr_t pc = static_cast<uintptr_t>(arm_thread_state64_get_pc(aState));
    if (!game || (pc != game + 0x28878 && pc != game + 0x2884c))
    {
        return;
    }

    char line[512];
    bool ok = true;
    const uintptr_t fpR = static_cast<uintptr_t>(arm_thread_state64_get_fp(aState));
    uint64_t saved[8]; // the caller's x19..x26
    for (int i = 0; i < 8; ++i)
    {
        saved[i] = Load<uint64_t>(fpR - 8 * (i + 1), ok);
    }
    const uintptr_t fpS = Load<uintptr_t>(fpR, ok);
    const uintptr_t retS = Load<uintptr_t>(fpR + 8, ok);
    std::snprintf(line, sizeof(line),
                  "[crash] grow: caller Cyberpunk2077+0x%lx x19=0x%llx x20=0x%llx x21=0x%llx x22=0x%llx x23=0x%llx x24=0x%llx "
                  "x25=0x%llx x26=0x%llx%s\n",
                  static_cast<unsigned long>(retS - game), static_cast<unsigned long long>(saved[0]),
                  static_cast<unsigned long long>(saved[1]), static_cast<unsigned long long>(saved[2]),
                  static_cast<unsigned long long>(saved[3]), static_cast<unsigned long long>(saved[4]),
                  static_cast<unsigned long long>(saved[5]), static_cast<unsigned long long>(saved[6]),
                  static_cast<unsigned long long>(saved[7]), ok ? "" : " (some unreadable)");
    Emit(line);
    if (!ok || retS < game + 0x1b1d9a8 || retS >= game + 0x1b1dc48)
    {
        return;
    }

    const uintptr_t stream = saved[0];
    const uintptr_t node = saved[1];
    const uintptr_t extractor = saved[4];

    const uintptr_t streamVt = Load<uintptr_t>(stream, ok);
    const uint8_t streamFlags = Load<uint8_t>(stream + 0x8, ok);
    const uintptr_t streamCtx = Load<uintptr_t>(stream + 0x10, ok);
    const uintptr_t data = Load<uintptr_t>(stream + 0x20, ok);
    const uint32_t size = Load<uint32_t>(stream + 0x28, ok);
    const uint32_t pos = Load<uint32_t>(stream + 0x2c, ok);
    const uintptr_t streamExtra = Load<uintptr_t>(stream + 0x30, ok);
    std::snprintf(line, sizeof(line),
                  "[crash] grow: stream %p vt=Cyberpunk2077+0x%lx%s flags=0x%x ctx=%p data=%p size=%u pos=%u extra=%p%s\n",
                  reinterpret_cast<void*>(stream), static_cast<unsigned long>(streamVt - game),
                  streamVt == game + 0x78fd490 ? " (memory reader)" : " (NOT the memory reader)", streamFlags,
                  reinterpret_cast<void*>(streamCtx), reinterpret_cast<void*>(data), size, pos,
                  reinterpret_cast<void*>(streamExtra), ok ? "" : " (some unreadable)");
    Emit(line);

    struct ListFields
    {
        uint64_t ptr;
        uint32_t capacity;
        uint32_t size;
    } lists[3]{};
    for (int i = 0; i < 3; ++i)
    {
        SafeRead(node + 0x60 + 0x10 * i, &lists[i], sizeof(ListFields));
    }
    const uintptr_t nodeVt = Load<uintptr_t>(node, ok);
    const uint8_t version = Load<uint8_t>(node + 0x90, ok);
    std::snprintf(line, sizeof(line),
                  "[crash] grow: node %p vt=Cyberpunk2077+0x%lx version=%u list60 %p cap=%u size=%u list70 %p cap=%u size=%u "
                  "list80 %p cap=%u size=%u, count read 0x%x\n",
                  reinterpret_cast<void*>(node), static_cast<unsigned long>(nodeVt - game), version,
                  reinterpret_cast<void*>(lists[0].ptr), lists[0].capacity, lists[0].size,
                  reinterpret_cast<void*>(lists[1].ptr), lists[1].capacity, lists[1].size,
                  reinterpret_cast<void*>(lists[2].ptr), lists[2].capacity, lists[2].size,
                  static_cast<unsigned>(saved[2]));
    Emit(line);

    // A list buffer inside the stream's buffer would mean that buffer was freed while it was being read.
    for (int i = 0; i < 3; ++i)
    {
        if (lists[i].ptr && lists[i].ptr + uint64_t{lists[i].capacity} * (i == 0 ? 0x30 : i == 1 ? 0x40 : 4) > data &&
            lists[i].ptr < data + size)
        {
            std::snprintf(line, sizeof(line), "[crash] grow: list%x buffer %p overlaps the stream buffer %p..%p\n", 0x60 + 0x10 * i,
                          reinterpret_cast<void*>(lists[i].ptr), reinterpret_cast<void*>(data), reinterpret_cast<void*>(data + size));
            Emit(line);
        }
    }
    HexDump("before-data", data - 64, 64, data);
    HexDump("list70-head", lists[1].ptr, lists[1].size ? 64 : 0, lists[1].ptr);
    if (lists[1].size)
    {
        HexDump("list70-tail", lists[1].ptr + uint64_t{lists[1].size} * 0x40 - 64, 64, lists[1].ptr);
    }

    const uintptr_t fpE = Load<uintptr_t>(fpS, ok);
    const uintptr_t retE = Load<uintptr_t>(fpS + 8, ok);
    if (!ok || retE != game + 0x120b1bc)
    {
        std::snprintf(line, sizeof(line), "[crash] grow: Serialize was not called by the package extractor (ret Cyberpunk2077+0x%lx)\n",
                      static_cast<unsigned long>(retE - game));
        Emit(line);
        HexDump("pos", data + (pos > 512 ? pos - 512 : 0), (pos > 512 ? 512 : pos) + 256, data);
        return;
    }

    const uintptr_t request = Load<uintptr_t>(fpS - 0x18, ok);
    const uint64_t pathHash = Load<uint64_t>(request + 0x28, ok);
    const uintptr_t context = Load<uintptr_t>(fpE - 0x10, ok);
    const uint64_t index = aState.__x[27];
    const uintptr_t entry = static_cast<uintptr_t>(aState.__x[28]);
    const uint32_t objectCount = Load<uint32_t>(extractor + 0x44, ok);
    const uintptr_t header = Load<uintptr_t>(fpE - 0x70 + 0x18, ok);
    const uint64_t baseOffset = Load<uint64_t>(fpE - 0x70 + 0x8, ok);
    const uintptr_t exports = Load<uintptr_t>(header + 0x30, ok);
    uint32_t e[6]{};
    uint32_t next[6]{};
    const bool haveEntry = SafeRead(entry, e, sizeof(e));
    const bool haveNext = index + 1 < objectCount && SafeRead(entry + 0x18, next, sizeof(next));
    std::snprintf(line, sizeof(line),
                  "[crash] grow: resource path hash 0x%016llx request %p context %p (request %s context+0x1d0, extractor %s "
                  "context+0xb0); object %llu of %u, export entry %p (%s exports %p + index * 0x18), base offset %llu\n",
                  static_cast<unsigned long long>(pathHash), reinterpret_cast<void*>(request), reinterpret_cast<void*>(context),
                  request == context + 0x1d0 ? "==" : "!=", extractor == context + 0xb0 ? "==" : "!=",
                  static_cast<unsigned long long>(index), objectCount,
                  reinterpret_cast<void*>(entry), entry == exports + index * 0x18 ? "==" : "!=", reinterpret_cast<void*>(exports),
                  static_cast<unsigned long long>(baseOffset));
    Emit(line);
    std::snprintf(line, sizeof(line), "[crash] grow: export %08x %08x %08x %08x %08x %08x, next %s %08x %08x %08x %08x %08x %08x\n",
                  e[0], e[1], e[2], e[3], e[4], e[5], haveNext ? "" : "(none)", next[0], next[1], next[2], next[3], next[4],
                  next[5]);
    Emit(line);

    // The serializer context (the job's state, with the buffers it owns), as qwords.
    for (uint32_t off = 0; off < 0x260; off += 0x20)
    {
        uint64_t q[4]{};
        const bool qok = SafeRead(context + off, q, sizeof(q));
        std::snprintf(line, sizeof(line), "[crash] grow: context+0x%03x %016llx %016llx %016llx %016llx%s\n", off,
                      static_cast<unsigned long long>(q[0]), static_cast<unsigned long long>(q[1]),
                      static_cast<unsigned long long>(q[2]), static_cast<unsigned long long>(q[3]), qok ? "" : " (unreadable)");
        Emit(line);
    }

    // The object's bytes. Offsets print from the start of the stream's buffer, so they are stream positions.
    const uint64_t start = baseOffset + e[3];
    const uint64_t end = haveNext ? baseOffset + next[3] : size;
    if (haveEntry && start <= pos && pos <= end && end <= size)
    {
        const uint64_t region = end - start;
        std::snprintf(line, sizeof(line), "[crash] grow: object bytes %llu..%llu (%llu), stream position %u\n",
                      static_cast<unsigned long long>(start), static_cast<unsigned long long>(end),
                      static_cast<unsigned long long>(region), pos);
        Emit(line);
        if (region <= 16384)
        {
            HexDump("obj", data + start, region, data);
        }
        else
        {
            HexDump("obj-head", data + start, 1024, data);
            const uint64_t from = pos - start > 1024 ? pos - 1024 : start;
            HexDump("obj-pos", data + from, (pos - from) + (end - pos > 256 ? 256 : end - pos), data);
            HexDump("obj-tail", data + end - 256, 256, data);
        }
    }
    else
    {
        std::snprintf(line, sizeof(line), "[crash] grow: object bytes %llu..%llu do not hold position %u (size %u)\n",
                      static_cast<unsigned long long>(start), static_cast<unsigned long long>(end), pos, size);
        Emit(line);
        HexDump("pos", data + (pos > 512 ? pos - 512 : 0), (pos > 512 ? 512 : pos) + 256, data);
    }
}

// DIAG R80. One loaded streaming sector, logged after deserialization (MacResourceJob, the load job hook): the sector's node setup
// buffer and, for each worldInstancedMeshNode (vtable +0x78e5130), its three lists (+0x60 / +0x70 / +0x80: pointer, capacity,
// size), the version byte (+0x90) and the first bytes of the lists. The R79 crash read past the end of an old-format (version 1)
// node of the LizziesBDs sector 0x550364e813d7a12a into a scratch buffer; this shows what that node reads on loads that do not crash.
// Node buffer at sector +0x40: setup DataBuffer (data +0x00, size +0x08), version +0x28, node handles +0x30 (entries, capacity, size).
void LogSectorNodesImpl(uintptr_t aSector, uint64_t aPathHash)
{
    const uintptr_t game = GameBase();
    char line[512];
    bool ok = true;
    const uintptr_t setupData = Load<uintptr_t>(aSector + 0x40, ok);
    const uint32_t setupSize = Load<uint32_t>(aSector + 0x48, ok);
    const uint32_t setupVersion = Load<uint32_t>(aSector + 0x40 + 0x28, ok);
    const uintptr_t nodes = Load<uintptr_t>(aSector + 0x40 + 0x30, ok);
    const uint32_t nodeCount = Load<uint32_t>(aSector + 0x40 + 0x3c, ok);
    uint64_t setupSum = 0;
    for (uint32_t off = 0; off + 8 <= setupSize && off < 0x10000; off += 8)
    {
        setupSum = setupSum * 31 + Load<uint64_t>(setupData + off, ok);
    }
    // The serializer's scratch buffer size, which is also the size below which a compressed file is decoded in the load job
    // (into the scratch buffer) instead of by the IO (into a buffer of its own size): game +0x99dc8a4 (reader +0x10eb1b4).
    const uint32_t scratch = Load<uint32_t>(game + 0x99dc8a4, ok);
    std::snprintf(line, sizeof(line), "[diag] R80 sector 0x%016llx: setups %p size %u version 0x%x sum %016llx, nodes %u, scratch %u, tails zeroed %llu%s\n",
                  static_cast<unsigned long long>(aPathHash), reinterpret_cast<void*>(setupData), setupSize, setupVersion,
                  static_cast<unsigned long long>(setupSum), nodeCount, scratch, Mac::ScratchTailsZeroed(), ok ? "" : " (some unreadable)");
    Emit(line);
    for (uint32_t i = 0; i < nodeCount && i < 256; ++i)
    {
        bool nodeOk = true;
        const uintptr_t node = Load<uintptr_t>(nodes + 0x10 * i, nodeOk);
        const uintptr_t vt = Load<uintptr_t>(node, nodeOk);
        if (!nodeOk || vt != game + 0x78e5130)
        {
            continue;
        }
        struct ListFields
        {
            uint64_t ptr;
            uint32_t capacity;
            uint32_t size;
        } lists[3]{};
        uint8_t head[3][16]{};
        for (int k = 0; k < 3; ++k)
        {
            SafeRead(node + 0x60 + 0x10 * k, &lists[k], sizeof(ListFields));
            if (lists[k].ptr && lists[k].size)
            {
                SafeRead(lists[k].ptr, head[k], sizeof(head[k]));
            }
        }
        const uint8_t version = Load<uint8_t>(node + 0x90, nodeOk);
        int len = std::snprintf(line, sizeof(line), "[diag] R80   node %u %p v%u", i, reinterpret_cast<void*>(node), version);
        for (int k = 0; k < 3; ++k)
        {
            len += std::snprintf(line + len, sizeof(line) - len, " | list%x size %u cap %u:", 0x60 + 0x10 * k, lists[k].size,
                                 lists[k].capacity);
            for (int b = 0; b < 16 && lists[k].size; ++b)
            {
                len += std::snprintf(line + len, sizeof(line) - len, " %02x", head[k][b]);
            }
        }
        std::snprintf(line + len, sizeof(line) - len, "\n");
        Emit(line);
    }
}

void Handler(int aSignal, siginfo_t* aInfo, void* aContext)
{
    // One report per process. A second fault inside the handler goes straight to the default action.
    static volatile sig_atomic_t s_entered = 0;
    if (s_entered)
    {
        std::signal(aSignal, SIG_DFL);
        if (!g_raiseMode)
        {
            _exit(128 + aSignal);
        }
        return;
    }
    s_entered = 1;

    char line[512];
    char where[160];
    auto* uc = static_cast<ucontext_t*>(aContext);
    const auto& ss = uc->uc_mcontext->__ss;
    const uintptr_t pc = static_cast<uintptr_t>(arm_thread_state64_get_pc(ss));
    const uintptr_t lr = static_cast<uintptr_t>(arm_thread_state64_get_lr(ss));
    const uintptr_t fp = static_cast<uintptr_t>(arm_thread_state64_get_fp(ss));
    const uintptr_t sp = static_cast<uintptr_t>(arm_thread_state64_get_sp(ss));

    std::snprintf(line, sizeof(line), "[crash] signal=%d code=%d addr=%p tid=%llu\n", aSignal, aInfo ? aInfo->si_code : -1,
                  aInfo ? aInfo->si_addr : nullptr, static_cast<unsigned long long>(pthread_mach_thread_np(pthread_self())));
    Emit(line);
    Describe(pc, where, sizeof(where));
    std::snprintf(line, sizeof(line), "[crash] #0 pc=0x%lx %s\n", static_cast<unsigned long>(pc), where);
    Emit(line);
    Describe(lr, where, sizeof(where));
    std::snprintf(line, sizeof(line), "[crash] #1 lr=0x%lx %s\n", static_cast<unsigned long>(lr), where);
    Emit(line);

    // Frame-pointer walk. [fp] = previous fp, [fp + 8] = return address. Stay inside this thread's stack.
    const auto self = pthread_self();
    const auto stackTop = reinterpret_cast<uintptr_t>(pthread_get_stackaddr_np(self));
    const auto stackBottom = stackTop - pthread_get_stacksize_np(self);
    uintptr_t frame = fp;
    for (int depth = 2; depth < 14; ++depth)
    {
        if (frame < stackBottom || frame + 16 > stackTop || (frame & 0xF) != 0)
        {
            break;
        }
        const auto next = *reinterpret_cast<const uintptr_t*>(frame);
        const auto ret = *reinterpret_cast<const uintptr_t*>(frame + 8);
        Describe(ret, where, sizeof(where));
        std::snprintf(line, sizeof(line), "[crash] #%d 0x%lx %s\n", depth, static_cast<unsigned long>(ret), where);
        Emit(line);
        if (next <= frame)
        {
            break;
        }
        frame = next;
    }
    std::snprintf(line, sizeof(line), "[crash] sp=0x%lx x0=0x%llx x1=0x%llx x2=0x%llx x19=0x%llx x20=0x%llx\n",
                  static_cast<unsigned long>(sp), static_cast<unsigned long long>(ss.__x[0]),
                  static_cast<unsigned long long>(ss.__x[1]), static_cast<unsigned long long>(ss.__x[2]),
                  static_cast<unsigned long long>(ss.__x[19]), static_cast<unsigned long long>(ss.__x[20]));
    Emit(line);

    // DIAG R79. Every register, then the package report when this is the DynArray grow trap. Guarded like R17 below.
    static volatile sig_atomic_t s_dumping = 0;
    if (!s_dumping)
    {
        s_dumping = 1;
        DumpRegisters(ss);
        DumpDynArrayGrowTrap(ss);
    }

    // R17. The script validator keeps the property it was checking; a fault inside the game's validator is otherwise
    // anonymous. Guarded: a second fault in here ends the process through the default action below.
    static volatile sig_atomic_t s_describing = 0;
    if (!s_describing)
    {
        s_describing = 1;
        char state[512];
        state[0] = '\0';
        Mac::DescribeLastValidatedProperty(state, sizeof(state));
        if (state[0])
        {
            std::snprintf(line, sizeof(line), "[crash] last validated property: %s\n", state);
            Emit(line);
        }
    }

    std::signal(aSignal, SIG_DFL);
    if (g_raiseMode)
    {
        // Default action: the crash goes to the crash reporters. This is the path that froze the game.
        std::raise(aSignal);
        return;
    }
    Emit("[crash] exiting now (_exit), no crash report\n");
    _exit(128 + aSignal);
}
}

void Mac::LogSectorNodes(void* aSector, unsigned long long aPathHash)
{
    LogSectorNodesImpl(reinterpret_cast<uintptr_t>(aSector), aPathHash);
}

void Mac::InstallCrashDiag()
{
    {
        const char* mode = std::getenv("CODEWARE_R16A_CRASHMODE");
        g_raiseMode = (mode && std::strcmp(mode, "raise") == 0) ? 1 : 0;
    }
    static char s_altStack[1 << 16];
    stack_t alt{};
    alt.ss_sp = s_altStack;
    alt.ss_size = sizeof(s_altStack);
    alt.ss_flags = 0;
    sigaltstack(&alt, nullptr);

    struct sigaction action{};
    action.sa_sigaction = &Handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO | SA_ONSTACK;
    for (const int sig : {SIGSEGV, SIGBUS, SIGILL, SIGTRAP, SIGABRT, SIGFPE})
    {
        sigaction(sig, &action, nullptr);
    }
}
