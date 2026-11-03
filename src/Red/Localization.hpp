#pragma once

namespace Raw::Localization
{
#if defined(__APPLE__)
// Mac ABI (R19): a plain function, the path in x0 and the entries Handle returned through x8. LocalizationService's
// HookAfter handler (Handle&, ResourcePath) is the "tail observer" form: it gets the returned Handle by reference and the path.
constexpr auto LoadTexts = Core::RawFunc<
    /* addr = */ Red::AddressLib::Localization_LoadOnScreens,
    /* type = */ Red::Handle<Red::localization::PersistenceOnScreenEntries> (*)(Red::ResourcePath aPath)>();
#else
constexpr auto LoadTexts = Core::RawFunc<
    /* addr = */ Red::AddressLib::Localization_LoadOnScreens,
    /* type = */ uint64_t (*)(Red::Handle<Red::localization::PersistenceOnScreenEntries>& aOut,
                              Red::ResourcePath aPath)>();
#endif
}
