#include "ComponentEx.hpp"
#include "App/Entity/ComponentWrapper.hpp"

bool App::ComponentEx::ChangeAppearance(Red::CName aAppearance)
{
    ComponentWrapper wrapper(this);
    return wrapper.SetAppearanceName(aAppearance) && wrapper.LoadAppearance();;
}

bool App::ComponentEx::LoadAppearance()
{
    ComponentWrapper wrapper(this);
    return wrapper.LoadAppearance();
}
