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
public func SetCustomizationPuppet(value: wref<gamePuppet>) -> Void {
    this.m_customizationPuppet = value;
}

@addMethod(PlayerSystem)
public func GetInventoryPuppet() -> wref<gamePuppet> {
    return this.m_inventoryPuppet;
}

@addMethod(PlayerSystem)
public func SetInventoryPuppet(value: wref<gamePuppet>) -> Void {
    this.m_inventoryPuppet = value;
}

@addMethod(PlayerSystem)
public func GetPhotoPuppet() -> wref<gamePuppet> {
    return this.m_photoPuppet;
}

@addMethod(PlayerSystem)
public func SetPhotoPuppet(value: wref<gamePuppet>) -> Void {
    this.m_photoPuppet = value;
}

@wrapMethod(inkPuppetPreviewGameController)
protected cb func OnPreviewInitialized() -> Bool {
    wrappedMethod();

    switch this.GetClassName() {
        case n"gameuiInventoryPuppetPreviewGameController":
            GameInstance.GetPlayerSystem(this.GetPlayerControlledObject().GetGame()).SetInventoryPuppet(this.GetGamePuppet());
            break;
        case n"gameuiCharacterCreationPuppetPreviewGameController":
            GameInstance.GetPlayerSystem(this.GetPlayerControlledObject().GetGame()).SetCustomizationPuppet(this.GetGamePuppet());
            break;
    }
}

@wrapMethod(PhotoModePlayerEntityComponent)
private final func SetupInventory(isCurrentPlayerObjectCustomizable: Bool) {
    wrappedMethod(isCurrentPlayerObjectCustomizable);

    GameInstance.GetPlayerSystem(this.GetOwner().GetGame()).SetPhotoPuppet(this.fakePuppet);
}
