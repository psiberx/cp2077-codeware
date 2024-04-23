public native class gsmGameDefinition extends CResource {
  native let mainQuests: array<ref<gsmMainQuest>>;
  native let world: ResourceAsyncRef; // raRef<worldWorld>
  native let streamingWorld: ResourceAsyncRef; // raRef<CResource>
  native let worldName: String;
  native let spawnPointTags: redTagList;
}
