public abstract native class ScriptableServiceContainer extends IGameSystem {
    public native func GetService(name: CName) -> ref<ScriptableService>
}

@addMethod(GameInstance)
public static native func GetScriptableServiceContainer() -> ref<ScriptableServiceContainer>
