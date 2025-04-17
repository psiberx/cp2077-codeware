@addField(EntityReference)
native persistent let type: gameEntityReferenceType;

@addField(EntityReference)
native persistent let names: array<CName>;

@addField(EntityReference)
native persistent let slotName: CName;

@addField(EntityReference)
native persistent let sceneActorContextName: CName;

@addField(EntityReference)
native persistent let dynamicEntityUniqueName: CName;
