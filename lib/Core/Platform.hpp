#pragma once

// Platform-specific includes and definitions

#if defined(_WIN32) || defined(_WIN64)
    #include "Core/Win.hpp"
#else
    #include "Core/macOS.hpp"
#endif
