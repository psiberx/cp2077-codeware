
public native class OpenWorldSystem extends IGameSystem {
    public native func IsReady() -> Bool

    public native func ReactivateMinorActivity(activity: CName) -> Bool
    public native func ReactivateMinorActivities()
}

@addMethod(GameInstance)
public static native func GetOpenWorldSystem() -> ref<OpenWorldSystem>
