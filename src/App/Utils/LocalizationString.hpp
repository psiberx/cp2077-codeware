#pragma once

namespace App
{
Red::LocalizationString CreateLocalizationString(const Red::CString& aValue)
{
    return {0, aValue};
}

Red::CString ExtractLocalizationString(const Red::LocalizationString& aValue)
{
    return aValue.unk08;
}
}

RTTI_DEFINE_GLOBALS({
    RTTI_FUNCTION(App::CreateLocalizationString);
    RTTI_FUNCTION(App::ExtractLocalizationString);
});
