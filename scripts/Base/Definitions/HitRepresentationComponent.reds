public native class HitRepresentationComponent extends SlotComponent {
  native let representations: array<HitShapeContainer>;
  native let physicsMaterial: CName;
  native let bvhRoot: gameHitShapeBVH;
  native let useResourceData: Bool;
  native let resource: ResourceAsyncRef; // raRef<HitRepresentationResource>
}
