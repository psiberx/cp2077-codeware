@addField(inkSliderController)
public native let slidingAreaRef: inkWidgetRef;

@addField(inkSliderController)
public native let handleRef: inkWidgetRef;

@addField(inkSliderController)
public native let nextRef: inkWidgetRef;

@addField(inkSliderController)
public native let priorRef: inkWidgetRef;

@addField(inkSliderController)
public native let direction: inkESliderDirection;

@addField(inkSliderController)
public native let autoSizeHandle: Bool;

@addField(inkSliderController)
public native let minHandleSize: Float;

@addField(inkSliderController)
public native let maxHandleSize: Float;

@addField(inkSliderController)
public native let percentHandleSize: Float;

@addField(inkSliderController)
public native let currentProgress: Float;

@addField(inkSliderController)
public native let minimumValue: Float;

@addField(inkSliderController)
public native let maximumValue: Float;

@addField(inkSliderController)
public native let step: Float;

@addField(inkSliderController)
public native let SliderInput: inkSliderControllerInputCallback;

@addField(inkSliderController)
public native let SliderValueChanged: inkSliderControllerValueChangeCallback;

@addField(inkSliderController)
public native let SliderHandleReleased: inkSliderControllerHandleReleasedCallback;
