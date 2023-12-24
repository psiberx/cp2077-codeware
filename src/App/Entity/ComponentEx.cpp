#include "ComponentEx.hpp"
#include "App/Entity/ComponentWrapper.hpp"

bool App::ComponentEx::ChangeResource(Red::ResourceAsyncReference<> aReference, Red::Optional<bool> aWait)
{
    ComponentWrapper wrapper(this);
    return wrapper.SetResourcePath(aReference.path) && wrapper.LoadResource(aWait);
}

bool App::ComponentEx::LoadResource(Red::Optional<bool> aWait)
{
    ComponentWrapper wrapper(this);
    return wrapper.LoadResource(aWait);
}

bool App::ComponentEx::ChangeAppearance(Red::CName aName)
{
    ComponentWrapper wrapper(this);
    return wrapper.SetAppearanceName(aName) && wrapper.LoadAppearance();
}

bool App::ComponentEx::LoadAppearance()
{
    ComponentWrapper wrapper(this);
    return wrapper.LoadAppearance();
}
