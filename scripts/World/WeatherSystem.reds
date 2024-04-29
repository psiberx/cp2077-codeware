@addMethod(WeatherSystem)
public native func SetWeather(weather: CName, opt blendTime: Float, opt priority: Uint32) -> Bool

@addMethod(WeatherSystem)
public native func ResetWeather(opt forceRestore: Bool, opt blendTime: Float) -> Bool

@addMethod(WeatherSystem)
public native func GetWeatherState() -> ref<worldWeatherState>

@addMethod(WeatherSystem)
public native func GetEnvironmentDefinition() -> ref<worldEnvironmentDefinition>
