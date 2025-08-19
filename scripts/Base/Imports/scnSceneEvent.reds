public abstract native class scnSceneEvent extends ISerializable {
  public native let id: scnSceneEventId;
  public native let type: scnEventType;
  public native let startTime: Uint32;
  public native let duration: Uint32;
  public native let executionTagFlags: Uint8;
  public native let scalingData: ref<scnIScalingData>;
}
