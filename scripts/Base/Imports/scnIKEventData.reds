public native struct scnIKEventData {
  native let orientation: Quaternion;
  native let basic: scnAnimTargetBasicData;
  native let chainName: CName;
  native let request: IKTargetRequest;
}
