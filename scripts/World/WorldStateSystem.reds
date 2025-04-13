public native class WorldStateSystem extends IGameSystem {
    public native func IsReady() -> Bool

    public native func ActivateCommunity(community: NodeRef, opt entry: CName)
    public native func DeactivateCommunity(community: NodeRef, opt entry: CName)

    public native func ToggleNode(node: NodeRef, state: Bool)
    public native func ToggleVariant(ref: NodeRef, name: CName, state: Bool)

    public func TogglePrefab(node: NodeRef, state: Bool) {
        this.ToggleNode(node, state);
    }

    public func TogglePrefabVariant(ref: NodeRef, name: CName, state: Bool) {
        this.ToggleVariant(ref, name, state);
    }
}

@addMethod(GameInstance)
public static native func GetWorldStateSystem() -> ref<WorldStateSystem>
