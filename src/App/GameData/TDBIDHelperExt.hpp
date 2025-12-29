#pragma once

namespace App
{
struct gamedataTDBIDHelperExt : Red::gamedataTDBIDHelper
{
    static Red::TweakDBID FromNumber(uint64_t aHash)
    {
        return {aHash};
    }
};
}

RTTI_EXPAND_CLASS(Red::gamedataTDBIDHelper, App::gamedataTDBIDHelperExt, {
    RTTI_METHOD(FromNumber);
});
