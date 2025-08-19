public native class animAnimStateTransitionDescription extends ISerializable {
  public native let targetStateIndex: Uint32;
  public native let condition: ref<animIAnimStateTransitionCondition>;
  public native let isEnabled: Bool;
  public native let interpolator: ref<animIAnimStateTransitionInterpolator>;
  public native let duration: Float;
  public native let priority: Int32;
  public native let syncMethod: ref<animISyncMethod>;
  public native let isForcedToTrue: Bool;
  public native let supportBlendFromPose: Bool;
  public native let canRequestInertialization: Bool;
  public native let animFeatureName: CName;
  public native let actionAnimDatabaseRef: ResourceRef; // rRef<animActionAnimDatabase>
  public native let isOutTransitionFromAction: Bool;
}
