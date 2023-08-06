#pragma once

namespace Red
{
struct KeyboardState
{
    uint16_t shiftLeft : 1;
    uint16_t shiftRight : 1;
    uint16_t controlLeft : 1;
    uint16_t controlRight : 1;
    uint16_t altLeft : 1;
    uint16_t altRight : 1;
    uint16_t b10 : 10;
};
RED4EXT_ASSERT_SIZE(KeyboardState, 0x2);

struct RawInputData
{
    EInputKey key;       // 00
    EInputAction action; // 04
    float value;         // 08
    uint32_t mouseX;     // 0C
    uint32_t mouseY;     // 10
    uint32_t unk14;      // 14
    uint32_t unk18;      // 18
    uint64_t unk20;      // 20
    uint64_t unk28;      // 28
    uint64_t unk30;      // 30
    uint64_t unk38;      // 38
};
RED4EXT_ASSERT_SIZE(RawInputData, 0x40);

struct RawInputBuffer
{
    virtual ~RawInputBuffer() = 0;
    virtual DynArray<RawInputData>& GetInputs() = 0;

    DynArray<RawInputData> inputs;
};
}
