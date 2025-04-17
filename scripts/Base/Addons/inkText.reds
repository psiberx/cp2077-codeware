@addField(inkText)
native let localizationString: LocalizationString;

@addField(inkText)
native let textIdKey: CName;

@addField(inkText)
native let text: String;

@addField(inkText)
native let fontFamily: ResourceAsyncRef; // raRef<inkFontFamilyResource>

@addField(inkText)
native let fontStyle: CName;

@addField(inkText)
native let fontSize: Uint32;

@addField(inkText)
native let font: ref<rendFont>;

@addField(inkText)
native let letterCase: textLetterCase;

@addField(inkText)
native let tracking: Uint32;

@addField(inkText)
native let lockFontInGame: Bool;

@addField(inkText)
native let wrappingInfo: textWrappingInfo;

@addField(inkText)
native let lineHeightPercentage: Float;

@addField(inkText)
native let justification: textJustificationType;

@addField(inkText)
native let textHorizontalAlignment: textHorizontalAlignment;

@addField(inkText)
native let textVerticalAlignment: textVerticalAlignment;

@addField(inkText)
native let textOverflowPolicy: textOverflowPolicy;

@addField(inkText)
native let scrollTextSpeed: Float;

@addField(inkText)
native let scrollDelay: Uint16;

@addField(inkText)
native let contentHAlign: inkEHorizontalAlign;

@addField(inkText)
native let contentVAlign: inkEVerticalAlign;
