public native class physicsSystemBody extends physicsISystemObject {
  public native let params: physicsSystemBodyParams;
  public native let localToModel: Transform;
  public native let collisionShapes: array<ref<physicsICollider>>;
  public native let mappedBoneName: CName;
  public native let mappedBoneToBody: Transform;
  public native let isQueryBodyOnly: Bool;
}
