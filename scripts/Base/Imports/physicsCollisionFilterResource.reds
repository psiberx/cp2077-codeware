public native class physicsCollisionFilterResource extends ISerializable {
  public native let collisionPresetJson: ResourceRef; // rRef<JsonResource>
  public native let overridesJson: ResourceRef; // rRef<JsonResource>
  public native let queryPresetJson: ResourceRef; // rRef<JsonResource>
  public native let collisionGroups: [CName; 64];
  public native let queryGroups: [CName; 64];
}
