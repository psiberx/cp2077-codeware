public native struct toolsMessage {
  native let severity: toolsMessageSeverity;
  native let created: Int64;
  native let location: ref<toolsIMessageLocation>;
  native let tokens: array<ref<toolsIMessageToken>>;
  native let verbosity: toolsMessageVerbosity;
}
