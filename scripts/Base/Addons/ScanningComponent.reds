@addField(ScanningComponent)
public native let scannableData: array<ScanningTooltipElementDef>;

@addField(ScanningComponent)
public native let timeNeeded: Float;

@addField(ScanningComponent)
public native let autoGenerateBoundingSphere: Bool;

@addField(ScanningComponent)
public native let boundingSphere: Sphere;

@addField(ScanningComponent)
public native let ignoresScanningDistanceLimit: Bool;

@addField(ScanningComponent)
public native let cpoEnableMultiplePlayersScanningModifier: Bool;
