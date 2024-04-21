public native struct gameMuppetCompressedInputStates {
  native let usesCompression: Bool;
  native let compressedInputStates: array<Uint8>;
  native let firstFrameId: Uint32;
  native let replicationTime: netTime;
}
