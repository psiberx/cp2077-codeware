public native struct ConsumableParameterWeakIScriptable {
  native let name: CName;
  native let value: wref<IScriptable>;

  native let consumed: Bool;
}
