#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

#include <string>

// C++ linkage. inkSystem.hpp declares these at global scope.

void cw_clipboard_get(std::string& aOut)
{
    @autoreleasepool
    {
        NSPasteboard* board = [NSPasteboard generalPasteboard];
        NSString* text = [board stringForType:NSPasteboardTypeString];
        if (text)
        {
            const char* utf8 = [text UTF8String];
            aOut.assign(utf8 ? utf8 : "");
        }
        else
        {
            aOut.clear();
        }
    }
}

void cw_clipboard_set(const char* aText)
{
    @autoreleasepool
    {
        NSPasteboard* board = [NSPasteboard generalPasteboard];
        [board clearContents];
        NSString* text = aText ? [NSString stringWithUTF8String:aText] : @"";
        [board setString:text forType:NSPasteboardTypeString];
    }
}
