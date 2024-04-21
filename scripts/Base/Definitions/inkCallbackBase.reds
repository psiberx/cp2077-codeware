public abstract native struct inkCallbackBase {
  native let callbackName: CName;
  native let listeners: array<inkCallbackListener>;
}
