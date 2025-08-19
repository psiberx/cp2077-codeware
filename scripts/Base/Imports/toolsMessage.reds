public native struct toolsMessage {
  public native let severity: toolsMessageSeverity;
  public native let created: Int64;
  public native let location: ref<toolsIMessageLocation>;
  public native let tokens: array<ref<toolsIMessageToken>>;
  public native let verbosity: toolsMessageVerbosity;
}
