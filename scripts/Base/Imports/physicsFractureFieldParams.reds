public native struct physicsFractureFieldParams {
  public native let origin: Vector3;
  public native let fractureFieldValue: Float;
  public native let destructionTypeMask: Uint16; // physicsDestructionType
  public native let fractureFieldTypeMask: Uint16; // physicsFractureFieldType
  public native let fractureFieldOptionsMask: Uint16; // physicsFractureFieldOptions
  public native let fractureFieldEffect: physicsFractureFieldEffect;
  public native let fractureFieldValueType: physicsFractureFieldValueType;
}
