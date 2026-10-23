// Patch 2.5 compatibility: the game provides its own CallbackSystem with game-prefixed enums,
// and inkText.SetWrapping now takes a Float width.

@addMethod(CallbackSystemHandler)
public final func SetLifetime(lifetime: CallbackLifetime) -> ref<CallbackSystemHandler> {
    return this.SetLifetime(IntEnum<gameCallbackLifetime>(EnumInt(lifetime)));
}

@addMethod(CallbackSystemHandler)
public final func SetRunMode(runMode: CallbackRunMode) -> ref<CallbackSystemHandler> {
    return this.SetRunMode(IntEnum<gameCallbackRunMode>(EnumInt(runMode)));
}

@addMethod(inkText)
public final func SetWrapping(enabled: Bool, width: Int32, opt policy: textWrappingPolicy) {
    this.SetWrapping(enabled, Cast<Float>(width), policy);
}
