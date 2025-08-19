public native struct locVoLanguageDataEntry {
  public native let languageCode: CName;
  public native let voiceverMapReport: ResourceAsyncRef; // raRef<JsonResource>
  public native let lengthMapReport: ResourceAsyncRef; // raRef<JsonResource>
  public native let voMapChunks: array<ResourceAsyncRef>;
}
