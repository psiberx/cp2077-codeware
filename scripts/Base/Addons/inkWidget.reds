@addField(inkWidget)
native let parentWidget: wref<inkWidget>;

@addField(inkWidget)
native let logicController: ref<inkLogicController>;

@addField(inkWidget)
native let secondaryControllers: array<ref<inkLogicController>>;

@addField(inkWidget)
native let userData: array<ref<inkUserData>>;

@addField(inkWidget)
native let canSupportFocus: Bool;

@addField(inkWidget)
native let effects: array<ref<inkIEffect>>;
