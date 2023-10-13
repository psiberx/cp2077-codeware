@addField(PlayerSystem)
private let m_customizationPuppet: wref<gamePuppet>;

@addField(PlayerSystem)
private let m_inventoryPuppet: wref<gamePuppet>;

@addField(PlayerSystem)
private let m_photoPuppet: wref<gamePuppet>;

@addMethod(PlayerSystem)
public func GetPlayer() -> ref<PlayerPuppet> {
    return this.GetLocalPlayerControlledGameObject() as PlayerPuppet;
}

@addMethod(PlayerSystem)
public func GetCustomizationPuppet() -> wref<gamePuppet> {
    return this.m_customizationPuppet;
}

@addMethod(PlayerSystem)
public func GetInventoryPuppet() -> wref<gamePuppet> {
    return this.m_inventoryPuppet;
}

@addMethod(PlayerSystem)
public func GetPhotoPuppet() -> wref<gamePuppet> {
    return this.m_photoPuppet;
}

@wrapMethod(inkPuppetPreviewGameController)
protected cb func OnPreviewInitialized() -> Bool {
    wrappedMethod();

    switch this.GetClassName() {
        case n"gameuiInventoryPuppetPreviewGameController":
            GameInstance.GetPlayerSystem(this.GetPlayerControlledObject().GetGame()).m_inventoryPuppet = this.GetGamePuppet();
            break;
        case n"gameuiCharacterCreationPuppetPreviewGameController":
            GameInstance.GetPlayerSystem(this.GetPlayerControlledObject().GetGame()).m_customizationPuppet = this.GetGamePuppet();
            break;
    }
}

@wrapMethod(PhotoModePlayerEntityComponent)
private final func SetupInventory(isCurrentPlayerObjectCustomizable: Bool) {
    wrappedMethod(isCurrentPlayerObjectCustomizable);

    GameInstance.GetPlayerSystem(this.GetOwner().GetGame()).m_photoPuppet = this.fakePuppet;
}
