public native func CreateLocalizationString(value: String) -> LocalizationString
public native func ExtractLocalizationString(value: LocalizationString) -> String

public func ToLocalizationString(value: String) -> LocalizationString = CreateLocalizationString(value)
public func ToString(value: LocalizationString) -> String = ExtractLocalizationString(value)
