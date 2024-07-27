#pragma once

namespace App
{
void Print(const Red::ScriptRef<Red::CString>& aText)
{
    Red::Log::Channel("DEBUG", *aText.ref);
}

void ModLog(Red::CName aMod, const Red::ScriptRef<Red::CString>& aText)
{
    Red::Log::Channel(aMod, *aText.ref);
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::Print);
    RTTI_FUNCTION(App::ModLog);
});
