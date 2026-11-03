#pragma once

#include "Core/Platform.hpp"

namespace Core
{
class ModuleImage
{
public:
#if defined(_WIN32) || defined(_WIN64)
    explicit ModuleImage(HMODULE aHandle);
#else
    explicit ModuleImage(void* aHandle);
#endif
    ~ModuleImage() = default;

    [[nodiscard]] std::filesystem::path GetPath() const;
    [[nodiscard]] std::filesystem::path GetDir() const;
    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] bool IsASI() const;

private:
    std::filesystem::path m_path;
};
}
