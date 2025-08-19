public native class questRewindableSectionTimeJump_NodeType extends questISceneManagerNodeType {
  public native let sceneFile: ResourceAsyncRef; // raRef<scnSceneResource>
  public native let jumpTargetTime: Uint32;
  public native let jumpSpeed: Float;
  public native let postJumpPlayDirection: scnPlayDirection;
  public native let postJumpPlaySpeed: scnPlaySpeed;
}
