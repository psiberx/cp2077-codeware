// -----------------------------------------------------------------------------
// Codeware.Localization.PlayerGenderWatcher
// -----------------------------------------------------------------------------

module Codeware.Localization

public class PlayerGenderWatcher {
    private let m_game: GameInstance;

    private let m_callbackID: Uint32;

    public func Initialize(game: GameInstance) {
        this.m_game = game;
    }

    public func Start() {
        this.m_callbackID = GameInstance.GetPlayerSystem(this.m_game)
            .RegisterPlayerPuppetAttachedCallback(this, n"OnPlayerAttached");
    }

    public func Stop() {
        GameInstance.GetPlayerSystem(this.m_game)
            .UnregisterPlayerPuppetAttachedCallback(this.m_callbackID);
    }

    private func OnPlayerAttached(player: ref<GameObject>) {
        GameInstance.GetScriptableSystemsContainer(this.m_game)
            .QueueRequest(UpdateGenderRequest.Create());
    }
}
