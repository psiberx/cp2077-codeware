public native class physicsSystemBody extends physicsISystemObject {
  native let params: physicsSystemBodyParams;
  native let localToModel: Transform;
  native let mappedBoneName: CName;
  native let mappedBoneToBody: Transform;
  native let isQueryBodyOnly: Bool;
}
