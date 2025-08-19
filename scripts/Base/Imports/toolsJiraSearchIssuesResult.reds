public native class toolsJiraSearchIssuesResult extends ISerializable {
  public native let startAt: Uint32;
  public native let maxResults: Uint32;
  public native let total: Uint32;
  public native let issues: array<toolsJiraIssue>;
  public native let errorMessages: array<String>;
  public native let warningMessages: array<String>;
}
