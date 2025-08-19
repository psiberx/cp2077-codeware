@addField(gameLightComponent)
public native let emissiveOnly: Bool;

@addField(gameLightComponent)
public native let materialZone: gameEMaterialZone;

@addField(gameLightComponent)
public native let meshBrokenAppearance: CName;

@addField(gameLightComponent)
public native let onStrength: Float;

@addField(gameLightComponent)
public native let turnOnByDefault: Bool;

@addField(gameLightComponent)
public native let turnOnTime: Float;

@addField(gameLightComponent)
public native let turnOnCurve: CName;

@addField(gameLightComponent)
public native let turnOffTime: Float;

@addField(gameLightComponent)
public native let turnOffCurve: CName;

@addField(gameLightComponent)
public native let loopTime: Float;

@addField(gameLightComponent)
public native let loopCurve: CName;

@addField(gameLightComponent)
public native let synchronizedLoop: Bool;

@addField(gameLightComponent)
public native let isDestructible: Bool;

@addField(gameLightComponent)
public native let colliderName: CName;

@addField(gameLightComponent)
public native let colliderTag: CName;

@addField(gameLightComponent)
public native let destructionEffect: ResourceAsyncRef; // raRef<worldEffect>

@addField(gameLightComponent)
public native let genericCurveSetOverride: ResourceRef; // rRef<CurveSet>
