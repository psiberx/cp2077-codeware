public abstract native struct ScriptableServiceContainer {
    public static native func Get(name: CName) -> ref<ScriptableService>
}
