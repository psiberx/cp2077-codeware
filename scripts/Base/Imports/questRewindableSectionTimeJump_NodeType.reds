public native class questRewindableSectionTimeJump_NodeType extends questISceneManagerNodeType {
  native let sceneFile: ResourceAsyncRef; // raRef<scnSceneResource>
  native let jumpTargetTime: Uint32;
  native let jumpSpeed: Float;
  native let postJumpPlayDirection: scnPlayDirection;
  native let postJumpPlaySpeed: scnPlaySpeed;
}
