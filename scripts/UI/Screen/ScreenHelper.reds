module Codeware.UI

public abstract class ScreenHelper {
    public static func GetResolution(game: GameInstance) -> String {
        let settings = GameInstance.GetSettingsSystem(game);
        let configVar = settings.GetVar(n"/video/display", n"Resolution") as ConfigVarListString;

        return configVar.GetValue();
    }

    public static func GetScreenSize(game: GameInstance) -> Vector2 {
        let resolution = ScreenHelper.GetResolution(game);
        let dimensions = StrSplit(resolution, "x");

        return Vector2(StringToFloat(dimensions[0]), StringToFloat(dimensions[1]));
    }
}
