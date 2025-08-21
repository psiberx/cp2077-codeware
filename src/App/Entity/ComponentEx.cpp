#include "ComponentEx.hpp"
#include "App/Entity/ComponentWrapper.hpp"

bool App::ComponentEx::ChangeResource(const Red::ResourceAsyncReference<>& aReference, Red::Optional<bool> aWait)
{
    ComponentWrapper wrapper(this);
    return wrapper.SetResourcePath(aReference.path) && wrapper.LoadResource(true, aWait);
}

bool App::ComponentEx::ChangeAppearance(Red::CName aName, Red::Optional<bool> aWait)
{
    ComponentWrapper wrapper(this);
    return wrapper.SetAppearanceName(aName) && wrapper.LoadResource(true, aWait);
}

bool App::ComponentEx::LoadAppearance(Red::Optional<bool> aWait)
{
    ComponentWrapper wrapper(this);
    return wrapper.LoadResource(true, aWait);
}

bool App::ComponentEx::RefreshAppearance()
{
    ComponentWrapper wrapper(this);
    return wrapper.RefreshAppearance();
}

void App::ComponentEx::ResetMaterialCache()
{
    ComponentWrapper wrapper(this);
    wrapper.ResetMaterialCache();
}
