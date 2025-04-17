@addField(AIBaseUseWorkspotCommand)
native persistent let workExcludedGestures: array<WorkEntryId>;

@addField(AIBaseUseWorkspotCommand)
native persistent let infiniteSequenceEntryId: WorkEntryId;

@addField(AIBaseUseWorkspotCommand)
native persistent let idleOnlyMode: Bool;
