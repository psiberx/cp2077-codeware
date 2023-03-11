#pragma once

namespace App
{
uint64_t NameToHash(Red::CName aName)
{
    return aName.hash;
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::NameToHash);
});
