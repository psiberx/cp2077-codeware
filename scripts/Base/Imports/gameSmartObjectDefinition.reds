public native class gameSmartObjectDefinition extends ISerializable {
  native let resource: ResourceRef; // rRef<gameSmartObjectResource>
  native let actions: array<CName>;
  native let motionActionDatabase: ResourceRef; // rRef<animActionAnimDatabase>
  native let enabled: Bool;
  native let overrideGeneratedParameters: Bool;
}
