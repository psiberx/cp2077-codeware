public native class worldEntityNode extends worldNode {
  public native let entityTemplate: ResourceAsyncRef; // raRef<entEntityTemplate>
  public native let instanceData: ref<entEntityInstanceData>;
  public native let appearanceName: CName;
  public native let ioPriority: entEntitySpawnPriority;
  public native let entityLod: Uint16;
}
