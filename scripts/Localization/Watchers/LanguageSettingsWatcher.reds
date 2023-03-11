// -----------------------------------------------------------------------------
// Codeware.Localization.LanguageSettingsWatcher
// -----------------------------------------------------------------------------

module Codeware.Localization

public class LanguageSettingsWatcher extends ConfigVarListener {
    private let m_game: GameInstance;

    public func Initialize(game: GameInstance) {
        this.m_game = game;
    }

    public func Start() {
        this.Register(n"/language");
    }

    protected cb func OnVarModified(groupPath: CName, varName: CName, varType: ConfigVarType, reason: ConfigChangeReason) {
        if Equals(reason, ConfigChangeReason.Accepted) {
            GameInstance.GetScriptableSystemsContainer(this.m_game)
                .QueueRequest(UpdateLocaleRequest.Create(varName));
        }
    }
}
