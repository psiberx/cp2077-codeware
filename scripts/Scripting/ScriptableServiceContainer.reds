public abstract native class CodewareScriptableServiceContainer extends IGameSystem {
    public native func GetService(name: CName) -> ref<CodewareScriptableService>
}

@addMethod(GameInstance)
public static native func GetCodewareScriptableServiceContainer() -> ref<CodewareScriptableServiceContainer>
