public native struct rendOpacityMicromapChunk {
  public native let mChunkIndex: Uint32;
  public native let unkIndex: Uint32;
  public native let terialIdentifier: Uint64;
  public native let terialName: CName;
  public native let mDigest: Uint64;
  public native let mIndexBufferSize: Uint32;
  public native let mIndexBuffer16bit: Uint32;
  public native let mIndexBufferOffset: Uint64;
  public native let mArrayBufferOffset: Uint64;
  public native let mDescsBufferOffset: Uint64;
  public native let mDescArrayHistogramData: array<rendOpacityMicromapUsageCounts>;
  public native let mIndexHistogramData: array<rendOpacityMicromapUsageCounts>;
}
