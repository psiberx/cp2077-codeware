public native struct scnMarker {
  public native let type: scnMarkerType;
  public native let localMarkerId: CName;
  public native let nodeRef: NodeRef;
  public native let entityRef: EntityReference;
  public native let slotName: CName;
  public native let isMounted: Bool;
}
