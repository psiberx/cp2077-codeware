public abstract native class animDangleConstraint_Simulation extends ISerializable {
  public native let collisionRoundedShapes: array<animCollisionRoundedShape>;
  public native let jsonCollisionShapes: ResourceRef; // rRef<JsonResource>
  public native let jsonCollisionShapesLoadedSuccessfully: Bool;
  public native let alpha: Float;
  public native let rotateParentToLookAtDangle: Bool;
  public native let parentRotationAltersTransformsOfDangleAndItsChildren: Bool;
  public native let parentRotationAltersTransformsOfNonDanglesAndItsChildren: Bool;
  public native let dangleAltersTransformsOfItsChildren: Bool;
}
