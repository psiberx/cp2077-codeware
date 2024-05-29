#pragma once

namespace App
{
Red::CName HashToName(uint64_t aValue)
{
    return aValue;
}

uint64_t NameToHash(Red::CName aName)
{
    return aName;
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::HashToName);
    RTTI_FUNCTION(App::NameToHash);
});
