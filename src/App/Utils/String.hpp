#pragma once

#if defined(__APPLE__)
#include <wctype.h>
#include <xlocale.h>
#endif

namespace App
{
#if defined(__APPLE__)
inline locale_t Utf8Locale()
{
    static const locale_t loc = newlocale(LC_CTYPE_MASK, "en_US.UTF-8", nullptr);
    return loc;
}

inline wchar_t Utf32Lower(wchar_t aChar)
{
    const locale_t loc = Utf8Locale();
    if (!loc)
    {
        return static_cast<wchar_t>(towlower(static_cast<wint_t>(aChar)));
    }
    return static_cast<wchar_t>(towlower_l(static_cast<wint_t>(aChar), loc));
}

inline wchar_t Utf32Upper(wchar_t aChar)
{
    const locale_t loc = Utf8Locale();
    if (!loc)
    {
        return static_cast<wchar_t>(towupper(static_cast<wint_t>(aChar)));
    }
    return static_cast<wchar_t>(towupper_l(static_cast<wint_t>(aChar), loc));
}
#endif

inline int32_t UTF8CharSize(const char& aChar)
{
    if ((aChar & 0x80) == 0)
        return 1;

    if ((aChar & 0xE0) == 0xC0)
        return 2;

    if ((aChar & 0xF0) == 0xE0)
        return 3;

    if ((aChar & 0xF8) == 0xF0)
        return 4;

    return 0;
}

inline uint32_t UTF8StrSize(std::string_view& aStr, int32_t aLength)
{
    uint32_t size = 0;

    while (aLength > 0 && size < aStr.size())
    {
        size += UTF8CharSize(aStr[size]);
        --aLength;
    }

    return size;
}

inline int32_t UTF8StrLen(Red::ScriptRef<Red::CString>& aStr)
{
    int32_t length = 0;

    for (const char& c : *aStr)
    {
        if ((c & 0b11000000) != 0b10000000)
        {
            ++length;
        }
    }

    return length;
}

inline Red::CString UTF8StrLeft(Red::ScriptRef<Red::CString>& aStr, int32_t aLength)
{
    std::string_view sv(aStr->c_str(), aStr->Length());
    sv.remove_suffix(sv.size() - UTF8StrSize(sv, aLength));
    return sv;
}

inline Red::CString UTF8StrRight(Red::ScriptRef<Red::CString>& aStr, int32_t aLength)
{
    std::string_view sv(aStr->c_str(), aStr->Length());
    sv.remove_prefix(UTF8StrSize(sv, UTF8StrLen(aStr) - aLength));
    return sv;
}

inline Red::CString UTF8StrMid(Red::ScriptRef<Red::CString>& aStr, int32_t aOffset, int32_t aLength)
{
    std::string_view sv(aStr->c_str(), aStr->Length());
    sv.remove_prefix(UTF8StrSize(sv, aOffset));
    sv.remove_suffix(sv.size() - UTF8StrSize(sv, aLength));
    return sv;
}

inline Red::CString UTF8StrLower(Red::ScriptRef<Red::CString>& aStr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wstr = converter.from_bytes(aStr->c_str());
#if defined(__APPLE__)
    std::transform(wstr.begin(), wstr.end(), wstr.begin(), Utf32Lower);
#else
    std::transform(wstr.begin(), wstr.end(), wstr.begin(), ::towlower);
#endif
    return converter.to_bytes(wstr);
}

inline Red::CString UTF8StrUpper(Red::ScriptRef<Red::CString>& aStr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wstr = converter.from_bytes(aStr->c_str());
#if defined(__APPLE__)
    std::transform(wstr.begin(), wstr.end(), wstr.begin(), Utf32Upper);
#else
    std::transform(wstr.begin(), wstr.end(), wstr.begin(), ::towupper);
#endif
    return converter.to_bytes(wstr);
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::UTF8StrLen);
    RTTI_FUNCTION(App::UTF8StrLeft);
    RTTI_FUNCTION(App::UTF8StrRight);
    RTTI_FUNCTION(App::UTF8StrMid);
    RTTI_FUNCTION(App::UTF8StrLower);
    RTTI_FUNCTION(App::UTF8StrUpper);
});
