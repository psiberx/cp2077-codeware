@addField(inkText)
public native let localizationString: LocalizationString;

@addField(inkText)
public native let textIdKey: CName;

@addField(inkText)
public native let text: String;

@addField(inkText)
public native let fontFamily: ResourceAsyncRef; // raRef<inkFontFamilyResource>

@addField(inkText)
public native let fontStyle: CName;

@addField(inkText)
public native let fontSize: Uint32;

@addField(inkText)
public native let font: ref<rendFont>;

@addField(inkText)
public native let letterCase: textLetterCase;

@addField(inkText)
public native let tracking: Uint32;

@addField(inkText)
public native let lockFontInGame: Bool;

@addField(inkText)
public native let wrappingInfo: textWrappingInfo;

@addField(inkText)
public native let lineHeightPercentage: Float;

@addField(inkText)
public native let justification: textJustificationType;

@addField(inkText)
public native let textHorizontalAlignment: textHorizontalAlignment;

@addField(inkText)
public native let textVerticalAlignment: textVerticalAlignment;

@addField(inkText)
public native let textOverflowPolicy: textOverflowPolicy;

@addField(inkText)
public native let scrollTextSpeed: Float;

@addField(inkText)
public native let scrollDelay: Uint16;

@addField(inkText)
public native let contentHAlign: inkEHorizontalAlign;

@addField(inkText)
public native let contentVAlign: inkEVerticalAlign;
