#pragma once

namespace App
{
template<typename T>
requires std::is_integral_v<T>
T ParseInt(const Red::CString& aIn, Red::Optional<int32_t, 10> aBase)
{
    using Temp = std::conditional_t<std::is_signed_v<T>, int64_t, uint64_t>;

    Temp out;
    char* end;

    if constexpr (std::is_signed_v<T>)
        out = std::strtoll(aIn.c_str(), &end, aBase);
    else
        out = std::strtoull(aIn.c_str(), &end, aBase);

    if (end != aIn.c_str() + aIn.Length())
        return static_cast<T>(0);

    return static_cast<T>(out);
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::ParseInt<int8_t>, "ParseInt8");
    RTTI_FUNCTION(App::ParseInt<int16_t>, "ParseInt16");
    RTTI_FUNCTION(App::ParseInt<int32_t>, "ParseInt32");
    RTTI_FUNCTION(App::ParseInt<int64_t>, "ParseInt64");
    RTTI_FUNCTION(App::ParseInt<uint8_t>, "ParseUint8");
    RTTI_FUNCTION(App::ParseInt<uint16_t>, "ParseUint16");
    RTTI_FUNCTION(App::ParseInt<uint32_t>, "ParseUint32");
    RTTI_FUNCTION(App::ParseInt<uint64_t>, "ParseUint64");
});
