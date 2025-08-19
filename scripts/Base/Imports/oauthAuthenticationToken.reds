public native struct oauthAuthenticationToken {
  public native let token: String;
  public native let secret: String;
  public native let sessionHandle: String;
  public native let tokenExpiresIn: Uint64;
  public native let authorizationExpiresIn: Uint64;
}
