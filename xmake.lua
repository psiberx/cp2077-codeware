set_xmakever("2.5.9")

set_project("Codeware")
set_version("1.17.0", {build = "%y%m%d%H%M"})

set_arch("x64")
set_languages("cxx2a")
add_cxxflags("/MP /GR- /EHsc")

if is_mode("debug") then
    set_symbols("debug")
    set_optimize("none")
    add_cxxflags("/Od /Ob0 /Zi /RTC1 /bigobj")
elseif is_mode("release") then
    set_symbols("hidden")
    set_strip("all")
    set_optimize("fastest")
    add_cxxflags("/Ob2")
elseif is_mode("releasedbg") then
    set_symbols("debug")
    set_strip("all")
    set_optimize("fastest")
    add_cxxflags("/Ob1 /Zi")
end

if is_mode("debug") then
    set_runtimes("MDd")
else
    set_runtimes("MD")
end

add_requires("hopscotch-map", "minhook", "spdlog", "tiltedcore")

target("Codeware")
    set_default(true)
    set_kind("shared")
    set_filename("Codeware.dll")
    set_pcxxheader("src/pch.hpp")
    add_files("src/**.cpp", "src/**.rc", "lib/**.cpp")
    add_headerfiles("src/**.hpp", "lib/**.hpp")
    add_includedirs("src/", "lib/")
    add_deps("RED4ext.SDK", "clip", "nameof", "semver", "wil")
    add_packages("hopscotch-map", "minhook", "spdlog", "tiltedcore")
    add_syslinks("Version", "User32")
    add_defines("WINVER=0x0601", "WIN32_LEAN_AND_MEAN", "NOMINMAX")
    set_configdir("src")
    add_configfiles("config/Project.hpp.in", {prefixdir = "App"})
    add_configfiles("config/Version.rc.in", {prefixdir = "App"})
    set_configvar("AUTHOR", "psiberx")
    set_configvar("NAME", "Codeware")

target("RED4ext.SDK")
    set_default(false)
    set_kind("static")
    set_group("vendor")
    add_headerfiles("vendor/RED4ext.SDK/include/**.hpp")
    add_includedirs("vendor/RED4ext.SDK/include/", { public = true })

target("clip")
    set_default(false)
    set_kind("static")
    set_group("vendor")
    add_files("vendor/clip/clip.cpp", "vendor/clip/clip_win.cpp")
    add_headerfiles("vendor/clip/*.h")
    add_includedirs("vendor/clip/", { public = true })

target("nameof")
    set_default(false)
    set_kind("static")
    set_group("vendor")
    add_headerfiles("vendor/nameof/include/**.hpp")
    add_includedirs("vendor/nameof/include/", { public = true })

target("semver")
    set_default(false)
    set_kind("static")
    set_group("vendor")
    add_headerfiles("vendor/semver/include/**.hpp")
    add_includedirs("vendor/semver/include/", { public = true })

target("wil")
    set_default(false)
    set_kind("static")
    set_group("vendor")
    add_headerfiles("vendor/wil/include/**.h")
    add_includedirs("vendor/wil/include/", { public = true })

add_rules("plugin.vsxmake.autoupdate")
