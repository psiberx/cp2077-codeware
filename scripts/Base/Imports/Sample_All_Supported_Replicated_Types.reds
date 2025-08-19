public native struct Sample_All_Supported_Replicated_Types {
  public native let bool: Bool;
  public native let uint8: Uint8;
  public native let int8: Int8;
  public native let uint16: Uint16;
  public native let int16: Int16;
  public native let uint32: Uint32;
  public native let int32: Int32;
  public native let uint64: Uint64;
  public native let int64: Int64;
  public native let float: Float;
  public native let double: Double;
  public native let name: CName;
  public native let string: String;
  public native let enum: Sample_Replicated_Enum;
  public native let struct: Sample_Replicated_Struct;
  public native let dynamicArray: array<Sample_Replicated_Struct>;
  public native let staticArray: [Sample_Replicated_Struct; 10];
  public native let THandle: ref<Sample_Replicated_Serializable>;
}
