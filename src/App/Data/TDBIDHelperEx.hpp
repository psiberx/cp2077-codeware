#pragma once

namespace App
{
struct gamedataTDBIDHelperEx : Red::gamedataTDBIDHelper
{
    static Red::TweakDBID FromNumber(uint64_t aHash)
    {
        return {aHash};
    }
};
}

RTTI_EXPAND_CLASS(Red::gamedataTDBIDHelper, App::gamedataTDBIDHelperEx, {
    RTTI_ALIAS("TDBID");

    RTTI_METHOD(FromNumber);
});
