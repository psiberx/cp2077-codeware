#pragma once

namespace App
{
struct JobHandle
{
    JobHandle() = default;

    JobHandle(Red::JobHandle aJobHandle)
        : jobHandle(std::move(aJobHandle))
    {
    }

    inline operator const Red::JobHandle&() const
    {
        return jobHandle;
    }

    Red::JobHandle jobHandle;
};

struct JobGroup
{
    JobGroup()
        : jobGroup(nullptr)
    {
    }

    JobGroup(const Red::JobGroup& aJobGroup)
        : jobGroup(&aJobGroup)
    {
    }

    inline operator const Red::JobGroup&() const
    {
        return *jobGroup;
    }

    inline operator bool() const
    {
        return jobGroup;
    }

    [[nodiscard]] bool IsValid() const
    {
        return jobGroup;
    }

    const Red::JobGroup* jobGroup;
};

struct JobQueue : public Red::IScriptable
{
    JobQueue() = default;

    JobQueue(const Red::JobGroup& aJobGroup)
        : jobQueue(aJobGroup)
    {
    }

    inline static Red::Handle<JobQueue> Create(Red::Optional<JobGroup> aJobGroup)
    {
        if (aJobGroup)
            return Red::MakeHandle<JobQueue>(aJobGroup);

        return Red::MakeHandle<JobQueue>();
    }

    inline bool DispatchJob(const Red::Handle<Red::IScriptable>& aJob, Red::Optional<int32_t> aJobSize,
                            Red::Optional<int32_t> aBatchSize)
    {
        if (!aJob)
            return false;

        if (!aJobSize)
        {
            auto handleFunc = Red::GetMemberFunction(aJob, "Handle");

            if (!handleFunc || handleFunc->params.Size() > 1)
                return false;

            if (handleFunc->params.Size() > 0 && handleFunc->params[0]->type != Red::GetType<JobGroup>())
                return false;

            jobQueue.Dispatch([aJob, handleFunc](const Red::JobGroup& aJobGroup) {
                if (handleFunc->params.Size() > 0)
                {
                    Red::CallFunction(aJob, handleFunc, JobGroup(aJobGroup));
                }
                else
                {
                    Red::CallFunction(aJob, handleFunc);
                }
            });
        }
        else
        {
            auto handleFunc = Red::GetMemberFunction(aJob, "Handle");

            if (!handleFunc || handleFunc->params.Size() < 2 || handleFunc->params.Size() > 3)
                return false;

            if (handleFunc->params.Size() > 2 && handleFunc->params[2]->type != Red::GetType<JobGroup>())
                return false;

            if (handleFunc->params[0]->type != Red::GetType<int32_t>())
                return false;

            if (handleFunc->params[1]->type != Red::GetType<int32_t>())
                return false;

            auto finishFunc = Red::GetMemberFunction(aJob, "Finish");

            if (finishFunc)
            {
                if (finishFunc->params.Size() > 2)
                    return false;

                if (finishFunc->params.Size() > 1 && finishFunc->params[1]->type != Red::GetType<JobGroup>())
                    return false;

                if (finishFunc->params.Size() > 0 && finishFunc->params[0]->type != Red::GetType<int32_t>())
                    return false;
            }

            jobQueue.Dispatch(
                [aJob, handleFunc](uint32_t aFrom, uint32_t aTo, const Red::JobGroup& aJobGroup) {
                    if (handleFunc->params.Size() > 2)
                    {
                        Red::CallFunction(aJob, handleFunc, static_cast<int32_t>(aFrom), static_cast<int32_t>(aTo),
                                          JobGroup(aJobGroup));
                    }
                    else if (handleFunc->params.Size() > 0)
                    {
                        Red::CallFunction(aJob, handleFunc, static_cast<int32_t>(aFrom), static_cast<int32_t>(aTo));
                    }
                    else
                    {
                        Red::CallFunction(aJob, handleFunc);
                    }
                },
                [aJob, finishFunc](uint32_t aJobSize, const Red::JobGroup& aJobGroup) {
                    if (!finishFunc)
                        return;

                    if (finishFunc->params.Size() > 1)
                    {
                        Red::CallFunction(aJob, finishFunc, static_cast<int32_t>(aJobSize), JobGroup(aJobGroup));
                    }
                    else if (finishFunc->params.Size() > 0)
                    {
                        Red::CallFunction(aJob, finishFunc, static_cast<int32_t>(aJobSize));
                    }
                    else
                    {
                        Red::CallFunction(aJob, finishFunc);
                    }
                },
                aJobSize);
        }

        return true;
    }

    inline void DispatchWait(const JobHandle& aJobHandle)
    {
        jobQueue.Wait(aJobHandle);
    }

    inline JobHandle Finalize()
    {
        return jobQueue.Capture();
    }

    inline void SyncWaitUntilFinished(Red::Optional<uint32_t, 60000> aTimeout)
    {
        Red::WaitForQueue(jobQueue, std::chrono::milliseconds(aTimeout));
    }

    Red::JobQueue jobQueue;

    RTTI_IMPL_TYPEINFO(JobQueue);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::JobHandle);

RTTI_DEFINE_CLASS(App::JobGroup, {
    RTTI_METHOD(IsValid);
});

RTTI_DEFINE_CLASS(App::JobQueue, {
    RTTI_METHOD(Create);
    RTTI_METHOD(DispatchJob);
    RTTI_METHOD(DispatchWait);
    RTTI_METHOD(SyncWaitUntilFinished);
    RTTI_METHOD(Finalize);
});
