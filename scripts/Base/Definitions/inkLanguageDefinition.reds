public native struct inkLanguageDefinition {
  native let languageCode: CName;
  native let isoScriptCode: CName;
  native let textDirection: inkETextDirection;
  native let fonts: array<inkLanguageFont>;
}
