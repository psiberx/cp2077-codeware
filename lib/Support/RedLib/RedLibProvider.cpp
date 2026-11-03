#include "RedLibProvider.hpp"
#include "Red/TypeInfo/Registrar.hpp"

#if defined(__APPLE__)
#include "Support/macOS/Lifecycle.hpp"
#endif

void Support::RedLibProvider::OnBootstrap()
{
#if defined(__APPLE__)
    // macOS: the game never calls the RTTI register callbacks. The queued RedLib callbacks run when the plugin entry
    // points report the two lifecycle events (see Support/macOS/Lifecycle.hpp): types register at script
    // initialisation, and the describe callbacks and late systems run again after the scripts are loaded.
    Mac::Lifecycle::OnNativesRegistered(&Red::TypeInfoRegistrar::RunPending, "RedLib");
    Mac::Lifecycle::OnScriptsLoaded(&Red::TypeInfoRegistrar::RunPending, "RedLib");
#else
    Red::TypeInfoRegistrar::RegisterDiscovered();
#endif
}
