public importonly struct HitShapeContainer {
  native let name: CName;
  native let slotName: CName;
  native let color: Color;
  native let shape: ref<IHitShape>;
  native let userData: ref<HitShapeUserData>;
  native let physicsMaterial: physicsMaterialReference;
}
