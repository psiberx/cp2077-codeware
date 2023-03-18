@addMethod(inkWidgetRef)
public static native func Set(self: script_ref<inkWidgetRef>, widget: ref<inkWidget>);

@addMethod(inkBorderRef)
public static func Create(widget: ref<inkBorder>) -> inkBorderRef {
    let ref = new inkBorderRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkCacheRef)
public static func Create(widget: ref<inkCacheWidget>) -> inkCacheRef {
    let ref = new inkCacheRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkCanvasRef)
public static func Create(widget: ref<inkCanvas>) -> inkCanvasRef {
    let ref = new inkCanvasRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkCircleRef)
public static func Create(widget: ref<inkCircle>) -> inkCircleRef {
    let ref = new inkCircleRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkFlexRef)
public static func Create(widget: ref<inkFlex>) -> inkFlexRef {
    let ref = new inkFlexRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkGridRef)
public static func Create(widget: ref<inkGrid>) -> inkGridRef {
    let ref = new inkGridRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkHorizontalPanelRef)
public static func Create(widget: ref<inkHorizontalPanel>) -> inkHorizontalPanelRef {
    let ref = new inkHorizontalPanelRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkImageRef)
public static func Create(widget: ref<inkImage>) -> inkImageRef {
    let ref = new inkImageRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkMaskRef)
public static func Create(widget: ref<inkMask>) -> inkMaskRef {
    let ref = new inkMaskRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkRectangleRef)
public static func Create(widget: ref<inkRectangle>) -> inkRectangleRef {
    let ref = new inkRectangleRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkScrollAreaRef)
public static func Create(widget: ref<inkScrollArea>) -> inkScrollAreaRef {
    let ref = new inkScrollAreaRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkShapeRef)
public static func Create(widget: ref<inkShape>) -> inkShapeRef {
    let ref = new inkShapeRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkTextRef)
public static func Create(widget: ref<inkText>) -> inkTextRef {
    let ref = new inkTextRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkUniformGridRef)
public static func Create(widget: ref<inkUniformGrid>) -> inkUniformGridRef {
    let ref = new inkUniformGridRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkVerticalPanelRef)
public static func Create(widget: ref<inkVerticalPanel>) -> inkVerticalPanelRef {
    let ref = new inkVerticalPanelRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkVideoRef)
public static func Create(widget: ref<inkVideo>) -> inkVideoRef {
    let ref = new inkVideoRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}

@addMethod(inkVirtualCompoundRef)
public static func Create(widget: ref<inkVirtualCompoundWidget>) -> inkVirtualCompoundRef {
    let ref = new inkVirtualCompoundRef();
    inkWidgetRef.Set(ref, widget);
    return ref;
}
