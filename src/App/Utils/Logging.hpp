#pragma once

namespace App
{
void ModLog(Red::ScriptRef<Red::CString>& aText)
{
    Red::Log::Channel("DEBUG", aText.ref->c_str());
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::ModLog);
});
