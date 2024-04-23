public abstract native class scnSceneEvent extends ISerializable {
  native let id: scnSceneEventId;
  native let type: scnEventType;
  native let startTime: Uint32;
  native let duration: Uint32;
  native let executionTagFlags: Uint8;
  native let scalingData: ref<scnIScalingData>;
}
