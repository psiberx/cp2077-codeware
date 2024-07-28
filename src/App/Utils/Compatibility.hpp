#pragma once

#include "App/Environment.hpp"

namespace App
{
bool GameFileExists(const Red::ScriptRef<Red::CString>& aPath)
{
    if (aPath.ref->Length() == 0)
        return false;

    const auto& gamePath = Env::GameDir();
    auto absolutePath = std::filesystem::absolute(gamePath / aPath.ref->c_str());
    auto relativePath = std::filesystem::relative(absolutePath, gamePath);

    if (relativePath.empty() || relativePath.native().starts_with('.'))
        return false;

    std::error_code error;
    return std::filesystem::exists(absolutePath, error);
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::GameFileExists);
});
