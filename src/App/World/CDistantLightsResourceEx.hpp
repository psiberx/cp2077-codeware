#pragma once

namespace App
{
struct CDistantLightsResourceEntry
{
    uint8_t red;           // 00
    uint8_t green;         // 01
    uint8_t blue;          // 02
    uint8_t unk03;         // 03
    float intensity;       // 04
    uint16_t unk08;        // 08
    uint16_t unk10;        // 10
    uint16_t unk0C;        // 0C
    uint8_t dirX;          // 0E
    uint8_t dirY;          // 0F
    uint32_t posX : 20;    // 10
    uint32_t posZ : 12;    // 10:20
    uint32_t posY : 20;    // 14
    uint32_t unk14_20 : 4; // 14:20
    uint32_t angle : 8;    // 14:24
};
RED4EXT_ASSERT_SIZE(CDistantLightsResourceEntry, 0x18);
RED4EXT_ASSERT_OFFSET(CDistantLightsResourceEntry, intensity, 0x04);

struct CDistantLightsResourceEx : Red::CDistantLightsResource
{
    [[nodiscard]] int32_t GetEntryCount()
    {
        auto* buffer = reinterpret_cast<Red::TDataBuffer<CDistantLightsResourceEntry>*>(&data);

        return static_cast<int32_t>(buffer->Size());
    }

    [[nodiscard]] Red::ScriptRef<CDistantLightsResourceEntry> GetEntry(int32_t aIndex)
    {
        auto* buffer = reinterpret_cast<Red::TDataBuffer<CDistantLightsResourceEntry>*>(&data);

        if (aIndex < 0 || aIndex >= buffer->Size())
            return {};

        auto& entry = buffer->At(aIndex);

        return {buffer->At(aIndex)};
    }
};
}

RTTI_EXPAND_CLASS(Red::CDistantLightsResource, App::CDistantLightsResourceEx, {
    RTTI_METHOD(GetEntryCount);
    RTTI_METHOD(GetEntry);
});

RTTI_DEFINE_CLASS(App::CDistantLightsResourceEntry, {
    RTTI_PROPERTY(red);
    RTTI_PROPERTY(green);
    RTTI_PROPERTY(blue);
    RTTI_PROPERTY(unk03);
    RTTI_PROPERTY(intensity);
    RTTI_PROPERTY(unk08);
    RTTI_PROPERTY(unk10);
    RTTI_PROPERTY(unk0C);
    RTTI_PROPERTY(dirX);
    RTTI_PROPERTY(dirY);
});
