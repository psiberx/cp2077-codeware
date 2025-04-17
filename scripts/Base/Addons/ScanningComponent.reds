@addField(ScanningComponent)
native let scannableData: array<ScanningTooltipElementDef>;

@addField(ScanningComponent)
native let timeNeeded: Float;

@addField(ScanningComponent)
native let autoGenerateBoundingSphere: Bool;

@addField(ScanningComponent)
native let boundingSphere: Sphere;

@addField(ScanningComponent)
native let ignoresScanningDistanceLimit: Bool;

@addField(ScanningComponent)
native let cpoEnableMultiplePlayersScanningModifier: Bool;
