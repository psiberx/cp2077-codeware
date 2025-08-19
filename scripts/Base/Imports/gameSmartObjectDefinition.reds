public native class gameSmartObjectDefinition extends ISerializable {
  public native let resource: ResourceRef; // rRef<gameSmartObjectResource>
  public native let actions: array<CName>;
  public native let motionActionDatabase: ResourceRef; // rRef<animActionAnimDatabase>
  public native let enabled: Bool;
  public native let overrideGeneratedParameters: Bool;
}
