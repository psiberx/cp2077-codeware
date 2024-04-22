public native class questBriefingSequencePlayer_NodeType extends questIUIManagerNodeType {
  native let function: questBriefingSequencePlayerFunction;
  native let briefingResource: ResourceAsyncRef; // raRef<inkWidgetLibraryResource>
  native let userData: ref<inkUserData>;
  native let audioEvent: CName;
  native let animationName: CName;
  native let startMarkerName: CName;
  native let endMarkerName: CName;
  native let loopType: inkanimLoopType;
  native let briefingPlayerType: questBriefingPlayerType;
  native let briefingType: questBriefingType;
  native let enableScanner: Bool;
}
