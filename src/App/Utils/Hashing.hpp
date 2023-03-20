#pragma once

namespace App
{
uint64_t FNV1a64(Red::ScriptRef<Red::CString>& aData, Red::Optional<uint64_t, 0xCBF29CE484222325> aSeed = {})
{
    return Red::FNV1a64(aData.ref->c_str(), aSeed);
}

uint32_t FNV1a32(Red::ScriptRef<Red::CString>& aData, Red::Optional<uint32_t, 0x811C9DC5> aSeed = {})
{
    return Red::FNV1a32(aData.ref->c_str(), aSeed);
}

uint32_t Murmur3(Red::ScriptRef<Red::CString>& aData, Red::Optional<uint32_t, 0X5EEDBA5E> aSeed = {})
{
    return Red::Murmur3_32(reinterpret_cast<const uint8_t*>(aData.ref->c_str()), aData.ref->Length(), aSeed);
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::FNV1a64);
    RTTI_FUNCTION(App::FNV1a32);
    RTTI_FUNCTION(App::Murmur3);
});
