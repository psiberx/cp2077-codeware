@addField(inkWidget)
native let logicController: ref<inkLogicController>;

@addField(inkWidget)
native let secondaryControllers: array<ref<inkLogicController>>;

@addField(inkWidget)
native let userData: array<ref<inkUserData>>;

@addField(inkWidget)
native let name: CName;

@addField(inkWidget)
native let state: CName;

@addField(inkWidget)
native let visible: Bool;

@addField(inkWidget)
native let affectsLayoutWhenHidden: Bool;

@addField(inkWidget)
native let isInteractive: Bool;

@addField(inkWidget)
native let canSupportFocus: Bool;

@addField(inkWidget)
native let style: ref<inkStyleResourceWrapper>;

@addField(inkWidget)
native let parentWidget: wref<inkWidget>;

@addField(inkWidget)
native let propertyManager: ref<inkPropertyManager>;

@addField(inkWidget)
native let fitToContent: Bool;

@addField(inkWidget)
native let layout: inkWidgetLayout;

@addField(inkWidget)
native let opacity: Float;

@addField(inkWidget)
native let tintColor: HDRColor;

@addField(inkWidget)
native let size: Vector2;

@addField(inkWidget)
native let renderTransformPivot: Vector2;

@addField(inkWidget)
native let renderTransform: inkUITransform;

@addField(inkWidget)
native let effects: array<ref<inkIEffect>>;
