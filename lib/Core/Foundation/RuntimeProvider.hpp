#pragma once

#include "Core/Foundation/Feature.hpp"
#include "Core/Platform.hpp"

namespace Core
{
class RuntimeProvider : public Feature
{
public:
#if defined(_WIN32) || defined(_WIN64)
    explicit RuntimeProvider(HMODULE aHandle) noexcept;
#else
    explicit RuntimeProvider(void* aHandle) noexcept;
#endif

    auto SetBaseImagePathDepth(int aDepth) noexcept
    {
        m_basePathDepth = aDepth;
        return Defer(this);
    }

protected:
    void OnInitialize() override;

#if defined(_WIN32) || defined(_WIN64)
    HMODULE m_handle;
#else
    void* m_handle;
#endif
    int m_basePathDepth;
};
}
