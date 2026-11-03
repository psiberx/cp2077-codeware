#include "HostImage.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include "Core/Win.hpp"

Core::HostImage::HostImage(int aExePathDepth)
{
    const auto handle = GetModuleHandleW(nullptr);

    m_base = reinterpret_cast<uintptr_t>(handle);

    std::wstring filePath;
    wil::GetModuleFileNameW(handle, filePath);

    m_exe = filePath;
    m_root = m_exe.parent_path();

    while (--aExePathDepth >= 0)
        m_root = m_root.parent_path();

    TryResolveVersion(filePath);
}

bool Core::HostImage::TryResolveVersion(const std::wstring& filePath)
{
    auto size = GetFileVersionInfoSizeW(filePath.c_str(), nullptr);
    if (!size)
        return false;

    std::unique_ptr<uint8_t[]> data(new (std::nothrow) uint8_t[size]());
    if (!data)
        return false;

    if (!GetFileVersionInfoW(filePath.c_str(), 0, size, data.get()))
        return false;

    VS_FIXEDFILEINFO* fileInfo = nullptr;
    UINT fileInfoBytes;

    if (!VerQueryValueW(data.get(), L"\\", reinterpret_cast<LPVOID*>(&fileInfo), &fileInfoBytes))
        return false;

    constexpr auto signature = 0xFEEF04BD;
    if (fileInfo->dwSignature != signature)
        return false;

    m_fileVer.major = (fileInfo->dwFileVersionMS >> 16) & 0xFF;
    m_fileVer.minor = fileInfo->dwFileVersionMS & 0xFFFF;
    m_fileVer.build = (fileInfo->dwFileVersionLS >> 16) & 0xFFFF;
    m_fileVer.revision = fileInfo->dwFileVersionLS & 0xFFFF;

    m_productVer.major = (fileInfo->dwProductVersionMS >> 16) & 0xFF;
    m_productVer.minor = fileInfo->dwProductVersionMS & 0xFFFF;
    m_productVer.patch = (fileInfo->dwProductVersionLS >> 16) & 0xFFFF;

    return true;
}

#else // macOS

#include "Core/macOS.hpp"

#include <cstdio>
#include <fstream>
#include <iterator>

Core::HostImage::HostImage(int aExePathDepth)
{
    m_base = Core::Platform::GetImageBase();

    // nullptr is the main executable: <game>/Cyberpunk2077.app/Contents/MacOS/Cyberpunk2077
    std::string filePath = Core::Platform::GetModuleFileName(nullptr);
    m_exe = filePath;
    m_root = m_exe.parent_path();

    while (--aExePathDepth >= 0)
        m_root = m_root.parent_path();

    TryResolveVersion(filePath);
}

bool Core::HostImage::TryResolveVersion(const std::string& filePath)
{
    // There is no file version resource in a Mach-O. The bundle's Info.plist (<app>/Contents/Info.plist, XML) carries
    // CFBundleShortVersionString, for example "2.3.1". A missing or binary plist leaves the version at 0.0.0.
    m_fileVer = {};
    m_productVer = {};

    const auto plistPath = std::filesystem::path(filePath).parent_path().parent_path() / "Info.plist";
    std::ifstream in(plistPath, std::ios::binary);
    if (!in)
        return false;

    const std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    const auto key = text.find("<key>CFBundleShortVersionString</key>");
    if (key == std::string::npos)
        return false;

    const auto open = text.find("<string>", key);
    const auto close = open == std::string::npos ? open : text.find("</string>", open);
    if (close == std::string::npos)
        return false;

    const auto version = text.substr(open + 8, close - open - 8);
    unsigned major = 0, minor = 0, patch = 0;
    if (std::sscanf(version.c_str(), "%u.%u.%u", &major, &minor, &patch) < 2)
        return false;

    m_fileVer.major = static_cast<uint16_t>(major);
    m_fileVer.minor = static_cast<uint16_t>(minor);
    m_fileVer.build = static_cast<uint16_t>(patch);
    m_fileVer.revision = 0;

    m_productVer.major = static_cast<uint16_t>(major);
    m_productVer.minor = static_cast<uint16_t>(minor);
    m_productVer.patch = patch;

    return true;
}

#endif // Platform

uintptr_t Core::HostImage::GetBase() const
{
    return m_base;
}

std::filesystem::path Core::HostImage::GetPath() const
{
    return m_exe;
}

std::string Core::HostImage::GetName() const
{
    return m_exe.stem().string();
}

std::filesystem::path Core::HostImage::GetRootDir() const
{
    return m_root;
}

const Core::FileVer& Core::HostImage::GetFileVer() const
{
    return m_fileVer;
}

const Core::SemvVer& Core::HostImage::GetProductVer() const
{
    return m_productVer;
}
