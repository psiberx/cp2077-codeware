public native struct Sample_All_Supported_Replicated_Types {
  native let bool: Bool;
  native let uint8: Uint8;
  native let int8: Int8;
  native let uint16: Uint16;
  native let int16: Int16;
  native let uint32: Uint32;
  native let int32: Int32;
  native let uint64: Uint64;
  native let int64: Int64;
  native let float: Float;
  native let double: Double;
  native let name: CName;
  native let string: String;
  native let enum: Sample_Replicated_Enum;
  native let struct: Sample_Replicated_Struct;
  native let dynamicArray: array<Sample_Replicated_Struct>;
  native let THandle: ref<Sample_Replicated_Serializable>;
}
