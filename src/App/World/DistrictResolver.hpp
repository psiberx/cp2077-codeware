#pragma once

namespace App
{
struct DistrictResolver
{
    inline static Red::gamedataDistrict GetDistrict(Red::CName aName)
    {
        if (!aName)
            return Red::gamedataDistrict::Invalid;

        auto key = Red::FNV1a64(reinterpret_cast<const uint8_t*>(aName.ToString() + 3), 7);
        auto it = s_districtMap.find(key);

        if (it == s_districtMap.end())
            return Red::gamedataDistrict::Invalid;

        return it.value();
    }

    inline static Red::gamedataDistrict GetArea(Red::CName aName)
    {
        if (!aName)
            return Red::gamedataDistrict::Invalid;

        auto key = Red::FNV1a64(reinterpret_cast<const uint8_t*>(aName.ToString() + 3), 7);
        auto it = s_areaMap.find(key);

        if (it == s_areaMap.end())
            return Red::gamedataDistrict::Invalid;

        return it.value();
    }

    inline static Core::Map<Red::CName, Red::gamedataDistrict> s_districtMap = {
        {"bls_ina", Red::gamedataDistrict::Badlands},
        {"cct_cpz", Red::gamedataDistrict::CorpoPlaza},
        {"cct_dtn", Red::gamedataDistrict::Downtown},
        {"hey_gle", Red::gamedataDistrict::Glen},
        {"hey_rey", Red::gamedataDistrict::VistaDelRey},
        {"hey_spr", Red::gamedataDistrict::Wellsprings},
        {"pac_cvi", Red::gamedataDistrict::Coastview},
        {"pac_wwd", Red::gamedataDistrict::WestWindEstate},
        {"std_arr", Red::gamedataDistrict::Arroyo},
        {"std_rcr", Red::gamedataDistrict::RanchoCoronado},
        {"wat_kab", Red::gamedataDistrict::Kabuki},
        {"wat_lch", Red::gamedataDistrict::LittleChina},
        {"wat_nid", Red::gamedataDistrict::Northside},
        {"wbr_hil", Red::gamedataDistrict::CharterHill},
        {"wbr_jpn", Red::gamedataDistrict::JapanTown},
        {"wbr_nok", Red::gamedataDistrict::NorthOaks},
    };

    inline static Core::Map<Red::CName, Red::gamedataDistrict> s_areaMap = {
        {"bls_ina", Red::gamedataDistrict::Badlands},
        {"cct_cpz", Red::gamedataDistrict::CityCenter},
        {"cct_dtn", Red::gamedataDistrict::CityCenter},
        {"hey_gle", Red::gamedataDistrict::Heywood},
        {"hey_rey", Red::gamedataDistrict::Heywood},
        {"hey_spr", Red::gamedataDistrict::Heywood},
        {"pac_cvi", Red::gamedataDistrict::Pacifica},
        {"pac_wwd", Red::gamedataDistrict::Pacifica},
        {"std_arr", Red::gamedataDistrict::SantoDomingo},
        {"std_rcr", Red::gamedataDistrict::SantoDomingo},
        {"wat_kab", Red::gamedataDistrict::Watson},
        {"wat_lch", Red::gamedataDistrict::Watson},
        {"wat_nid", Red::gamedataDistrict::Watson},
        {"wbr_hil", Red::gamedataDistrict::Westbrook},
        {"wbr_jpn", Red::gamedataDistrict::Westbrook},
        {"wbr_nok", Red::gamedataDistrict::Westbrook},
    };
};
}