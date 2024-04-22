public native struct scnLookAtBasicEventData {
  native let basic: scnAnimTargetBasicData;
  native let removePreviousAdvancedLookAts: Bool;
  native let requests: array<animLookAtRequestForPart>;
}
