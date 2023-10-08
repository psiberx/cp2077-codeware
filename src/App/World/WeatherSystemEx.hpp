#pragma once

namespace App
{
struct WeatherSystemEx : Red::WeatherSystem
{
    bool SetWeather(Red::CName aWeather, Red::Optional<float> aBlendTime, Red::Optional<uint32_t> aPriority);
    bool ResetWeather(Red::Optional<bool> aForceRestore);
};
}

RTTI_EXPAND_CLASS(Red::WeatherSystem, App::WeatherSystemEx, {
    RTTI_METHOD(SetWeather);
    RTTI_METHOD(ResetWeather);
});
