public native struct scnScenesVersionsChangedRecord {
  native let changeInVersion: Uint32;
  native let sceneBeforeChange: ResourceAsyncRef; // raRef<scnSceneResource>
}
