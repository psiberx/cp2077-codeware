#pragma once

#include "Red/GameEngine.hpp"

namespace App
{
struct EngineTimeEx : Red::EngineTime
{
    static uint64_t GetFrequency()
    {
        return static_cast<uint64_t>(*Raw::EngineTime::Frequency);
    }

    static Red::EngineTime FromTicks(uint64_t aTicks)
    {
        return {aTicks};
    }

    uint64_t ToTicks()
    {
        return ticks;
    }
};
}

RTTI_EXPAND_CLASS(Red::EngineTime, App::EngineTimeEx, {
    RTTI_METHOD(GetFrequency);
    RTTI_METHOD(FromTicks);
    RTTI_METHOD(ToTicks);
});
