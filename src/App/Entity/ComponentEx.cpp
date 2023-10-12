#include "ComponentEx.hpp"
#include "App/Entity/ComponentWrapper.hpp"

bool App::ComponentEx::LoadAppearance()
{
    return ComponentWrapper(this).LoadAppearance();
}
