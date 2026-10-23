public native class CodewareResourceTarget extends CodewareCallbackSystemTarget {
    public static native func Path(resourcePath: ResRef) -> ref<CodewareResourceTarget>
    public static native func Type(resourceType: CName) -> ref<CodewareResourceTarget>
}
