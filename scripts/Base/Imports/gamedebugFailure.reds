public native class gamedebugFailure extends ISerializable {
  public native let id: gamedebugFailureId;
  public native let time: Float;
  public native let message: String;
  public native let path: gameDebugPath;
  public native let previous: ref<gamedebugFailure>;
  public native let cause: ref<gamedebugFailure>;
}
