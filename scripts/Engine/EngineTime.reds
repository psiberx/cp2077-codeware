@addMethod(EngineTime)
public final static native func GetFrequency() -> Uint64

@addMethod(EngineTime)
public final static native func FromTicks(value: Uint64) -> EngineTime

@addMethod(EngineTime)
public final static native func ToTicks(self: EngineTime) -> Uint64
