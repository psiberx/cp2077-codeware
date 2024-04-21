public native class gameDelayedFunctionsScheduler extends ISerializable {
  native persistent let initialized: Bool;
  native persistent let currentTime: EngineTime;
  native persistent let nextCallId: Uint32;
}
