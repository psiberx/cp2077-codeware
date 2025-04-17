public native class physicsCollisionFilterResource extends ISerializable {
  native let collisionPresetJson: ResourceRef; // rRef<JsonResource>
  native let overridesJson: ResourceRef; // rRef<JsonResource>
  native let queryPresetJson: ResourceRef; // rRef<JsonResource>
  native let collisionGroups: [CName; 64];
  native let queryGroups: [CName; 64];
}
