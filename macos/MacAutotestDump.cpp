// R27, TEST-ONLY (tools/autotest). A generic dump of a game object through the RTTI: class, properties, handles, arrays. The
// in-world test harness uses it to read what a merged quest phase actually contains (nodes, sockets, conditions), because the
// mod archives are Oodle-compressed and cannot be read offline.
//
// Gated by the environment variable CP2077_AUTOTEST=1 (the harness sets it; a normal game never does). Read only: it never
// writes into the object. Output goes to stderr as "[dump] ..." lines.

#include <RED4ext/RED4ext.hpp>

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <string>

namespace
{
struct DumpState
{
    int maxDepth = 6;
    int budget = 20000; // lines
    int arrayCap = 80;  // elements per array
    std::set<const void*> seen;
};

bool Enabled()
{
    const char* value = std::getenv("CP2077_AUTOTEST");
    return value && std::strcmp(value, "1") == 0;
}

void Line(DumpState& aState, int aDepth, const char* aFormat, ...) __attribute__((format(printf, 3, 4)));

void Line(DumpState& aState, int aDepth, const char* aFormat, ...)
{
    if (aState.budget <= 0)
        return;
    --aState.budget;
    char buffer[1024];
    va_list args;
    va_start(args, aFormat);
    std::vsnprintf(buffer, sizeof(buffer), aFormat, args);
    va_end(args);
    std::fprintf(stderr, "[dump] %*s%s\n", aDepth * 2, "", buffer);
}

std::string TypeText(RED4ext::CBaseRTTIType* aType, void* aPtr)
{
    if (!aType || !aPtr)
        return "<null>";
    RED4ext::CString text;
    if (!aType->ToString(aPtr, text))
        return "<?>";
    const char* c = text.c_str();
    return c ? c : "";
}

void DumpValue(DumpState& aState, int aDepth, const char* aName, RED4ext::CBaseRTTIType* aType, void* aPtr);
void DumpObject(DumpState& aState, int aDepth, const char* aName, RED4ext::ISerializable* aObject);

void DumpStruct(DumpState& aState, int aDepth, RED4ext::CClass* aClass, void* aBase)
{
    for (auto* cls = aClass; cls; cls = cls->parent)
    {
        for (uint32_t i = 0; i < cls->props.Size(); ++i)
        {
            auto* prop = cls->props[i];
            if (!prop || !prop->type)
                continue;
            DumpValue(aState, aDepth, prop->name.ToString(), prop->type, prop->GetValuePtr<void>(aBase));
        }
    }
}

void DumpObject(DumpState& aState, int aDepth, const char* aName, RED4ext::ISerializable* aObject)
{
    if (!aObject)
    {
        Line(aState, aDepth, "%s = null", aName);
        return;
    }

    auto* cls = aObject->GetType();
    const char* className = cls ? cls->name.ToString() : "?";
    if (aState.seen.count(aObject))
    {
        Line(aState, aDepth, "%s = %s @%p (already dumped)", aName, className, static_cast<void*>(aObject));
        return;
    }
    aState.seen.insert(aObject);

    if (aDepth >= aState.maxDepth)
    {
        Line(aState, aDepth, "%s = %s @%p (depth limit)", aName, className, static_cast<void*>(aObject));
        return;
    }

    Line(aState, aDepth, "%s = %s @%p {", aName, className, static_cast<void*>(aObject));
    if (cls)
        DumpStruct(aState, aDepth + 1, cls, aObject);
    Line(aState, aDepth, "}");
}

void DumpValue(DumpState& aState, int aDepth, const char* aName, RED4ext::CBaseRTTIType* aType, void* aPtr)
{
    using RED4ext::ERTTIType;

    if (aState.budget <= 0 || !aType || !aPtr)
        return;

    switch (aType->GetType())
    {
    case ERTTIType::Class:
    {
        auto* cls = static_cast<RED4ext::CClass*>(aType);
        Line(aState, aDepth, "%s = struct %s {", aName, cls->name.ToString());
        DumpStruct(aState, aDepth + 1, cls, aPtr);
        Line(aState, aDepth, "}");
        break;
    }
    case ERTTIType::Handle:
    {
        auto* handle = static_cast<RED4ext::Handle<RED4ext::ISerializable>*>(aPtr);
        DumpObject(aState, aDepth, aName, handle->instance);
        break;
    }
    case ERTTIType::WeakHandle:
    {
        // Not followed (cycles): the target class and address, so that it can be matched with the "@address" of a dumped object.
        // A weak handle keeps its instance pointer after the object is gone: only a handle whose reference block still has a strong
        // reference is dereferenced (a stale one crashed the first dump of a nested phase).
        auto* handle = static_cast<RED4ext::WeakHandle<RED4ext::ISerializable>*>(aPtr);
        auto* target = handle->instance;
        if (!target)
        {
            Line(aState, aDepth, "%s -> null", aName);
        }
        else if (!handle->refCount || handle->refCount->strongRefs == 0)
        {
            Line(aState, aDepth, "%s -> (expired) @%p", aName, static_cast<void*>(target));
        }
        else
        {
            Line(aState, aDepth, "%s -> %s @%p", aName, target->GetType() ? target->GetType()->name.ToString() : "?", static_cast<void*>(target));
        }
        break;
    }
    case ERTTIType::Array:
    case ERTTIType::StaticArray:
    case ERTTIType::NativeArray:
    {
        auto* arrayType = static_cast<RED4ext::CRTTIBaseArrayType*>(aType);
        const uint32_t length = arrayType->GetLength(aPtr);
        if (length > 1000000u)
        {
            Line(aState, aDepth, "%s = [implausible length %u]", aName, length);
            break;
        }
        auto* inner = arrayType->GetInnerType();
        Line(aState, aDepth, "%s = [%u x %s]%s", aName, length, inner ? inner->GetName().ToString() : "?", length ? " {" : "");
        if (length)
        {
            const uint32_t shown = length < static_cast<uint32_t>(aState.arrayCap) ? length : static_cast<uint32_t>(aState.arrayCap);
            for (uint32_t i = 0; i < shown; ++i)
            {
                char label[32];
                std::snprintf(label, sizeof(label), "[%u]", i);
                DumpValue(aState, aDepth + 1, label, inner, arrayType->GetElement(aPtr, i));
            }
            if (shown < length)
                Line(aState, aDepth + 1, "... %u more", length - shown);
            Line(aState, aDepth, "}");
        }
        break;
    }
    case ERTTIType::Name:
    {
        auto* name = static_cast<RED4ext::CName*>(aPtr);
        Line(aState, aDepth, "%s = CName \"%s\" (0x%llx)", aName, name->ToString(), static_cast<unsigned long long>(name->hash));
        break;
    }
    default:
    {
        const std::string text = TypeText(aType, aPtr);
        Line(aState, aDepth, "%s = %s: %.200s", aName, aType->GetName().ToString(), text.c_str());
        break;
    }
    }
}
} // namespace

// Dumps aObject (a handle's target) and what it owns. aLabel names the dump in the log.
extern "C" void cw_autotest_dump_object(RED4ext::ISerializable* aObject, int aMaxDepth, int aArrayCap, const char* aLabel)
{
    if (!Enabled())
        return;

    DumpState state;
    if (aMaxDepth > 0)
        state.maxDepth = aMaxDepth;
    if (aArrayCap > 0)
        state.arrayCap = aArrayCap;

    std::fprintf(stderr, "[dump] ===== BEGIN %s =====\n", aLabel ? aLabel : "?");
    DumpObject(state, 0, "root", aObject);
    std::fprintf(stderr, "[dump] ===== END %s (%d lines left of 20000) =====\n", aLabel ? aLabel : "?", state.budget);
    std::fflush(stderr);
}
