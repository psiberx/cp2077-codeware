public native class entVisualControllerComponent extends IComponent {
  public native let meshProxy: ResourceRef; // rRef<CMesh>
  public native let appearanceDependency: array<entVisualControllerDependency>;
  public native let cookedAppearanceData: ResourceAsyncRef; // raRef<appearanceCookedAppearanceData>
  public native let forcedLodDistance: entForcedLodDistance;

  public native func LoadAppearanceDependencies(opt wait: Bool) -> Bool
}
