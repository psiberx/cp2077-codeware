@addField(AIArgumentMapping)
native let type: AIArgumentType;

@addField(AIArgumentMapping)
native let parameterizationType: AIParameterizationType;

@addField(AIArgumentMapping)
native let defaultValue: Variant;

@addField(AIArgumentMapping)
native let prefixValue: ref<AIArgumentMapping>;

@addField(AIArgumentMapping)
native let customTypeName: CName;
