public native struct locVoLanguageDataEntry {
  native let languageCode: CName;
  native let voiceverMapReport: ResourceAsyncRef; // raRef<JsonResource>
  native let lengthMapReport: ResourceAsyncRef; // raRef<JsonResource>
  native let voMapChunks: array<ResourceAsyncRef>;
}
