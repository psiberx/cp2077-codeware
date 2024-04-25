public abstract native class ScriptableService {
    // private cb func OnLoad()
    // private cb func OnReload()
    // private cb func OnInitialize()
    // private cb func OnUninitialize()
}

// DEPRECATED
public abstract class ScriptableEnv extends ScriptableService {
    public static final func Get(name: CName) -> ref<ScriptableService>
        = GameInstance.GetScriptableServiceContainer().GetService(name)
}
