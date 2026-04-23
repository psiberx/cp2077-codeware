@addMethod(TraceResult)
public final static native func GetProxyID(self: script_ref<TraceResult>) -> Uint32

@addMethod(TraceResult)
public final static native func GetActorIndex(self: script_ref<TraceResult>) -> Uint32

@addMethod(TraceResult)
public final static native func GetShapeIndex(self: script_ref<TraceResult>) -> Int32

@addMethod(TraceResult)
public final static native func GetHitObject(self: script_ref<TraceResult>) -> ref<ISerializable>

@addMethod(TraceResult)
public final static native func GetHitEntity(self: script_ref<TraceResult>) -> ref<Entity>
