public native class entEntityOrientationProvider extends IOrientationProvider {
  native let slotComponent: wref<SlotComponent>;
  native let slotId: Int32;
  native let entity: wref<Entity>;
  native let orientationEntitySpace: Quaternion;
}
