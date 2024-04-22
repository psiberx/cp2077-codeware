public native struct scnMarker {
  native let type: scnMarkerType;
  native let localMarkerId: CName;
  native let nodeRef: NodeRef;
  native let entityRef: EntityReference;
  native let slotName: CName;
  native let isMounted: Bool;
}
