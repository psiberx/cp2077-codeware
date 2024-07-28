#pragma once

#include "Core/Facades/Runtime.hpp"

namespace App::Env
{
inline std::filesystem::path ScriptsDir()
{
    return Core::Runtime::GetModuleDir() / L"Scripts";
}

inline std::filesystem::path PersistentDir()
{
    return Core::Runtime::GetModuleDir() / L"Persistent";
}

inline std::filesystem::path KnownHashesPath()
{
    return Core::Runtime::GetModuleDir() / L"Data" / L"KnownHashes.txt";
}

inline std::filesystem::path LegacyScriptsDir()
{
    return Core::Runtime::GetRootDir() / L"r6" / L"scripts" / L"Codeware";
}

inline std::filesystem::path GameDir()
{
    return Core::Runtime::GetRootDir();
}
}
