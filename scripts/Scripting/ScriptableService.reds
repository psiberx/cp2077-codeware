public abstract native class ScriptableService {
    // private cb func OnLoad()
    // private cb func OnReload()
    // private cb func OnInitialize()

    public static native func Get(name: CName) -> ref<ScriptableService>
}

// Backwards compatibility
public abstract class ScriptableEnv extends ScriptableService {
    public static final func Get(name: CName) -> ref<ScriptableService> = ScriptableService.Get(name)
}
