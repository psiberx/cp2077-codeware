#pragma once

namespace App
{
// The loaded mesh Handle of an entSkinnedMeshComponent. 0x200 on Windows. On Mac it is 0x1F8: clang puts the first member of the derived
// class into the tail padding of its base, so the whole derived part sits 8 lower (R21). Checked against the game by the code twin of the
// function that reads it (Windows 0x1B3B5C reads [this+0x200] and sets bit 3 of [this+0x25B]; the Mac twin 0xC7D688 reads [this+0x1F8]
// and sets bit 3 of [this+0x253]) and guarded at build time (macos/MacLayoutGuard.cpp).
#if defined(__APPLE__)
constexpr uint32_t SkinnedMeshHandleOffset = 0x200; // Mac 2.5.0: 0x200, as on Windows (2.3.1: 0x1F8; Mac 0x198FDA0 reads [this+0x200])
#else
constexpr uint32_t SkinnedMeshHandleOffset = 0x200;
#endif
}

RTTI_EXPAND_CLASS(Red::entSkinnedMeshComponent, {
    RTTI_PROPERTY(Red::Handle<Red::CMesh>, App::SkinnedMeshHandleOffset, "meshResource");
});
