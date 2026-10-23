public abstract native class CodewareScriptableService {
    // private cb func OnLoad()
    // private cb func OnReload()
    // private cb func OnInitialize()
    // private cb func OnUninitialize()
}

// DEPRECATED
public abstract class CodewareScriptableEnv extends CodewareScriptableService {
    public static final func Get(name: CName) -> ref<CodewareScriptableService>
        = GameInstance.GetCodewareScriptableServiceContainer().GetService(name)
}
