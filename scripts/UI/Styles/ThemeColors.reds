// -----------------------------------------------------------------------------
// Codeware.UI.ThemeColors
// -----------------------------------------------------------------------------
//
// NOTE: reference for base colors (should be replaced by ThemePicker /
// StylePicker). You should use BindProperty and main_colors.inkstyle to use
// game's engine colors when possible.
//

module Codeware.UI

public abstract class ThemeColors {
    public static func ElectricBlue() -> HDRColor = HDRColor(0.368627, 0.964706, 1.0, 1.0)
    public static func Bittersweet() -> HDRColor = HDRColor(1.1761, 0.3809, 0.3476, 1.0)
    public static func Dandelion() -> HDRColor = HDRColor(1.1192, 0.8441, 0.2565, 1.0)
    public static func LightGreen() -> HDRColor = HDRColor(0.113725, 0.929412, 0.513726, 1.0)
    public static func BlackPearl() -> HDRColor = HDRColor(0.054902, 0.054902, 0.090196, 1.0)

    public static func RedOxide() -> HDRColor = HDRColor(0.411765, 0.086275, 0.090196, 1.0)
    public static func Bordeaux() -> HDRColor = HDRColor(0.262745, 0.086275, 0.094118, 1.0)

    public static func PureBlack() -> HDRColor = HDRColor(0.0, 0.0, 0.0, 1.0)
    public static func PureWhite() -> HDRColor = HDRColor(1.0, 1.0, 1.0, 1.0)
}
