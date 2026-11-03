#include "ModuleImage.hpp"

#if !defined(_WIN32) && !defined(_WIN64)
#include <cstdio>
#include <dlfcn.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
Core::ModuleImage::ModuleImage(HMODULE aHandle)
{
    std::wstring filePath;
    wil::GetModuleFileNameW(aHandle, filePath);

    m_path = filePath;
}
#else
// Path of the image that holds this function (the plugin itself)
static std::string GetThisLibraryPath()
{
    Dl_info info;
    // Use the address of this function to find which library contains it
    if (dladdr(reinterpret_cast<void*>(&GetThisLibraryPath), &info) && info.dli_fname)
    {
        return info.dli_fname;
    }
    return "";
}

Core::ModuleImage::ModuleImage(void* aHandle)
{
    // aHandle is an address inside the module (dladdr), or a RED4ext plugin handle that dladdr cannot resolve.
    std::string filePath = Core::Platform::GetModuleFileName(aHandle);
    
    if (filePath.empty())
    {
        // Fallback: use dladdr on a function in this library
        filePath = GetThisLibraryPath();
    }
    
    if (!filePath.empty())
    {
        m_path = filePath;
    }
    else
    {
        std::fprintf(stderr, "[ModuleImage] Warning: could not determine the module path\n");
        m_path = "";
    }
}
#endif

std::filesystem::path Core::ModuleImage::GetPath() const
{
    return m_path;
}

std::filesystem::path Core::ModuleImage::GetDir() const
{
    return m_path.parent_path();
}

std::string Core::ModuleImage::GetName() const
{
    return m_path.stem().string();
}

bool Core::ModuleImage::IsASI() const
{
#if defined(_WIN32) || defined(_WIN64)
    return m_path.extension() == L".asi";
#else
    return m_path.extension() == ".asi";
#endif
}
