public native struct animFacialSetup_BufferInfo {
  native let tracksMapping: animFacialSetup_TracksMapping;
  native let numLipsyncOverridesIndexMapping: Uint16;
  native let numJointRegions: Uint16;
  native let face: animFacialSetup_OneSermoBufferInfo;
  native let eyes: animFacialSetup_OneSermoBufferInfo;
  native let tongue: animFacialSetup_OneSermoBufferInfo;
}
