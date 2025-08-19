public importonly struct HitShapeContainer {
  public native let name: CName;
  public native let slotName: CName;
  public native let color: Color;
  public native let shape: ref<IHitShape>;
  public native let userData: ref<HitShapeUserData>;
  public native let physicsMaterial: physicsMaterialReference;
}
