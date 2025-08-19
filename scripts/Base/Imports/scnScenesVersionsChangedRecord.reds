public native struct scnScenesVersionsChangedRecord {
  public native let changeInVersion: Uint32;
  public native let sceneBeforeChange: ResourceAsyncRef; // raRef<scnSceneResource>
}
