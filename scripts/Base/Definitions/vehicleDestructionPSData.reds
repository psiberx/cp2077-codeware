public native struct vehicleDestructionPSData {
  native persistent let brokenGlass: Uint32;
  native persistent let brokenLights: Uint32;
  native persistent let flatTire: Uint8;
  native persistent let windshieldShattered: Bool;
  native persistent let windshieldPoints: array<Vector3>;
  native persistent let detachedParts: array<CName>;
}
