public native class worldEntityNode extends worldNode {
  native let entityTemplate: ResourceAsyncRef; // raRef<entEntityTemplate>
  native let appearanceName: CName;
  native let ioPriority: entEntitySpawnPriority;
  native let entityLod: Uint16;
}
