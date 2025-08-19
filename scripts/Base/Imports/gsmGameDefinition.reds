public native class gsmGameDefinition extends CResource {
  public native let mainQuests: array<ref<gsmMainQuest>>;
  public native let world: ResourceAsyncRef; // raRef<worldWorld>
  public native let streamingWorld: ResourceAsyncRef; // raRef<CResource>
  public native let worldName: String;
  public native let spawnPointTags: redTagList;
}
