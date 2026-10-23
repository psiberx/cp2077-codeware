#pragma once

// Patch 2.5 added native game types with the same names as these Codeware types,
// so Codeware registers its own under prefixed names.

namespace App
{
class CallbackSystem;
struct CallbackSystemEvent;
struct CallbackSystemHandler;
struct CallbackSystemTarget;
struct GameSessionEvent;
struct ResourceEvent;
struct InputTarget;
struct ResourceTarget;
struct ScriptableService;
struct ScriptableServiceContainer;
struct inkKeyInputEvent;
struct inkLayerWrapper;
struct KeyInputEvent;
}

RTTI_MAP_TYPE_NAME(App::CallbackSystem, "CodewareCallbackSystem");
RTTI_MAP_TYPE_NAME(App::CallbackSystemEvent, "CodewareCallbackSystemEvent");
RTTI_MAP_TYPE_NAME(App::CallbackSystemHandler, "CodewareCallbackSystemHandler");
RTTI_MAP_TYPE_NAME(App::CallbackSystemTarget, "CodewareCallbackSystemTarget");
RTTI_MAP_TYPE_NAME(App::GameSessionEvent, "CodewareGameSessionEvent");
RTTI_MAP_TYPE_NAME(App::ResourceEvent, "CodewareResourceEvent");
RTTI_MAP_TYPE_NAME(App::InputTarget, "CodewareInputTarget");
RTTI_MAP_TYPE_NAME(App::ResourceTarget, "CodewareResourceTarget");
RTTI_MAP_TYPE_NAME(App::ScriptableService, "CodewareScriptableService");
RTTI_MAP_TYPE_NAME(App::ScriptableServiceContainer, "CodewareScriptableServiceContainer");
RTTI_MAP_TYPE_NAME(App::inkKeyInputEvent, "CodewareInkKeyInputEvent");
RTTI_MAP_TYPE_NAME(App::inkLayerWrapper, "CodewareInkLayerWrapper");
RTTI_MAP_TYPE_NAME(App::KeyInputEvent, "CodewareKeyInputEvent");
