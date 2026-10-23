// Game 2.5 declares CallbackSystemHandler.SetRunMode/SetLifetime with its own enums
// (gameCallbackRunMode/gameCallbackLifetime), while mods pass Codeware's enums.
// Both enums have the same members and values.

@addMethod(CallbackSystemHandler)
public func SetRunMode(runMode: CallbackRunMode) -> ref<CallbackSystemHandler> {
    switch runMode {
        case CallbackRunMode.Once:
            return this.SetRunMode(gameCallbackRunMode.Once);
        case CallbackRunMode.OncePerTarget:
            return this.SetRunMode(gameCallbackRunMode.OncePerTarget);
        default:
            return this.SetRunMode(gameCallbackRunMode.Default);
    }
}

@addMethod(CallbackSystemHandler)
public func SetLifetime(lifetime: CallbackLifetime) -> ref<CallbackSystemHandler> {
    switch lifetime {
        case CallbackLifetime.Forever:
            return this.SetLifetime(gameCallbackLifetime.Forever);
        default:
            return this.SetLifetime(gameCallbackLifetime.Session);
    }
}
