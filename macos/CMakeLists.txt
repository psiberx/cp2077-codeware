cmake_minimum_required(VERSION 3.21)
# The version string is upstream's (xmake.lua set_version), so the Mac build reports what upstream's own build reports.
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/../xmake.lua" _upstream_xmake)
string(REGEX MATCH "set_version\\(\"([0-9]+\\.[0-9]+\\.[0-9]+)\"" _upstream_version "${_upstream_xmake}")
if(NOT CMAKE_MATCH_1)
    message(FATAL_ERROR "no set_version(\"x.y.z\") in ../xmake.lua")
endif()
project(Codeware VERSION ${CMAKE_MATCH_1} LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64")

if(NOT APPLE)
    message(FATAL_ERROR "This target builds the macOS Codeware dylib")
endif()

add_compile_definitions(RED4EXT_PLATFORM_MACOS)
add_compile_definitions(RED4EXT_USE_FRIDA_GADGET)
add_compile_definitions(RED4EXT_HEADER_ONLY)
add_compile_definitions(HOOKCHAIN_SELF=codeware)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")

# R17 B3. Built from this tree plus the macOS RED4ext SDK checkout (a sibling clone by default). Nothing from the
# TweakXL tree: lib/Core and lib/Support are Codeware's own, nameof and semver are Codeware's vendor checkouts.
set(CODEWARE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(RED4EXT_SDK_DIR "${CODEWARE_DIR}/../RED4ext.SDK-macos" CACHE PATH "macOS RED4ext SDK checkout")
set(SDK_INCLUDE "${RED4EXT_SDK_DIR}/include")

# Reproducible builds: no checkout path ends up in the dylib (__FILE__ in asserts and logs), so the same sources build to the same bytes
# from any directory.
get_filename_component(_repo_root "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)
get_filename_component(_sdk_root "${RED4EXT_SDK_DIR}" ABSOLUTE)
add_compile_options("-ffile-prefix-map=${_repo_root}=." "-ffile-prefix-map=${_sdk_root}=RED4ext.SDK-macos"
                    "-ffile-prefix-map=${CMAKE_BINARY_DIR}=build")

set(NAME "Codeware")
set(AUTHOR "psiberx")
set(VERSION "${PROJECT_VERSION}")
set(MODE "release")
set(DEBUG "")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/generated/App")
configure_file(
    "${CODEWARE_DIR}/config/Project.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/generated/App/Project.hpp"
)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

set(CODEWARE_SOURCES
    Main.cpp
    ../src/rtti.cpp
    MacSupport.cpp
    MacAddressResolver.cpp
    MacR13.cpp
    MacGameInstanceHook.cpp
    MacScriptValidator.cpp
    MacDiag.cpp
    MacHookChain.cpp
    MacTrap.cpp
    MacEngine.cpp
    MacR19.cpp
    MacR20.cpp
    MacR21.cpp
    MacR25.cpp
    MacR16a.cpp
    MacR16b.cpp
    MacR17.cpp
    MacCrashDiag.cpp
    MacScratchTail.cpp
    MacInstancedMeshGuard.cpp
    ArchiveXLScripts.cpp
    Clipboard.mm
    KeyTranslate.mm
    MacAutotest.mm
    MacAutotestDump.cpp
    ../src/App/Application.cpp
    ../src/App/Facade.cpp
    ../src/App/Callback/CallbackSystem.cpp
    ../src/App/Callback/CallbackSystemController.cpp
    ../src/App/Entity/EntityEx.cpp
    ../src/App/Scripting/ScriptableServiceContainer.cpp
    ../src/App/Scripting/ScriptingService.cpp
    ../src/App/Scripting/VanillaApiCompat.cpp
    ../src/App/Localization/LocalizationService.cpp
    ../src/App/Localization/Language.cpp
    ../src/App/Entity/PersistencyService.cpp
    ../src/App/Shared/ResourcePathRegistry.cpp
    ../src/App/World/OpenWorldTracker.cpp
    ../src/App/UI/WidgetSpawningService.cpp
    ../src/App/UI/WidgetInputService.cpp
    ../src/App/Entity/ComponentEx.cpp
    ../src/App/Entity/ComponentWrapper.cpp
    ../src/App/World/DynamicEntitySystem.cpp
    ../src/App/World/StaticEntitySystem.cpp
    ../src/App/World/OpenWorldSystem.cpp
    ../src/App/World/WeatherSystemEx.cpp
    ../src/App/World/WorldStateSystem.cpp
    ../src/App/World/CommunityWrapper.cpp
    ../src/App/World/PopulationSpawnerWrapper.cpp
    ../src/App/Quest/QuestPhaseRegistry.cpp
    ../src/App/UI/WidgetBuildingService.cpp
    ../src/Red/InkSystem.cpp
    ${CODEWARE_DIR}/lib/Core/Facades/Runtime.cpp
    ${CODEWARE_DIR}/lib/Core/Runtime/HostImage.cpp
    ${CODEWARE_DIR}/lib/Core/Runtime/ModuleImage.cpp
    ${CODEWARE_DIR}/lib/Core/Hooking/HookingAgent.cpp
    ${CODEWARE_DIR}/lib/Core/Hooking/HookingDriver.cpp
    ${CODEWARE_DIR}/lib/Core/Memory/AddressResolver.cpp
    ${CODEWARE_DIR}/lib/Core/Logging/LoggingAgent.cpp
    ${CODEWARE_DIR}/lib/Core/Logging/LoggingDriver.cpp
    ${CODEWARE_DIR}/lib/Core/Runtime/OwnerMutex.cpp
    ${CODEWARE_DIR}/lib/Core/Foundation/Application.cpp
    ${CODEWARE_DIR}/lib/Core/Foundation/RuntimeProvider.cpp
    ${CODEWARE_DIR}/lib/Support/RedLib/RedLibProvider.cpp
)

# R16a. SDK-internal address lookups (UniversalRelocFunc, for example CClass::GetProperty) resolve through the
# SDK's own Mac table in RED4ext/Relocation-inl.hpp, not through Codeware's MacAddressResolver. The vendored SDK
# (in the TweakXL fork) is not touched. The rows Codeware needs on top of its table live in MacSdkRows.inc and are
# injected into a generated copy of the header, which comes first on the include path.
set(SDK_RELOC "${SDK_INCLUDE}/RED4ext/Relocation-inl.hpp")
set(SDK_ROWS_INC "${CMAKE_CURRENT_SOURCE_DIR}/MacSdkRows.inc")
set(SDK_OVERLAY "${CMAKE_CURRENT_BINARY_DIR}/sdk-overlay")
file(READ "${SDK_RELOC}" SDK_RELOC_TEXT)
file(READ "${SDK_ROWS_INC}" SDK_ROWS_TEXT)
set(SDK_ROWS_MARKER "        { 4201325776, 0x109BAA8 },  // CGlobalFunction_ctor\n")
string(FIND "${SDK_RELOC_TEXT}" "${SDK_ROWS_MARKER}" SDK_ROWS_POS)
if(SDK_ROWS_POS EQUAL -1)
    message(FATAL_ERROR "R16a: the anchor row (CGlobalFunction_ctor) is not in ${SDK_RELOC}. Update the anchor in CMakeLists.txt.")
endif()
string(REPLACE "${SDK_ROWS_MARKER}" "${SDK_ROWS_MARKER}${SDK_ROWS_TEXT}" SDK_RELOC_TEXT "${SDK_RELOC_TEXT}")

# R17. An unmapped hash must not resolve to 0 (the caller would jump to null). Replace the unknown-hash tail of the Mac
# Resolve with a call to the trap table (macos/MacTrap.cpp): the returned stub logs once and returns zero.
set(SDK_TAIL_START "    // Address not found or placeholder - return a non-zero sentinel value")
set(SDK_TAIL_END "    return 0;\n#else\n    if constexpr (Detail::AddressResolverOverride<uint32_t>::value)")
string(FIND "${SDK_RELOC_TEXT}" "${SDK_TAIL_START}" SDK_TAIL_A)
string(FIND "${SDK_RELOC_TEXT}" "${SDK_TAIL_END}" SDK_TAIL_B)
if(SDK_TAIL_A EQUAL -1 OR SDK_TAIL_B EQUAL -1)
    message(FATAL_ERROR "R17: the unknown-hash tail of Resolve was not found in ${SDK_RELOC}. Update the anchors in CMakeLists.txt.")
endif()
string(SUBSTRING "${SDK_RELOC_TEXT}" 0 ${SDK_TAIL_A} SDK_HEAD)
math(EXPR SDK_REST_FROM "${SDK_TAIL_B} + 14")
string(SUBSTRING "${SDK_RELOC_TEXT}" ${SDK_REST_FROM} -1 SDK_REST)
set(SDK_RELOC_TEXT "${SDK_HEAD}    // R17: Codeware trap table. Logs on the first call of the returned stub, then returns 0.\n    return codeware_mac_trap_for_hash(aHash);\n${SDK_REST}")
set(SDK_DECL_MARKER "extern \"C\" uintptr_t tweakxl_class_vslot(uint32_t aByteOffset);\n")
string(FIND "${SDK_RELOC_TEXT}" "${SDK_DECL_MARKER}" SDK_DECL_POS)
if(SDK_DECL_POS EQUAL -1)
    message(FATAL_ERROR "R17: the extern declaration anchor was not found in ${SDK_RELOC}.")
endif()
string(REPLACE "${SDK_DECL_MARKER}" "${SDK_DECL_MARKER}extern \"C\" uintptr_t codeware_mac_trap_for_hash(uint32_t aHash);\n" SDK_RELOC_TEXT "${SDK_RELOC_TEXT}")
file(WRITE "${SDK_OVERLAY}/RED4ext/Relocation-inl.hpp" "${SDK_RELOC_TEXT}")
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${SDK_RELOC}" "${SDK_ROWS_INC}")
message(STATUS "R16a: SDK Mac table overlay written to ${SDK_OVERLAY}")

# 2.5: the generated layout guard asserts the Mac reflection-dump layouts. Leave it out (-DMAC_LAYOUT_GUARD=OFF) only for the build
# that takes a new reflection dump; regenerate it with tools/mac/gen-mac-layout.py and build with the guard again afterwards.
option(MAC_LAYOUT_GUARD "Build macos/MacLayoutGuard.cpp (generated layout asserts)" ON)

add_library(Codeware SHARED ${CODEWARE_SOURCES})
if(MAC_LAYOUT_GUARD)
    target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/MacLayoutGuard.cpp")
endif()

set_target_properties(Codeware PROPERTIES
    OUTPUT_NAME "Codeware"
    PREFIX ""
    SUFFIX ".dylib"
)

target_include_directories(Codeware PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${SDK_OVERLAY}"
    "${CMAKE_CURRENT_BINARY_DIR}/generated"
    "${CODEWARE_DIR}/lib"
    "${CODEWARE_DIR}/src"
    "${SDK_INCLUDE}"
    "${CODEWARE_DIR}/vendor/nameof/include"
    "${CODEWARE_DIR}/vendor/semver/include"
)

target_link_libraries(Codeware PRIVATE
    spdlog::spdlog
    fmt::fmt
    "-framework AppKit"
    "-framework ApplicationServices"
    "-framework Foundation"
)

target_precompile_headers(Codeware PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.hpp")
set_source_files_properties(Clipboard.mm KeyTranslate.mm MacAutotest.mm PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

target_compile_options(Codeware PRIVATE
    -fno-rtti
    -fexceptions
    -Wno-deprecated-declarations
    -fvisibility=hidden
    -fvisibility-inlines-hidden
)

# R14. The plugin folder carries vendored spdlog and fmt next to Codeware.dylib. Rewrite the Homebrew install
# names to @loader_path and re-sign. The script finds the names itself, so a Homebrew version bump still works.
add_custom_command(TARGET Codeware POST_BUILD
    COMMAND /bin/bash "${CMAKE_CURRENT_SOURCE_DIR}/fix-install-names.sh" "$<TARGET_FILE:Codeware>"
    VERBATIM
)

# R17 B3. Fail the build when a Codeware function is declared but not compiled in (the link flag above would hide it).
add_custom_command(TARGET Codeware POST_BUILD
    COMMAND /bin/bash "${CMAKE_CURRENT_SOURCE_DIR}/check-undefined.sh" "$<TARGET_FILE:Codeware>"
    VERBATIM
)

message(STATUS "Codeware ${PROJECT_VERSION} configured for macOS")
