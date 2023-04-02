#include "RedLibProvider.hpp"
#include "Red/Rtti/Registrar.hpp"

void Support::RedLibProvider::OnBootstrap()
{
    Red::RTTIRegistrar::RegisterPending();
}
