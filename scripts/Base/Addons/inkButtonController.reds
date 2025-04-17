@addField(inkButtonController)
native let ButtonClick: inkButtonClickCallback;

@addField(inkButtonController)
native let ButtonHoldComplete: inkButtonHoldCompleteCallback;

@addField(inkButtonController)
native let ButtonStateChanged: inkButtonStateChangeCallback;

@addField(inkButtonController)
native let ButtonSelectionChanged: inkButtonSelectionCallback;

@addField(inkButtonController)
native let ButtonHoldProgressChanged: inkButtonProgressChangedCallback;

@addField(inkButtonController)
native let canHold: Bool;

@addField(inkButtonController)
native let selected: Bool;

@addField(inkButtonController)
native let autoUpdateWidgetState: Bool;
