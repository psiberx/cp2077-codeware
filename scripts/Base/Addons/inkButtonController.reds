@addField(inkButtonController)
public native let ButtonClick: inkButtonClickCallback;

@addField(inkButtonController)
public native let ButtonHoldComplete: inkButtonHoldCompleteCallback;

@addField(inkButtonController)
public native let ButtonStateChanged: inkButtonStateChangeCallback;

@addField(inkButtonController)
public native let ButtonSelectionChanged: inkButtonSelectionCallback;

@addField(inkButtonController)
public native let ButtonHoldProgressChanged: inkButtonProgressChangedCallback;

@addField(inkButtonController)
public native let canHold: Bool;

@addField(inkButtonController)
public native let selected: Bool;

@addField(inkButtonController)
public native let autoUpdateWidgetState: Bool;
