public native class gameEffectTriggerEffectDesc extends ISerializable {
  public native let effect: ResourceAsyncRef; // raRef<worldEffect>
  public native let positionType: gameEffectTriggerPositioningType;
  public native let rotationType: gameEffectTriggerRotationType;
  public native let offset: Vector3;
  public native let playFromHour: Uint32;
  public native let playTillHour: Uint32;
}
