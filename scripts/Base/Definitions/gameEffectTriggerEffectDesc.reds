public native class gameEffectTriggerEffectDesc extends ISerializable {
  native let effect: ResourceAsyncRef; // raRef<worldEffect>
  native let positionType: gameEffectTriggerPositioningType;
  native let rotationType: gameEffectTriggerRotationType;
  native let offset: Vector3;
  native let playFromHour: Uint32;
  native let playTillHour: Uint32;
}
