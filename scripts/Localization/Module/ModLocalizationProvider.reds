// -----------------------------------------------------------------------------
// Codeware.Localization.ModLocalizationProvider
// -----------------------------------------------------------------------------
//
// Purpose:
// - Resolve packages by language code
// - Define logic on locale and gender changes
//
// Supported language codes:
// - pl-pl (Polish)
// - en-us (English)
// - es-es (Spanish)
// - fr-fr (French)
// - it-it (Italian)
// - de-de (German)
// - es-mx (Latin American Spanish)
// - kr-kr (Korean)
// - zh-cn (Simplified Chinese)
// - ru-ru (Russian)
// - pt-br (Brazilian Portuguese)
// - jp-jp (Japanese)
// - zh-tw (Traditional Chinese)
// - ar-ar (Arabic)
// - cz-cz (Czech)
// - hu-hu (Hungarian)
// - tr-tr (Turkish)
// - th-th (Thai)
//
// -----------------------------------------------------------------------------
//
// public abstract class ModLocalizationProvider extends ScriptableSystem {
//   public func GetPackage(language: CName) -> ref<ModLocalizationPackage>
//   public func GetFallback() -> CName
//   public func OnLocaleChange()
//   public func OnGenderChange()
// }
//

module Codeware.Localization

public abstract class ModLocalizationProvider extends ScriptableSystem {
    protected func OnAttach() {
        GameInstance.GetScriptableSystemsContainer(this.GetGameInstance())
            .QueueRequest(RegisterProviderRequest.Create(this));
    }

    public func GetPackage(language: CName) -> ref<ModLocalizationPackage>

    public func GetFallback() -> CName

    public func OnLocaleChange()

    public func OnGenderChange()

    public func GetOnScreenEntries(language: CName, out entries: array<localizationPersistenceOnScreenEntry>) {
        let packages: array<ref<ModLocalizationPackage>>;

        let fallback = this.GetFallback();
        if NotEquals(language, fallback) {
            let fallbackPackage = this.GetPackage(fallback);
            if IsDefined(fallbackPackage) {
                ArrayPush(packages, fallbackPackage);
            }
        }

        let mainPackage = this.GetPackage(language);
        if IsDefined(mainPackage) {
            ArrayPush(packages, mainPackage);
        }

        for package in packages {
            let values: array<wref<IScriptable>>;
            package.GetEntries(EntryType.Interface).GetValues(values);

            for value in values {
                let entry = value as LocalizationEntry;
                ArrayPush(entries, new localizationPersistenceOnScreenEntry(
                    0ul,
                    entry.GetKey(),
                    entry.GetVariant(PlayerGender.Female),
                    entry.GetVariant(PlayerGender.Male)
                ));
            }
        }
    }
}
