public native struct entReplicatedLookAtAdd {
  public native let creationNetTime: netTime;
  public native let bodyPart: CName;
  public native let request: LookAtRequest;
  public native let targetPositionProvider: ref<IPositionProvider>;
  public native let ref: LookAtRef;
}
