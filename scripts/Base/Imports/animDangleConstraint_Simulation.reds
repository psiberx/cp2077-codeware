public abstract native class animDangleConstraint_Simulation extends ISerializable {
  native let collisionRoundedShapes: array<animCollisionRoundedShape>;
  native let jsonCollisionShapes: ResourceRef; // rRef<JsonResource>
  native let jsonCollisionShapesLoadedSuccessfully: Bool;
  native let alpha: Float;
  native let rotateParentToLookAtDangle: Bool;
  native let parentRotationAltersTransformsOfDangleAndItsChildren: Bool;
  native let parentRotationAltersTransformsOfNonDanglesAndItsChildren: Bool;
  native let dangleAltersTransformsOfItsChildren: Bool;
}
