// R27. TEST-ONLY key injection for the unattended in-world runs (tools/autotest in ~/repos/cp2077-mac). Not a feature: it is not part of Codeware,
// it is left out of anything user-facing, and it does nothing unless the environment has CP2077_AUTOTEST=1, which only tools/autotest/run.sh sets
// (a default session or launch_modded.sh never has it, and no script of a default cache declares the native).
//
// The start screen and the "press to continue" prompt after a load wait for a key, and no script API advances them. This hands a key event for the
// game's own window to the game's own GameView (-[GameView keyDown:] / keyUp:, the entry the game's windowing uses), on the main thread, inside the
// process. No other process is involved: no CGEventPostToPid, no macOS permission, no OS focus change, nothing that reaches the owner's keyboard.
// The GameView ignores keys until the engine believes its window has focus, which it gets from the window becoming key. Launched from a script the
// game is not the active app, so once per run this sends the game's own windowDidBecomeKey: handlers (the window delegate and the window controller)
// the notification, as jackmaxwil/RED4ext-macos does in its background mode (src/dll/Platform/Background.cpp, MIT; that file is also where the idea of
// calling -[GameView keyDown:] with a synthetic event comes from). Reached from script as CodewareMacSelfTest.PostKey.
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#import <objc/message.h>
#import <objc/runtime.h>

#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace
{
bool Enabled()
{
    const char* flag = std::getenv("CP2077_AUTOTEST");
    return flag && std::strcmp(flag, "1") == 0;
}

NSView* FindGameView()
{
    Class gameViewClass = NSClassFromString(@"GameView");
    if (!gameViewClass)
    {
        return nil;
    }
    for (NSWindow* window in [NSApp windows])
    {
        NSView* view = [window contentView];
        if (view && [view isKindOfClass:gameViewClass])
        {
            return view;
        }
    }
    return nil;
}

NSEvent* MakeKey(NSEventType aType, NSWindow* aWindow, int aKeyCode, NSString* aChars)
{
    return [NSEvent keyEventWithType:aType
                            location:NSZeroPoint
                       modifierFlags:0
                           timestamp:[[NSProcessInfo processInfo] systemUptime]
                        windowNumber:[aWindow windowNumber]
                             context:nil
                          characters:aChars
         charactersIgnoringModifiers:aChars
                           isARepeat:NO
                             keyCode:static_cast<unsigned short>(aKeyCode)];
}

void Send(id aObject, SEL aSelector, id aArg)
{
    ((void (*)(id, SEL, id))objc_msgSend)(aObject, aSelector, aArg);
}

// Runs on the main thread.
void Deliver(int aKeyCode, int aHoldMs)
{
    @autoreleasepool
    {
        NSView* view = FindGameView();
        if (!view)
        {
            std::fprintf(stderr, "[autotest] {\"event\":\"KEY_DELIVERY\",\"key\":%d,\"delivered\":false,\"why\":\"no GameView window\"}\n", aKeyCode);
            return;
        }
        NSWindow* window = [view window];
        static bool focused = false;
        if (!focused)
        {
            focused = true;
            id delegate = [window delegate];
            SEL controllerSel = NSSelectorFromString(@"m_windowController");
            id controller = [view respondsToSelector:controllerSel] ? ((id (*)(id, SEL))objc_msgSend)(view, controllerSel) : nil;
            SEL becomeKey = NSSelectorFromString(@"windowDidBecomeKey:");
            if (delegate && [delegate respondsToSelector:becomeKey])
            {
                Send(delegate, becomeKey, nil);
            }
            if (controller && [controller respondsToSelector:becomeKey])
            {
                Send(controller, becomeKey, nil);
            }
            std::fprintf(stderr, "[autotest] {\"event\":\"KEY_FOCUS\",\"note\":\"windowDidBecomeKey: sent to the game's own handlers\",\"appActive\":%d,\"windowKey\":%d,\"delegate\":%d,\"controller\":%d}\n",
                         [NSApp isActive] ? 1 : 0, [window isKeyWindow] ? 1 : 0, delegate ? 1 : 0, controller ? 1 : 0);
        }
        NSString* chars = aKeyCode == 49 ? @" " : @"";
        Send(view, @selector(keyDown:), MakeKey(NSEventTypeKeyDown, window, aKeyCode, chars));
        std::fprintf(stderr, "[autotest] {\"event\":\"KEY_DELIVERY\",\"key\":%d,\"delivered\":true,\"mainThread\":%d}\n", aKeyCode, [NSThread isMainThread] ? 1 : 0);
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, static_cast<int64_t>(aHoldMs) * NSEC_PER_MSEC), dispatch_get_main_queue(), ^{
            @autoreleasepool
            {
                NSView* again = FindGameView();
                if (again)
                {
                    Send(again, @selector(keyUp:), MakeKey(NSEventTypeKeyUp, [again window], aKeyCode, chars));
                }
            }
        });
    }
}
} // namespace

namespace
{
std::atomic<uint32_t> g_keySeries{0}; // generation; a new series or a stop moves it on and ends the running one

void ScheduleSeries(uint32_t aGeneration, int aKeyCode, int aIntervalMs, int aRemaining)
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, static_cast<int64_t>(aIntervalMs) * NSEC_PER_MSEC), dispatch_get_main_queue(), ^{
        if (g_keySeries.load() != aGeneration || aRemaining <= 0)
        {
            return;
        }
        Deliver(aKeyCode, 90);
        ScheduleSeries(aGeneration, aKeyCode, aIntervalMs, aRemaining - 1);
    });
}
} // namespace

// Called once at the plugin's load. One line says whether the test hook is on.
extern "C" void cw_autotest_log_registration()
{
    if (Enabled())
    {
        std::fprintf(stderr, "[selftest] R27 test-only key injection registered (CP2077_AUTOTEST=1)\n");
        // R31 prep (test sessions only). macOS throttles an app whose window is covered by another app (App Nap / occlusion): in run
        // 20261009-160056 the game's per-frame input hook ran 93 times in 50 s instead of about 1,600, the start screen never advanced and the run
        // timed out. An activity assertion for the life of the process keeps the game at full speed while it runs behind the owner's windows. It
        // changes no setting and does not take focus; the process ends with the session.
        static id activity = nil;
        if (!activity)
        {
            @autoreleasepool
            {
                // Manual reference counting in this file (no -fobjc-arc): keep the token alive for the life of the process.
                activity = [[[NSProcessInfo processInfo] beginActivityWithOptions:(NSActivityUserInitiated | NSActivityLatencyCritical)
                                                                       reason:@"autotest"] retain];
            }
            std::fprintf(stderr, "[selftest] R31 autotest activity assertion begun (NSActivityUserInitiated | NSActivityLatencyCritical): %s\n",
                         activity ? "ok" : "FAILED");
        }
    }
}

// Returns 1 when a key press was queued for the main thread, 0 when the test hook is off.
extern "C" int cw_autotest_post_key(int aKeyCode, int aHoldMs)
{
    if (!Enabled())
    {
        return 0;
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        Deliver(aKeyCode, aHoldMs);
    });
    return 1;
}

// A series of presses, for the loading screen: the game's script time does not run while a save loads, so the driver cannot press from script timers
// there. Presses the key every aIntervalMs milliseconds, aCount times, on the main thread, until cw_autotest_stop_keys. Returns 1 when started.
extern "C" int cw_autotest_key_series(int aKeyCode, int aIntervalMs, int aCount)
{
    if (!Enabled())
    {
        return 0;
    }
    const uint32_t generation = g_keySeries.fetch_add(1) + 1;
    ScheduleSeries(generation, aKeyCode, aIntervalMs, aCount);
    return 1;
}

extern "C" void cw_autotest_stop_keys()
{
    if (Enabled())
    {
        g_keySeries.fetch_add(1);
    }
}
