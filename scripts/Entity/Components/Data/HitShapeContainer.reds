public importonly native struct HitShapeContainer {
  native let name: CName;
  native let slotName: CName;
  native let color: Color;
  native let userData: ref<HitShapeUserData>;
  native let physicsMaterial: physicsMaterialReference;
}
