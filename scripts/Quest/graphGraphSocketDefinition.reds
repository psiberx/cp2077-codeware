public abstract native class graphGraphSocketDefinition extends graphIGraphObjectDefinition {
  native let name: CName;
  native let connections: array<ref<graphGraphConnectionDefinition>>;
  native let owner: wref<graphGraphNodeDefinition>;
}
