#pragma once

#include "Core/Runtime/HostImage.hpp"
#include "Core/Runtime/ModuleImage.hpp"

namespace Core::Runtime
{
void Initialize(const Core::HostImage& aHost, const Core::ModuleImage& aModule);

HostImage* GetHost();
ModuleImage* GetModule();

[[nodiscard]] uintptr_t GetImageBase();
[[nodiscard]] std::filesystem::path GetImagePath();
[[nodiscard]] std::filesystem::path GetRootDir();
[[nodiscard]] std::filesystem::path GetModulePath();
[[nodiscard]] std::filesystem::path GetModuleDir();
[[nodiscard]] std::string GetModuleName();
[[nodiscard]] bool IsASI();
#if defined(_WIN32) || defined(_WIN64)
[[nodiscard]] bool IsASI(HMODULE aHandle);
[[nodiscard]] bool IsEXE(std::wstring_view aName);
#else
[[nodiscard]] bool IsASI(void* aHandle);
[[nodiscard]] bool IsEXE(std::string_view aName);
#endif
}
