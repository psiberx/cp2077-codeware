public native class toolsJiraSearchIssuesResult extends ISerializable {
  native let startAt: Uint32;
  native let maxResults: Uint32;
  native let total: Uint32;
  native let issues: array<toolsJiraIssue>;
  native let errorMessages: array<String>;
  native let warningMessages: array<String>;
}
