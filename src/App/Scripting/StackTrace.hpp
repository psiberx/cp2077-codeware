#pragma once

namespace App
{
struct StackTraceEntry
{
    StackTraceEntry() = default;

    StackTraceEntry(Red::CName aClass, Red::CName aFunction,
                    Red::WeakHandle<Red::IScriptable> aObject)
        : m_class(aClass)
        , m_function(aFunction)
        , m_object(std::move(aObject))
    {
    }

    Red::CName m_class;
    Red::CName m_function;
    Red::WeakHandle<Red::IScriptable> m_object;
};

inline Red::DynArray<StackTraceEntry> GetStackTrace(Red::Optional<int32_t> aDepth, Red::Optional<bool> aWithCurrent,
                                                    Red::CStackFrame* aFrame)
{
    Red::DynArray<StackTraceEntry> trace;

    auto frame = aFrame->parent;

    if (!frame)
    {
        return trace;
    }

    if (!aWithCurrent)
    {
        frame = frame->parent;
    }

    auto depth = std::max(1, std::min(128, aDepth.value));
    while (depth > 0 && frame && frame->func)
    {
        Red::CName className;
        if (!frame->func->flags.isStatic && frame->context && frame->context->ref.instance)
        {
            className = frame->context->GetType()->name;
        }

        trace.EmplaceBack(className, frame->func->fullName, Red::AsWeakHandle(frame->context));

        frame = frame->parent;
        --depth;
    }

    return trace;
}
}

RTTI_DEFINE_CLASS(App::StackTraceEntry, {
    RTTI_PROPERTY(m_class);
    RTTI_PROPERTY(m_function);
    RTTI_PROPERTY(m_object);
});

RTTI_DEFINE_GLOBALS(App, {
    RTTI_FUNCTION(GetStackTrace);
});
