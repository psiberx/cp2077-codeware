#include "Language.hpp"

Red::CName App::Language::ResolveFromTextResource(Red::ResourcePath aPath)
{
    static Core::Map<Red::ResourcePath, Red::CName> s_codes {
        { R"(base\localization\ar-ar\onscreens\onscreens.json)", "ar-ar" },
        { R"(base\localization\cz-cz\onscreens\onscreens.json)", "cz-cz" },
        { R"(base\localization\db-db\onscreens\onscreens.json)", "db-db" },
        { R"(base\localization\de-de\onscreens\onscreens.json)", "de-de" },
        { R"(base\localization\en-us\onscreens\onscreens.json)", "en-us" },
        { R"(base\localization\es-es\onscreens\onscreens.json)", "es-es" },
        { R"(base\localization\es-mx\onscreens\onscreens.json)", "es-mx" },
        { R"(base\localization\fr-fr\onscreens\onscreens.json)", "fr-fr" },
        { R"(base\localization\hu-hu\onscreens\onscreens.json)", "hu-hu" },
        { R"(base\localization\it-it\onscreens\onscreens.json)", "it-it" },
        { R"(base\localization\jp-jp\onscreens\onscreens.json)", "jp-jp" },
        { R"(base\localization\kr-kr\onscreens\onscreens.json)", "kr-kr" },
        { R"(base\localization\pl-pl\onscreens\onscreens.json)", "pl-pl" },
        { R"(base\localization\pt-br\onscreens\onscreens.json)", "pt-br" },
        { R"(base\localization\ru-ru\onscreens\onscreens.json)", "ru-ru" },
        { R"(base\localization\th-th\onscreens\onscreens.json)", "th-th" },
        { R"(base\localization\tr-tr\onscreens\onscreens.json)", "tr-tr" },
        { R"(base\localization\ua-ua\onscreens\onscreens.json)", "ua-ua" },
        { R"(base\localization\zh-cn\onscreens\onscreens.json)", "zh-cn" },
        { R"(base\localization\zh-tw\onscreens\onscreens.json)", "zh-tw" },
    };

    const auto& it = s_codes.find(aPath);

    if (it == s_codes.end())
        return {};

    return it.value();
}
