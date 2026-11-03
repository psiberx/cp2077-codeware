#include "MacDiag.hpp"

#include <cstdlib>
#include <cstring>

bool Mac::DiagEnabled()
{
    static const bool s_enabled = [] {
        const char* value = std::getenv("CODEWARE_MAC_DIAG");
        return value && std::strcmp(value, "1") == 0;
    }();
    return s_enabled;
}
