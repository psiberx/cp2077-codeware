public native struct oauthAuthenticationToken {
  native let token: String;
  native let secret: String;
  native let sessionHandle: String;
  native let tokenExpiresIn: Uint64;
  native let authorizationExpiresIn: Uint64;
}
