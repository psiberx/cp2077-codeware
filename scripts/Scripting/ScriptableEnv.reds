
public abstract native class ScriptableEnv {
    // private cb func OnLoad()
    // private cb func OnReload()
    // private cb func OnInitialize()

    public static native func Get(name: CName) -> ref<ScriptableEnv>
}
