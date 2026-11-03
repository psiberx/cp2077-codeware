// R81. Zero a short tail after a package decoded into the resource serializer's scratch buffer.
//
// A compressed file smaller than the serializer's scratch buffer is decoded by the deserialize job (+0x1207ed4) into a pooled
// scratch buffer (the worker's free list, capacity = the scratch size at +0x99dc8a4, 1 MiB) through +0x1219c30, and the objects are
// then read with a memory stream whose size is the whole scratch buffer. A read past the end of the package therefore returns what an
// earlier package left in that buffer, where the IO path's stream (sized to the data) returns zeros. Game 2.5's worldInstancedMeshNode
// reader takes 8 bytes more than an old-format (version 1) node holds. When such a node is the last object of its package, as in the
// LizziesBDs mod sector 0x550364e813d7a12a (built for an earlier game version), those 8 bytes are the leftovers; leftover text makes it
// ask for billions of list entries and the game stops in its DynArray grow trap (+0x28878, the R79 report). On the loads that did not
// crash the leftovers were zeros, so the node got one entry in its first list and two empty lists (R80).
//
// The hook runs before the decode and zeroes up to 4 KB after the decoded size, so such reads always get the zeros a fresh buffer
// gives. It touches only scratch buffers (the capacity equals the scratch size), only KARK data (the header holds the decoded size), and
// only bytes inside [decoded size, capacity), which nothing reads as package data.

#include "MacR13.hpp"
#include "MacDiag.hpp"
#include "MacEngine.hpp"

#include "Core/Hooking/HookingAgent.hpp"

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace Red
{
// The compressed data the job decodes from (the read data holder's view at serializer context +0x60).
struct MacDecodeSource
{
    const uint8_t* data; // 00
    uint32_t size;       // 08
};
}

namespace Raw::ResourceSerializer
{
// +0x1219c30 (callers jump through the 4-byte thunk +0x1219c2c): bool(const char* aName, const MacDecodeSource* aSource,
// uint8_t* aDestination, uint32_t aCapacity). One decode of the source's format (the first 4 bytes); returns whether it worked.
constexpr auto MacJobDecode = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceSerializer_MacJobDecode,
    /* type = */ bool (*)(const char* aName, const Red::MacDecodeSource* aSource, uint8_t* aDestination, uint32_t aCapacity)>();
}

namespace
{
constexpr uint32_t KarkMagic = 0x4b52414b;     // "KARK": the archive's Kraken container, the decoded size follows the magic
constexpr uintptr_t ScratchSizeRva = 0x99dc8a4; // u32, read by +0x10eb1b4 and by the worker that allocates the buffers
// One straddling element plus the counts after it reach into the tail; a zero count ends any list, so 4 KB is ample.
constexpr uint32_t TailBytes = 4096;

std::atomic<uint64_t> s_zeroed{0};

class ScratchTailHook : public Core::HookingAgent
{
public:
    static bool Install()
    {
        const bool ok = IsHooked<Raw::ResourceSerializer::MacJobDecode>() ||
                        HookBefore<Raw::ResourceSerializer::MacJobDecode>(&OnJobDecode);
        MAC_DIAG_UNLESS(ok, "[cw] hook %s ScratchTailHook target=%p\n", ok ? "installed" : "FAILED",
                        reinterpret_cast<void*>(Raw::ResourceSerializer::MacJobDecode.GetOriginalAddress()));
        return ok;
    }

private:
    static void OnJobDecode(const char*, const Red::MacDecodeSource* aSource, uint8_t* aDestination, uint32_t aCapacity)
    {
        if (!aSource || !aSource->data || aSource->size < 8 || !aDestination)
        {
            return;
        }
        const uint32_t scratchSize = *reinterpret_cast<const uint32_t*>(RED4ext::RelocBase::GetImageBase() + ScratchSizeRva);
        if (scratchSize == 0 || aCapacity != scratchSize)
        {
            return;
        }
        uint32_t magic = 0;
        uint32_t decoded = 0;
        std::memcpy(&magic, aSource->data, sizeof(magic));
        std::memcpy(&decoded, aSource->data + 4, sizeof(decoded));
        if (magic != KarkMagic || decoded >= aCapacity)
        {
            return;
        }
        std::memset(aDestination + decoded, 0, (std::min)(TailBytes, aCapacity - decoded));
        s_zeroed.fetch_add(1, std::memory_order_relaxed);
    }
};
}

bool Mac::InstallScratchTailHook()
{
    return ScratchTailHook::Install();
}

unsigned long long Mac::ScratchTailsZeroed()
{
    return s_zeroed.load(std::memory_order_relaxed);
}
