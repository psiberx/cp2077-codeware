#include "RuntimeProvider.hpp"
#include "Core/Facades/Runtime.hpp"

#if defined(_WIN32) || defined(_WIN64)
Core::RuntimeProvider::RuntimeProvider(HMODULE aHandle) noexcept
    : m_handle(aHandle)
    , m_basePathDepth(0)
{
}
#else
Core::RuntimeProvider::RuntimeProvider(void* aHandle) noexcept
    : m_handle(aHandle)
    , m_basePathDepth(0)
{
}
#endif

void Core::RuntimeProvider::OnInitialize()
{
    Runtime::Initialize(HostImage(m_basePathDepth), ModuleImage(m_handle));
}
