public native struct vehicleDestructionPSData {
  public native persistent let gridValues: [Float; 30];
  public native persistent let brokenGlass: Uint32;
  public native persistent let brokenLights: Uint32;
  public native persistent let flatTire: Uint8;
  public native persistent let windshieldShattered: Bool;
  public native persistent let windshieldPoints: array<Vector3>;
  public native persistent let detachedParts: array<CName>;
}
