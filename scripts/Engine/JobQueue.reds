public native struct JobHandle {}

public native struct JobGroup {
    public static native func IsValid(group: JobGroup) -> Bool
}

public native class JobQueue {
    public native func DispatchJob(job: ref<IScriptable>, opt size: Int32, opt batch: Int32) -> Bool
    public native func DispatchWait(job: JobHandle)
    public native func Finalize() -> JobHandle
    public native func SyncWaitUntilFinished(opt timeout: Uint32)

    public static native func Create(opt group: JobGroup) -> ref<JobQueue>
}
