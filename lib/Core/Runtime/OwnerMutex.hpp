#pragma once

#include "Core/Platform.hpp"

namespace Core
{
class OwnerMutex
{
public:
    explicit OwnerMutex(std::string_view aName);
    explicit OwnerMutex(std::wstring_view aName);
    ~OwnerMutex();

    bool Obtain();
    bool Release();
    bool IsOwner();

private:
    std::string_view m_aname;
    std::wstring_view m_wname;
#if defined(_WIN32) || defined(_WIN64)
    HANDLE m_mutex;
#else
    void* m_mutex;
    int m_fd;
#endif
};
}
