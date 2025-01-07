public static native func CreateLocalizationString(value: String) -> LocalizationString
public static native func ExtractLocalizationString(value: LocalizationString) -> String

public static func ToLocalizationString(value: String) -> LocalizationString = CreateLocalizationString(value)
public static func ToString(value: LocalizationString) -> String = ExtractLocalizationString(value)
