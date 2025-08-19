public native struct scnIKEventData {
  public native let orientation: Quaternion;
  public native let basic: scnAnimTargetBasicData;
  public native let chainName: CName;
  public native let request: IKTargetRequest;
}
