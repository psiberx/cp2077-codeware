@addField(StatusEffect)
native persistent let durationID: Uint32;

@addField(StatusEffect)
native persistent let duration: Float;

@addField(StatusEffect)
native persistent let remainingDuration: Float;

@addField(StatusEffect)
native persistent let maxStacks: Uint32;

@addField(StatusEffect)
native persistent let sourcesData: array<gameSourceData>;

@addField(StatusEffect)
native persistent let initialApplicationTimestamp: Float;

@addField(StatusEffect)
native persistent let lastApplicationTimestamp: Float;

@addField(StatusEffect)
native persistent let ownerEntityID: EntityID;

@addField(StatusEffect)
native persistent let instigatorRecordID: TweakDBID;

@addField(StatusEffect)
native persistent let instigatorEntityID: EntityID;

@addField(StatusEffect)
native persistent let proxyEntityID: EntityID;

@addField(StatusEffect)
native persistent let direction: Vector4;

@addField(StatusEffect)
native persistent let removeAllStacksWhenDurationEnds: Bool;

@addField(StatusEffect)
native persistent let applicationSource: CName;
