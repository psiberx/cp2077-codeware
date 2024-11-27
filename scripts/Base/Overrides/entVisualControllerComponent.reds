public native class entVisualControllerComponent extends IComponent {
  native let meshProxy: ResourceRef; // rRef<CMesh>
  native let appearanceDependency: array<entVisualControllerDependency>;
  native let cookedAppearanceData: ResourceAsyncRef; // raRef<appearanceCookedAppearanceData>
  native let forcedLodDistance: entForcedLodDistance;

  public native func LoadAppearanceDependencies(opt wait: Bool) -> Bool
}
