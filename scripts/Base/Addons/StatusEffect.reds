// @mixedRef()

@addField(StatusEffect)
public native persistent let durationID: Uint32;

@addField(StatusEffect)
public native persistent let duration: Float;

@addField(StatusEffect)
public native persistent let remainingDuration: Float;

@addField(StatusEffect)
public native persistent let maxStacks: Uint32;

@addField(StatusEffect)
public native persistent let sourcesData: array<gameSourceData>;

@addField(StatusEffect)
public native persistent let initialApplicationTimestamp: Float;

@addField(StatusEffect)
public native persistent let lastApplicationTimestamp: Float;

@addField(StatusEffect)
public native persistent let ownerEntityID: EntityID;

@addField(StatusEffect)
public native persistent let instigatorRecordID: TweakDBID;

@addField(StatusEffect)
public native persistent let instigatorEntityID: EntityID;

@addField(StatusEffect)
public native persistent let proxyEntityID: EntityID;

@addField(StatusEffect)
public native persistent let direction: Vector4;

@addField(StatusEffect)
public native persistent let removeAllStacksWhenDurationEnds: Bool;

@addField(StatusEffect)
public native persistent let applicationSource: CName;
