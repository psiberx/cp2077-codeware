#include "OwnerMutex.hpp"

#if !defined(_WIN32) && !defined(_WIN64)
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#endif

Core::OwnerMutex::OwnerMutex(std::string_view aName)
    : m_aname(aName)
    , m_mutex(nullptr)
#ifndef _WIN32
    , m_fd(-1)
#endif
{
}

Core::OwnerMutex::OwnerMutex(std::wstring_view aName)
    : m_wname(aName)
    , m_mutex(nullptr)
#ifndef _WIN32
    , m_fd(-1)
#endif
{
}

Core::OwnerMutex::~OwnerMutex()
{
    Release();
}

bool Core::OwnerMutex::Obtain()
{
#if defined(_WIN32) || defined(_WIN64)
    const auto mutex = !m_wname.empty()
        ? CreateMutexW(NULL, TRUE, m_wname.data())
        : CreateMutexA(NULL, TRUE, m_aname.data());

    if (!mutex)
        return false;

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        ReleaseMutex(mutex);
        return false;
    }

    m_mutex = mutex;

    return true;
#else
    // macOS: a file lock in /tmp stands in for the named mutex
    std::string lockPath = "/tmp/codeware_";
    lockPath += m_aname.empty() ? "default" : m_aname;
    lockPath += ".lock";
    
    m_fd = open(lockPath.c_str(), O_CREAT | O_RDWR, 0666);
    if (m_fd < 0)
        return false;
    
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    
    if (fcntl(m_fd, F_SETLK, &fl) < 0)
    {
        close(m_fd);
        m_fd = -1;
        return false;
    }
    
    m_mutex = reinterpret_cast<void*>(static_cast<intptr_t>(1)); // Mark as owned
    return true;
#endif
}

bool Core::OwnerMutex::Release()
{
    if (!m_mutex)
        return false;

#if defined(_WIN32) || defined(_WIN64)
    ReleaseMutex(m_mutex);
#else
    if (m_fd >= 0)
    {
        struct flock fl;
        fl.l_type = F_UNLCK;
        fl.l_whence = SEEK_SET;
        fl.l_start = 0;
        fl.l_len = 0;
        fcntl(m_fd, F_SETLK, &fl);
        close(m_fd);
        m_fd = -1;
    }
#endif
    m_mutex = nullptr;

    return true;
}

bool Core::OwnerMutex::IsOwner()
{
    return m_mutex;
}
