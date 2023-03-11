#pragma once

namespace App
{
template<typename T>
bool BitGet(T aValue, int32_t aPos)
{
    return (aValue >> aPos) & static_cast<T>(1);
}

template<typename T>
T BitSet(T aValue, int32_t aPos, bool aState)
{
    return aState
        ? (aValue | (static_cast<T>(1) << aPos))
        : (aValue & ~(static_cast<T>(1) << aPos));
}

template<typename T>
T BitShiftLeft(T aValue, int32_t aShift)
{
    return aValue << aShift;
}

template<typename T>
T BitShiftRight(T aValue, int32_t aShift)
{
    return aValue >> aShift;
}
}

#define RTTI_BIT_FUNCTIONS(_size, _type) \
    RTTI_FUNCTION(App::BitGet<_type>, "BitTest"#_size); \
    RTTI_FUNCTION(App::BitSet<_type>, "BitSet"#_size); \
    RTTI_FUNCTION(App::BitShiftLeft<_type>, "BitShiftL"#_size); \
    RTTI_FUNCTION(App::BitShiftRight<_type>, "BitShiftR"#_size);

RTTI_DEFINE_GLOBALS({
    RTTI_BIT_FUNCTIONS(8, uint8_t);
    RTTI_BIT_FUNCTIONS(16, uint16_t);
    RTTI_BIT_FUNCTIONS(32, uint32_t);
    RTTI_BIT_FUNCTIONS(64, uint64_t);
});
