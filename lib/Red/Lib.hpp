#pragma once

#include <concepts>
#include <cstdint>
#include <functional>
#include <format>
#include <source_location>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include <RED4ext/GameEngine.hpp>
#include <RED4ext/RTTISystem.hpp>
#include <RED4ext/Scripting/Natives/ScriptGameInstance.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/IGameSystem.hpp>

#include "Alias.hpp"
#include "Framework.hpp"
#include "LogChannel.hpp"
#include "Rtti/Construction.hpp"
#include "Rtti/Definition.hpp"
#include "Rtti/Invocation.hpp"
#include "Rtti/Registrar.hpp"
#include "Rtti/Resolving.hpp"
#include "Specializations.hpp"
