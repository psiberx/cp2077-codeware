public native class gameDelayedFunctionsScheduler extends ISerializable {
  public native persistent let initialized: Bool;
  public native persistent let currentTime: EngineTime;
  public native persistent let nextCallId: Uint32;
}
