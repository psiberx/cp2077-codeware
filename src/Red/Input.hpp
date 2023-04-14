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
}
