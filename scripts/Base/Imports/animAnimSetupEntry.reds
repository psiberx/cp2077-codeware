public native struct animAnimSetupEntry {
  native let priority: Uint8;
  native let animSet: ResourceAsyncRef; // raRef<animAnimSet>
  native let variableNames: array<CName>;
}
