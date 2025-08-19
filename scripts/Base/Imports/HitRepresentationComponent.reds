public native class HitRepresentationComponent extends SlotComponent {
  public native let representations: array<HitShapeContainer>;
  public native let physicsMaterial: CName;
  public native let bvhRoot: gameHitShapeBVH;
  public native let useResourceData: Bool;
  public native let resource: ResourceAsyncRef; // raRef<HitRepresentationResource>
  public native let appearanceOverrides: array<HitRepresentationOverride>;
}
