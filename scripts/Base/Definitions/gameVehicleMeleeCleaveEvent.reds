public native class gameVehicleMeleeCleaveEvent extends Event {
  native let attackData: ref<AttackData>;
  native let hitPosition: Vector4;
  native let hitDirection: Vector4;
  native let hitComponent: wref<IPlacedComponent>;
}
