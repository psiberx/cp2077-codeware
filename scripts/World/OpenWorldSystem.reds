public native class OpenWorldSystem extends IGameSystem {
    public native func IsReady() -> Bool

    public native func GetActivity(name: CName) -> OpenWorldActivityState
    public native func GetActivities() -> array<OpenWorldActivityState>

    public native func StartActivity(name: CName) -> Bool
    public native func StartActivities(opt request: OpenWorldActivityRequest) -> Bool
}

@addMethod(GameInstance)
public static native func GetOpenWorldSystem() -> ref<OpenWorldSystem>
