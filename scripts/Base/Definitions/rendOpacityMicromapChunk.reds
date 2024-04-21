public native struct rendOpacityMicromapChunk {
  native let mChunkIndex: Uint32;
  native let unkIndex: Uint32;
  native let terialIdentifier: Uint64;
  native let terialName: CName;
  native let mDigest: Uint64;
  native let mIndexBufferSize: Uint32;
  native let mIndexBuffer16bit: Uint32;
  native let mIndexBufferOffset: Uint64;
  native let mArrayBufferOffset: Uint64;
  native let mDescsBufferOffset: Uint64;
  native let mDescArrayHistogramData: array<rendOpacityMicromapUsageCounts>;
  native let mIndexHistogramData: array<rendOpacityMicromapUsageCounts>;
}
