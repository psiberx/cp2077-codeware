@addMethod(CallbackSystemHandler)
public func SetRunMode(mode: CallbackRunMode) -> ref<CallbackSystemHandler> {
    return this.SetRunMode(IntEnum<gameCallbackRunMode>(EnumInt(mode)));
}

@addMethod(CallbackSystemHandler)
public func SetLifetime(lifetime: CallbackLifetime) -> ref<CallbackSystemHandler> {
    return this.SetLifetime(IntEnum<gameCallbackLifetime>(EnumInt(lifetime)));
}
