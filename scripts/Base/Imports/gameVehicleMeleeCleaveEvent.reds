public native class gameVehicleMeleeCleaveEvent extends Event {
  public native let attackData: ref<AttackData>;
  public native let hitPosition: Vector4;
  public native let hitDirection: Vector4;
  public native let hitComponent: wref<IPlacedComponent>;
}
