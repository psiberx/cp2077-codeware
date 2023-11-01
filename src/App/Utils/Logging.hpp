#pragma once

namespace App
{
void ModLog(Red::CName aMod, Red::ScriptRef<Red::CString>& aText)
{
    Red::Log::Channel("DEBUG", std::format("[{}] {}", aMod.ToString(), aText.ref->c_str()));
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::ModLog);
});
