#pragma once

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <future>
#include <map>
#include <memory>
#include <ranges>
#include <source_location>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include <RED4ext/Api/EMainReason.hpp>
#include <RED4ext/Api/Sdk.hpp>
#include <RED4ext/Api/Runtime.hpp>
#include <RED4ext/Api/SemVer.hpp>
#include <RED4ext/Api/Version.hpp>

#include <RED4ext/CName.hpp>
#include <RED4ext/CNamePool.hpp>
#include <RED4ext/CString.hpp>
#include <RED4ext/Common.hpp>
#include <RED4ext/DynArray.hpp>
#include <RED4ext/GameApplication.hpp>
#include <RED4ext/GameEngine.hpp>
#include <RED4ext/Handle.hpp>
#include <RED4ext/HashMap.hpp>
#include <RED4ext/ISerializable.hpp>
#include <RED4ext/JobQueue.hpp>
#include <RED4ext/NativeTypes.hpp>
#include <RED4ext/Relocation.hpp>
#include <RED4ext/ResourceDepot.hpp>
#include <RED4ext/ResourceLoader.hpp>
#include <RED4ext/ResourcePath.hpp>
#include <RED4ext/RTTISystem.hpp>
#include <RED4ext/RTTITypes.hpp>
#include <RED4ext/SortedArray.hpp>
#include <RED4ext/TweakDB.hpp>
#include <RED4ext/Hashing/FNV1a.hpp>
#include <RED4ext/Memory/Allocators.hpp>
#include <RED4ext/Memory/SharedPtr.hpp>
#include <RED4ext/Scripting/CProperty.hpp>
#include <RED4ext/Scripting/IScriptable.hpp>
#include <RED4ext/Scripting/Natives/ScriptGameInstance.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/Entity.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/IComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ui/GameSystemUI.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/anim/Processor.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/CompoundWidget.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/ControllerProcessor.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/IEffect.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/Layer.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/LayerProxy.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/MultiChildren.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/PropertyManager.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/SpawningProcessor.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/StyleResourceWrapper.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/UserData.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/VirtualWindow.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/Widget.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WidgetLibraryItemInstance.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WidgetLibraryResource.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WidgetLogicController.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WidgetReference.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/IWidgetController.hpp>

#include <nameof.hpp>
#include <semver.hpp>

#include "Core/Raw.hpp"
#include "Core/Stl.hpp"

#include "Red/Alias.hpp"
#include "Red/Stl.hpp"
#include "Red/Rtti/Construction.hpp"
#include "Red/Rtti/Calling.hpp"
#include "Red/Rtti/Definition.hpp"
#include "Red/Rtti/Resolving.hpp"

#ifdef VERBOSE
#include "Red/Log.hpp"
#endif
