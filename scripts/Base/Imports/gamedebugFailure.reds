public native class gamedebugFailure extends ISerializable {
  native let id: gamedebugFailureId;
  native let time: Float;
  native let message: String;
  native let path: gameDebugPath;
  native let previous: ref<gamedebugFailure>;
  native let cause: ref<gamedebugFailure>;
}
