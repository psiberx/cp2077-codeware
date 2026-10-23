#pragma once

namespace Red
{
// Game 2.5 (exe 3.0.88.46235): the node setup layout changed with the sector buffer version (0x3E -> 0x44).
// The 2.5 converter for old 0x3E data, 0x20BDFB0 (`cmp dword ptr [rcx+0x28],0x3e`), copies old 0x00-0x4F as is,
// old 0x58/0x60/0x68 to the same offsets, old float 0x70 -> 0x78, old float 0x74 -> 0x7C, old byte 0x88 -> 0x84,
// and packs a qword at 0x70: (old 0x78 & 0x7FFFF) | ((old 0x78 >> 1) & 0xFFFFFFF80000) | (old 0x80 << 48).
// The node pointer fix-up 0x699F10 reads the node index as `[setup+0x70] & 0x7FFFF` (2.31 0x26F390:
// `[setup+0x78] & 0xFFFFF`) and writes the node pointer to setup+0x50; the element stride stays 0x90 (/144).
struct __declspec(align(0x10)) CompiledNodeInstanceSetupInfo
{
    Transform transform;               // 00
    Vector3 scale;                     // 20
    Vector3 secondaryRefPointPosition; // 2C
    Vector3 streamingRefPoint;         // 38
    Vector3 unk44;                     // 44
    worldNode* node;                   // 50
    uint64_t globalNodeID;             // 58
    uint64_t proxyNodeID;              // 60
    ResourcePath unk68;                // 68
    uint64_t nodeIndex : 19;           // 70 (2.31: uint16 at 0x78, engine mask 0xFFFFF)
    uint64_t unk70_19 : 29;            // 70 (2.31: bits 20-48 of the qword at 0x78)
    uint64_t unk70_48 : 16;            // 70 (2.31: uint16 at 0x80)
    float secondaryRefPointDistance;   // 78 (2.31: 70)
    float streamingDistance;           // 7C (2.31: 74)
    uint32_t unk80;                    // 80
    uint8_t unk84;                     // 84 (2.31: 88)
    uint8_t unk85[0x90 - 0x85];        // 85
};
RED4EXT_ASSERT_SIZE(CompiledNodeInstanceSetupInfo, 0x90);
RED4EXT_ASSERT_OFFSET(CompiledNodeInstanceSetupInfo, node, 0x50);
RED4EXT_ASSERT_OFFSET(CompiledNodeInstanceSetupInfo, globalNodeID, 0x58);
RED4EXT_ASSERT_OFFSET(CompiledNodeInstanceSetupInfo, proxyNodeID, 0x60);
RED4EXT_ASSERT_OFFSET(CompiledNodeInstanceSetupInfo, secondaryRefPointDistance, 0x78);
RED4EXT_ASSERT_OFFSET(CompiledNodeInstanceSetupInfo, streamingDistance, 0x7C);
RED4EXT_ASSERT_OFFSET(CompiledNodeInstanceSetupInfo, unk84, 0x84);

struct CompiledNodeInstanceSetupInfoBuffer : DataBuffer
{
    [[nodiscard]] inline CompiledNodeInstanceSetupInfo* begin() const
    {
        return reinterpret_cast<CompiledNodeInstanceSetupInfo*>(buffer.data);
    }

    [[nodiscard]] inline CompiledNodeInstanceSetupInfo* end() const
    {
        return reinterpret_cast<CompiledNodeInstanceSetupInfo*>(reinterpret_cast<uintptr_t>(buffer.data) +
                                                                buffer.size);
    }

    CompiledNodeInstanceSetupInfo* GetInstance(int64_t aIndex)
    {
        return begin() + aIndex;
    }

    uint32_t GetInstanceCount()
    {
        return buffer.size / sizeof(CompiledNodeInstanceSetupInfo);
    }
};
RED4EXT_ASSERT_SIZE(CompiledNodeInstanceSetupInfoBuffer, 0x28);

// Game 2.5 (exe 3.0.88.46235): a dword (the setup data version) was inserted at +0x28, so the arrays moved by 8.
// The buffer serializer 0x6CCF7C handles `lea rcx,[rbp+0x30]` (nodes, size at +0x3C) and `lea rcx,[rbp+0x40]`
// (nodeRefs, size at +0x4C); 2.31's 0x41A58C used +0x28/+0x34 and +0x38/+0x44. The sector's serialize virtual
// 0xE9A7DC stores an old version with `mov dword ptr [sector+0x68],eax` (buffer +0x28) and the fix-up 0x699F10
// reads the node handles from `[buffer+0x30]`.
struct StreamingSectorNodeBuffer
{
    CompiledNodeInstanceSetupInfoBuffer nodeSetups; // 00
    uint32_t setupVersion;                          // 28 (0x44 on 2.5; 0x3E data is converted on load)
    DynArray<Handle<worldNode>> nodes;              // 30 (2.31: 28)
    DynArray<NodeRef> nodeRefs;                     // 40 (2.31: 38)
};
RED4EXT_ASSERT_OFFSET(StreamingSectorNodeBuffer, setupVersion, 0x28);
RED4EXT_ASSERT_OFFSET(StreamingSectorNodeBuffer, nodes, 0x30);
RED4EXT_ASSERT_OFFSET(StreamingSectorNodeBuffer, nodeRefs, 0x40);
}

namespace Raw::StreamingSector
{
// Game 2.5: unchanged at +0x40 (worldStreamingSector serialize virtual 0xE9A7DC `lea rdx,[rbx+0x40]` and dtor
// 0x699B04 `lea rcx,[rbx+0x40]`, same as 2.31 0xDF0384/0x26EED9); the sector grew by 8 inside this buffer.
using NodeBuffer = Core::OffsetPtr<0x40, Red::StreamingSectorNodeBuffer>;
}
