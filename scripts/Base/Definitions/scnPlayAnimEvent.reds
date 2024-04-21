public abstract native class scnPlayAnimEvent extends scnSceneEvent {
  native let animData: scneventsPlayAnimEventExData;
  native let performer: scnPerformerId;
  native let actorComponent: CName;
  native let convertToAdditive: Bool;
  native let neckWeight: Float;
  native let upperFaceBlendAdditive: Bool;
  native let lowerFaceBlendAdditive: Bool;
  native let eyesBlendAdditive: Bool;
}
