public native struct StackTraceEntry {
    public native let class: CName;
    public native let function: CName;
    public native let object: wref<IScriptable>;
}

public native func GetStackTrace(opt depth: Int32, opt current: Bool) -> array<StackTraceEntry>
