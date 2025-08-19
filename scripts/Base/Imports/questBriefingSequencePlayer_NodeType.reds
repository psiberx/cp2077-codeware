public native class questBriefingSequencePlayer_NodeType extends questIUIManagerNodeType {
  public native let function: questBriefingSequencePlayerFunction;
  public native let briefingResource: ResourceAsyncRef; // raRef<inkWidgetLibraryResource>
  public native let userData: ref<inkUserData>;
  public native let audioEvent: CName;
  public native let animationName: CName;
  public native let startMarkerName: CName;
  public native let endMarkerName: CName;
  public native let loopType: inkanimLoopType;
  public native let briefingPlayerType: questBriefingPlayerType;
  public native let briefingType: questBriefingType;
  public native let enableScanner: Bool;
}
