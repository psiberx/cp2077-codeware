@addMethod(inkWidgetRef)
public static native func Set(self: script_ref<inkWidgetRef>, widget: ref<inkWidget>);

@addMethod(inkWidgetRef)
public static func Create(widget: ref<inkWidget>) -> inkWidgetRef {
    let ref: inkWidgetRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkBorderRef)
public static func Create(widget: ref<inkBorder>) -> inkBorderRef {
    let ref: inkBorderRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkCacheRef)
public static func Create(widget: ref<inkCacheWidget>) -> inkCacheRef {
    let ref: inkCacheRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkCanvasRef)
public static func Create(widget: ref<inkCanvas>) -> inkCanvasRef {
    let ref: inkCanvasRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkCircleRef)
public static func Create(widget: ref<inkCircle>) -> inkCircleRef {
    let ref: inkCircleRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkFlexRef)
public static func Create(widget: ref<inkFlex>) -> inkFlexRef {
    let ref: inkFlexRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkGridRef)
public static func Create(widget: ref<inkGrid>) -> inkGridRef {
    let ref: inkGridRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkHorizontalPanelRef)
public static func Create(widget: ref<inkHorizontalPanel>) -> inkHorizontalPanelRef {
    let ref: inkHorizontalPanelRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkImageRef)
public static func Create(widget: ref<inkImage>) -> inkImageRef {
    let ref: inkImageRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkMaskRef)
public static func Create(widget: ref<inkMask>) -> inkMaskRef {
    let ref: inkMaskRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkRectangleRef)
public static func Create(widget: ref<inkRectangle>) -> inkRectangleRef {
    let ref: inkRectangleRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkScrollAreaRef)
public static func Create(widget: ref<inkScrollArea>) -> inkScrollAreaRef {
    let ref: inkScrollAreaRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkShapeRef)
public static func Create(widget: ref<inkShape>) -> inkShapeRef {
    let ref: inkShapeRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkTextRef)
public static func Create(widget: ref<inkText>) -> inkTextRef {
    let ref: inkTextRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkUniformGridRef)
public static func Create(widget: ref<inkUniformGrid>) -> inkUniformGridRef {
    let ref: inkUniformGridRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkVerticalPanelRef)
public static func Create(widget: ref<inkVerticalPanel>) -> inkVerticalPanelRef {
    let ref: inkVerticalPanelRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkVideoRef)
public static func Create(widget: ref<inkVideo>) -> inkVideoRef {
    let ref: inkVideoRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkVirtualCompoundRef)
public static func Create(widget: ref<inkVirtualCompoundWidget>) -> inkVirtualCompoundRef {
    let ref: inkVirtualCompoundRef;
    inkWidgetRef.Set(ref, widget);
    return ref;
}
