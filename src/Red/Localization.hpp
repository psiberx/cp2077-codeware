#pragma once

namespace Raw::Localization
{
constexpr auto LoadTexts = Core::RawFunc<
    /* addr = */ Red::AddressLib::Localization_LoadOnScreens,
    /* type = */ uint64_t (*)(Red::Handle<Red::localization::PersistenceOnScreenEntries>& aOut,
                              Red::ResourcePath aPath)>();
}
