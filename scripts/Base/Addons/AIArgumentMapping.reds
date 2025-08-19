@addField(AIArgumentMapping)
public native let type: AIArgumentType;

@addField(AIArgumentMapping)
public native let parameterizationType: AIParameterizationType;

@addField(AIArgumentMapping)
public native let defaultValue: Variant;

@addField(AIArgumentMapping)
public native let prefixValue: ref<AIArgumentMapping>;

@addField(AIArgumentMapping)
public native let customTypeName: CName;
