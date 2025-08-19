@addField(EntityReference)
public native persistent let type: gameEntityReferenceType;

@addField(EntityReference)
public native persistent let names: array<CName>;

@addField(EntityReference)
public native persistent let slotName: CName;

@addField(EntityReference)
public native persistent let sceneActorContextName: CName;

@addField(EntityReference)
public native persistent let dynamicEntityUniqueName: CName;
