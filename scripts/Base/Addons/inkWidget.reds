@addField(inkWidget)
public native let logicController: ref<inkLogicController>;

@addField(inkWidget)
public native let secondaryControllers: array<ref<inkLogicController>>;

@addField(inkWidget)
public native let userData: array<ref<inkUserData>>;

@addField(inkWidget)
public native let name: CName;

@addField(inkWidget)
public native let state: CName;

@addField(inkWidget)
public native let visible: Bool;

@addField(inkWidget)
public native let affectsLayoutWhenHidden: Bool;

@addField(inkWidget)
public native let isInteractive: Bool;

@addField(inkWidget)
public native let canSupportFocus: Bool;

@addField(inkWidget)
public native let style: ref<inkStyleResourceWrapper>;

@addField(inkWidget)
public native let parentWidget: wref<inkWidget>;

@addField(inkWidget)
public native let propertyManager: ref<inkPropertyManager>;

@addField(inkWidget)
public native let fitToContent: Bool;

@addField(inkWidget)
public native let layout: inkWidgetLayout;

@addField(inkWidget)
public native let opacity: Float;

@addField(inkWidget)
public native let tintColor: HDRColor;

@addField(inkWidget)
public native let size: Vector2;

@addField(inkWidget)
public native let renderTransformPivot: Vector2;

@addField(inkWidget)
public native let renderTransform: inkUITransform;

@addField(inkWidget)
public native let effects: array<ref<inkIEffect>>;
