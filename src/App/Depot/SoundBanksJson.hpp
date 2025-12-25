#pragma once

#include "Red/AudioSystem.hpp"

namespace App
{
struct SoundBanksJson : Red::CResource
{
    SoundBanksJson() = default;

    Red::DynArray<Red::SoundBankEntry> soundBanks;

    RTTI_IMPL_TYPEINFO(App::SoundBanksJson);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(Red::SoundBankEntry, {
    RTTI_PROPERTY(name);
    RTTI_PROPERTY(isResident);
    RTTI_PROPERTY(resourcePath);
});

RTTI_DEFINE_CLASS(App::SoundBanksJson, {
    RTTI_ABSTRACT();
    RTTI_PARENT(Red::CResource);
    RTTI_PROPERTY(soundBanks);
});
