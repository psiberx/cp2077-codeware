public native struct entReplicatedLookAtAdd {
  native let creationNetTime: netTime;
  native let bodyPart: CName;
  native let request: LookAtRequest;
  native let targetPositionProvider: ref<IPositionProvider>;
  native let ref: LookAtRef;
}
