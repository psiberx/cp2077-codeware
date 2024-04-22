public abstract native class ScriptableService {
    // private cb func OnLoad()
    // private cb func OnReload()
    // private cb func OnInitialize()
}

// DEPRECATED
// BACKWARDS COMPATIBILITY
public abstract class ScriptableEnv extends ScriptableService {
    public static final func Get(name: CName) -> ref<ScriptableService> = ScriptableServiceContainer.Get(name)
}
