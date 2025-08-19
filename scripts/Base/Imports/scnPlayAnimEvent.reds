public abstract native class scnPlayAnimEvent extends scnSceneEvent {
  public native let animData: scneventsPlayAnimEventExData;
  public native let performer: scnPerformerId;
  public native let actorComponent: CName;
  public native let convertToAdditive: Bool;
  public native let neckWeight: Float;
  public native let upperFaceBlendAdditive: Bool;
  public native let lowerFaceBlendAdditive: Bool;
  public native let eyesBlendAdditive: Bool;
}
