#pragma once

namespace App
{
struct CDistantLightsResourceEntry
{
    uint8_t red;               // 00
    uint8_t green;             // 01
    uint8_t blue;              // 02
    uint8_t unk03;             // 03
    float intensity;           // 04
    uint16_t unk08;            // 08
    uint16_t unk0A;            // 0A
    uint16_t unk0C;            // 0C
    uint8_t dirX;              // 0E
    uint8_t dirY;              // 0F
    uint32_t posX_posZ;        // 10
    uint32_t posY_flipZ_angle; // 14
};
RED4EXT_ASSERT_SIZE(CDistantLightsResourceEntry, 0x18);
RED4EXT_ASSERT_OFFSET(CDistantLightsResourceEntry, intensity, 0x04);
RED4EXT_ASSERT_OFFSET(CDistantLightsResourceEntry, unk08, 0x08);
RED4EXT_ASSERT_OFFSET(CDistantLightsResourceEntry, unk0A, 0x0A);
RED4EXT_ASSERT_OFFSET(CDistantLightsResourceEntry, unk0C, 0x0C);
RED4EXT_ASSERT_OFFSET(CDistantLightsResourceEntry, dirX, 0x0E);
RED4EXT_ASSERT_OFFSET(CDistantLightsResourceEntry, posX_posZ, 0x10);
RED4EXT_ASSERT_OFFSET(CDistantLightsResourceEntry, posY_flipZ_angle, 0x14);

struct CDistantLightsResourceEntryWrapper : Red::IScriptable
{
    CDistantLightsResourceEntryWrapper()
        : entry(nullptr)
    {
    }

    CDistantLightsResourceEntryWrapper(CDistantLightsResourceEntry* aEntry)
        : entry(aEntry)
    {
    }

    CDistantLightsResourceEntryWrapper(const CDistantLightsResourceEntryWrapper&) = default;
    CDistantLightsResourceEntryWrapper(CDistantLightsResourceEntryWrapper&&) = default;

    [[nodiscard]] Red::Color GetColor() const
    {
        return {entry->red, entry->green, entry->blue, 0};
    }

    void SetColor(const Red::Color& aColor) const
    {
        entry->red = aColor.Red;
        entry->green = aColor.Green;
        entry->blue = aColor.Blue;
    }

    [[nodiscard]] float GetIntensity() const
    {
        return entry->intensity;
    }

    void SetIntensity(float aValue) const
    {
        entry->intensity = aValue;
    }

    [[nodiscard]] float GetField08() const
    {
        return static_cast<float>(std::bit_cast<float16_t>(entry->unk08));
    }

    void SetField08(float aValue) const
    {
        entry->unk08 = std::bit_cast<uint16_t>(static_cast<float16_t>(aValue));
    }

    [[nodiscard]] float GetField0A() const
    {
        return static_cast<float>(std::bit_cast<float16_t>(entry->unk0A));
    }

    void SetField0A(float aValue) const
    {
        entry->unk0A = std::bit_cast<uint16_t>(static_cast<float16_t>(aValue));
    }

    [[nodiscard]] float GetDirX() const
    {
        return static_cast<float>(entry->dirX) / 127.0f - 1.0f;
    }

    void SetDirX(float aValue) const
    {
        const auto scaled = std::clamp(aValue, -1.0f, 1.0f) * 127.0f + 127.0f;

        entry->dirX = static_cast<uint8_t>(std::lround(scaled));
    }

    [[nodiscard]] float GetDirY() const
    {
        return static_cast<float>(entry->dirY) / 127.0f - 1.0f;
    }

    void SetDirY(float aValue) const
    {
        const auto scaled = std::clamp(aValue, -1.0f, 1.0f) * 127.0f + 127.0f;

        entry->dirY = static_cast<uint8_t>(std::lround(scaled));
    }

    [[nodiscard]] float GetPosX() const
    {
        const auto position = static_cast<int32_t>(entry->posX_posZ & 0xFFFFF) - (1 << 19);

        return static_cast<float>(position) * 0.02f;
    }

    void SetPosX(float aValue) const
    {
        const auto position = std::clamp(aValue * 50.0f, -524288.0f, 524287.0f);
        const auto packed = static_cast<uint32_t>(static_cast<int32_t>(std::lround(position)) & 0xFFFFF);

        entry->posX_posZ = (entry->posX_posZ & ~0xFFFFFu) | packed;
    }

    [[nodiscard]] float GetPosY() const
    {
        const auto position = static_cast<int32_t>(entry->posY_flipZ_angle & 0xFFFFF) - (1 << 19);

        return static_cast<float>(position) * 0.02f;
    }

    void SetPosY(float aValue) const
    {
        const auto position = std::clamp(aValue * 50.0f, -524288.0f, 524287.0f);
        const auto packed = static_cast<uint32_t>(static_cast<int32_t>(std::lround(position)) & 0xFFFFF);

        entry->posY_flipZ_angle = (entry->posY_flipZ_angle & ~0xFFFFFu) | packed;
    }

    [[nodiscard]] float GetPosZ() const
    {
        const auto position = static_cast<float>(entry->posX_posZ >> 20) / 4095.0f;

        return position * position * 850.0f - 50.0f;
    }

    void SetPosZ(float aValue) const
    {
        const auto position = std::clamp(aValue + 50.0f, 0.0f, 850.0f);
        const auto packed = static_cast<uint32_t>(std::lround(std::sqrt(position / 850.0f) * 4095.0f)) << 20;

        entry->posX_posZ = (entry->posX_posZ & 0xFFFFFu) | packed;
    }

    [[nodiscard]] bool IsZFlip() const
    {
        return (entry->posY_flipZ_angle & 0x100000) != 0;
    }

    void SetZFlip(bool aValue) const
    {
        const auto packed = aValue ? 0x100000u : 0u;

        entry->posY_flipZ_angle = (entry->posY_flipZ_angle & ~0x100000u) | packed;
    }

    [[nodiscard]] float GetAngle() const
    {
        return static_cast<float>(entry->posY_flipZ_angle >> 24) * (180.0f / 255.0f);
    }

    void SetAngle(float aValue) const
    {
        const auto packed = static_cast<uint32_t>(std::lround(std::clamp(aValue, 0.0f, 180.0f) / 180.0f * 255.0f)) << 24;

        entry->posY_flipZ_angle = (entry->posY_flipZ_angle & 0x00FFFFFFu) | packed;
    }

    CDistantLightsResourceEntry* entry;

    RTTI_IMPL_TYPEINFO(App::CDistantLightsResourceEntryWrapper);
    RTTI_IMPL_ALLOCATOR();
};

struct CDistantLightsResourceEx : Red::CDistantLightsResource
{
    [[nodiscard]] int32_t GetEntryCount()
    {
        auto* buffer = reinterpret_cast<Red::TDataBuffer<CDistantLightsResourceEntry>*>(&data);

        return static_cast<int32_t>(buffer->Size());
    }

    [[nodiscard]] Red::Handle<CDistantLightsResourceEntryWrapper> GetEntry(int32_t aIndex)
    {
        auto* buffer = reinterpret_cast<Red::TDataBuffer<CDistantLightsResourceEntry>*>(&data);

        if (aIndex < 0 || aIndex >= buffer->Size())
            return {};

        return Red::MakeHandle<CDistantLightsResourceEntryWrapper>(&buffer->At(aIndex));
    }
};
}

RTTI_EXPAND_CLASS(Red::CDistantLightsResource, App::CDistantLightsResourceEx, {
    RTTI_METHOD(GetEntryCount);
    RTTI_METHOD(GetEntry);
});

RTTI_DEFINE_CLASS(App::CDistantLightsResourceEntryWrapper, {
    RTTI_METHOD(GetColor);
    RTTI_METHOD(SetColor);
    RTTI_METHOD(GetIntensity);
    RTTI_METHOD(SetIntensity);
    RTTI_METHOD(GetField08);
    RTTI_METHOD(SetField08);
    RTTI_METHOD(GetField0A);
    RTTI_METHOD(SetField0A);
    RTTI_METHOD(GetDirX);
    RTTI_METHOD(SetDirX);
    RTTI_METHOD(GetDirY);
    RTTI_METHOD(SetDirY);
    RTTI_METHOD(GetPosX);
    RTTI_METHOD(SetPosX);
    RTTI_METHOD(GetPosY);
    RTTI_METHOD(SetPosY);
    RTTI_METHOD(GetPosZ);
    RTTI_METHOD(SetPosZ);
    RTTI_METHOD(IsZFlip);
    RTTI_METHOD(SetZFlip);
    RTTI_METHOD(GetAngle);
    RTTI_METHOD(SetAngle);
});
