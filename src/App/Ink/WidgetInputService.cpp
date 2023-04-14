#include "WidgetInputService.hpp"
#include "inkKeyInputEvent.hpp"

#include <winuser.h>

namespace
{
constexpr auto RawInputEventName = Red::CName("OnInputKey");

App::RawInputCallback s_callback;
}

void App::WidgetInputService::OnBootstrap()
{
    if (!HookBefore<Raw::inkSystem::ProcessCharacterEvent>(&OnInput))
        throw std::runtime_error("Failed to hook inkSystem::ProcessCharacterEvent.");
}

void App::WidgetInputService::OnShutdown()
{
    Unhook<Raw::inkSystem::ProcessCharacterEvent>();
}

void App::WidgetInputService::OnInput(Red::InkSystem* aSystem, Red::EInputKey aKey, Red::EInputAction aAction)
{
    if (aAction != Red::EInputAction::IACT_Axis)
    {
        if (s_callback)
        {
            s_callback(aSystem->keyboardState, aAction, aKey);
        }

        if (aSystem->inputWidget)
        {
            auto event = Red::MakeHandle<inkKeyInputEvent>(aSystem->keyboardState, aKey, aAction, ToCharacter(aKey));
            auto manager = Raw::inkWidget::EventManager(aSystem->inputWidget.instance);
            Raw::inkWidget::TriggerEvent(manager, RawInputEventName, event);
        }
    }
}

std::string App::WidgetInputService::ToCharacter(Red::EInputKey aKey)
{
    if (!IsCharacter(aKey))
        return {};

    BYTE keyboardState[256];
    GetKeyboardState(keyboardState);

    // if (keyboardState[static_cast<size_t>(Red::EInputKey::IK_LControl)]
    //     || keyboardState[static_cast<size_t>(Red::EInputKey::IK_RControl)])
    //     return {};

    WCHAR buffer[5]{};
    const auto size = ToUnicode(static_cast<UINT>(aKey), 0, keyboardState, buffer, 4, 0);

    if (size <= 0)
        return {};

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(buffer);
}

bool App::WidgetInputService::IsCharacter(Red::EInputKey aKey)
{
    return aKey == Red::EInputKey::IK_Space
        || (aKey >= Red::EInputKey::IK_0 && aKey <= Red::EInputKey::IK_9)
        || (aKey >= Red::EInputKey::IK_A && aKey <= Red::EInputKey::IK_Z)
        || (aKey >= Red::EInputKey::IK_NumPad0 && aKey <= Red::EInputKey::IK_NumSlash)
        || (aKey >= Red::EInputKey::IK_Semicolon && aKey <= Red::EInputKey::IK_Tilde)
        || (aKey >= Red::EInputKey::IK_LeftBracket && aKey <= Red::EInputKey::IK_SingleQuote);
}

void App::WidgetInputService::SetCallback(App::RawInputCallback aCallback)
{
    s_callback = aCallback;
}

void App::WidgetInputService::ClearCallback()
{
    s_callback = nullptr;
}
