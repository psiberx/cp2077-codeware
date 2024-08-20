@addField(gameLightComponent)
native let emissiveOnly: Bool;

@addField(gameLightComponent)
native let materialZone: gameEMaterialZone;

@addField(gameLightComponent)
native let meshBrokenAppearance: CName;

@addField(gameLightComponent)
native let onStrength: Float;

@addField(gameLightComponent)
native let turnOnByDefault: Bool;

@addField(gameLightComponent)
native let turnOnTime: Float;

@addField(gameLightComponent)
native let turnOnCurve: CName;

@addField(gameLightComponent)
native let turnOffTime: Float;

@addField(gameLightComponent)
native let turnOffCurve: CName;

@addField(gameLightComponent)
native let loopTime: Float;

@addField(gameLightComponent)
native let loopCurve: CName;

@addField(gameLightComponent)
native let synchronizedLoop: Bool;

@addField(gameLightComponent)
native let isDestructible: Bool;

@addField(gameLightComponent)
native let colliderName: CName;

@addField(gameLightComponent)
native let colliderTag: CName;

@addField(gameLightComponent)
native let destructionEffect: ResourceAsyncRef; // raRef<worldEffect>

@addField(gameLightComponent)
native let genericCurveSetOverride: ResourceRef; // rRef<CurveSet>

