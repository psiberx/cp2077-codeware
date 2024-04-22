public native class animAnimStateTransitionDescription extends ISerializable {
  native let targetStateIndex: Uint32;
  native let isEnabled: Bool;
  native let duration: Float;
  native let priority: Int32;
  native let isForcedToTrue: Bool;
  native let supportBlendFromPose: Bool;
  native let canRequestInertialization: Bool;
  native let animFeatureName: CName;
  native let actionAnimDatabaseRef: ResourceRef; // rRef<animActionAnimDatabase>
  native let isOutTransitionFromAction: Bool;
}
