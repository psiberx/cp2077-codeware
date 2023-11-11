public native class WorldStateSystem extends IGameSystem {
    public native func IsReady() -> Bool

    public native func ActivateCommunity(community: NodeRef, opt entry: CName)
    public native func DeactivateCommunity(community: NodeRef, opt entry: CName)

    public native func TogglePrefab(prefab: NodeRef, state: Bool)
    public native func TogglePrefabVariant(prefab: NodeRef, variant: CName, state: Bool)
}

@addMethod(GameInstance)
public static native func GetWorldStateSystem() -> ref<WorldStateSystem>
