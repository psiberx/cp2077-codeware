#pragma once

namespace App
{
Red::CRUID HashToCRUID(uint64_t aValue)
{
    return *reinterpret_cast<Red::CRUID*>(&aValue);
}

uint64_t CRUIDToHash(Red::CRUID aValue)
{
    return aValue.unk00;
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::HashToCRUID);
    RTTI_FUNCTION(App::CRUIDToHash);
});
