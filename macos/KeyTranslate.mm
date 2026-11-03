#import <ApplicationServices/ApplicationServices.h>
#import <Foundation/Foundation.h>

#include <cstdint>
#include <string>

// R20. EInputKey (Windows virtual-key codes) to the text the key types now, for WidgetInputService::ToCharacter. Windows uses
// ToUnicode with the keyboard state. Here: the virtual key becomes a macOS ANSI key code, a synthetic key event gets the
// current Shift, Caps Lock and Option state, and CGEventKeyboardGetUnicodeString gives the character the active layout
// produces (thread safe, no TIS calls, which must run on the main thread). Empty when Command or Control is down, so that
// shortcuts do not type. A US layout table is the fallback when the event gives no string.

namespace
{
int MacKeyCode(int aVirtualKey)
{
    static const int letters[26] = {0x00, 0x0B, 0x08, 0x02, 0x0E, 0x03, 0x05, 0x04, 0x22, 0x26, 0x28, 0x25, 0x2E,
                                    0x2D, 0x1F, 0x23, 0x0C, 0x0F, 0x01, 0x11, 0x20, 0x09, 0x0D, 0x07, 0x10, 0x06};
    static const int digits[10] = {0x1D, 0x12, 0x13, 0x14, 0x15, 0x17, 0x16, 0x1A, 0x1C, 0x19};
    static const int numpad[10] = {0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5B, 0x5C};

    if (aVirtualKey >= 'A' && aVirtualKey <= 'Z')
        return letters[aVirtualKey - 'A'];
    if (aVirtualKey >= '0' && aVirtualKey <= '9')
        return digits[aVirtualKey - '0'];
    if (aVirtualKey >= 96 && aVirtualKey <= 105) // IK_NumPad0..9
        return numpad[aVirtualKey - 96];

    switch (aVirtualKey)
    {
    case 32: return 0x31;  // IK_Space
    case 106: return 0x43; // IK_NumStar
    case 107: return 0x45; // IK_NumPlus
    case 109: return 0x4E; // IK_NumMinus
    case 110: return 0x41; // IK_NumPeriod
    case 111: return 0x4B; // IK_NumSlash
    case 186: return 0x29; // IK_Semicolon
    case 187: return 0x18; // IK_Equals
    case 188: return 0x2B; // IK_Comma
    case 189: return 0x1B; // IK_Minus
    case 190: return 0x2F; // IK_Period
    case 191: return 0x2C; // IK_Slash
    case 192: return 0x32; // IK_Tilde (grave)
    case 219: return 0x21; // IK_LeftBracket
    case 220: return 0x2A; // IK_Backslash
    case 221: return 0x1E; // IK_RightBracket
    case 222: return 0x27; // IK_SingleQuote
    default: return -1;
    }
}

// US layout fallback: {plain, shifted}.
const char* UsText(int aVirtualKey, bool aShift)
{
    static const char* const shiftedDigits = ")!@#$%^&*(";
    static char buf[2] = {0, 0};

    if (aVirtualKey >= 'A' && aVirtualKey <= 'Z')
    {
        buf[0] = static_cast<char>(aShift ? aVirtualKey : aVirtualKey + 32);
        return buf;
    }
    if (aVirtualKey >= '0' && aVirtualKey <= '9')
    {
        buf[0] = aShift ? shiftedDigits[aVirtualKey - '0'] : static_cast<char>(aVirtualKey);
        return buf;
    }
    if (aVirtualKey >= 96 && aVirtualKey <= 105)
    {
        buf[0] = static_cast<char>('0' + (aVirtualKey - 96));
        return buf;
    }
    switch (aVirtualKey)
    {
    case 32: return " ";
    case 106: return "*";
    case 107: return "+";
    case 109: return "-";
    case 110: return ".";
    case 111: return "/";
    case 186: return aShift ? ":" : ";";
    case 187: return aShift ? "+" : "=";
    case 188: return aShift ? "<" : ",";
    case 189: return aShift ? "_" : "-";
    case 190: return aShift ? ">" : ".";
    case 191: return aShift ? "?" : "/";
    case 192: return aShift ? "~" : "`";
    case 219: return aShift ? "{" : "[";
    case 220: return aShift ? "|" : "\\";
    case 221: return aShift ? "}" : "]";
    case 222: return aShift ? "\"" : "'";
    default: return "";
    }
}
}

// C++ linkage. WidgetInputService.cpp declares it at global scope.
std::string cw_key_to_text(int aVirtualKey)
{
    @autoreleasepool
    {
        const CGEventFlags state = CGEventSourceFlagsState(kCGEventSourceStateCombinedSessionState);
        if (state & (kCGEventFlagMaskCommand | kCGEventFlagMaskControl))
            return {};

        const bool shift = (state & kCGEventFlagMaskShift) != 0;
        const int keyCode = MacKeyCode(aVirtualKey);
        if (keyCode < 0)
            return {};

        std::string text;
        if (CGEventRef event = CGEventCreateKeyboardEvent(nullptr, static_cast<CGKeyCode>(keyCode), true))
        {
            CGEventSetFlags(event, state & (kCGEventFlagMaskShift | kCGEventFlagMaskAlphaShift | kCGEventFlagMaskAlternate));
            UniChar chars[8] = {};
            UniCharCount length = 0;
            CGEventKeyboardGetUnicodeString(event, 8, &length, chars);
            CFRelease(event);
            if (length > 0 && chars[0] >= 0x20)
            {
                NSString* string = [NSString stringWithCharacters:chars length:length];
                const char* utf8 = [string UTF8String];
                if (utf8)
                    text = utf8;
            }
        }

        if (text.empty())
            text = UsText(aVirtualKey, shift);
        return text;
    }
}
