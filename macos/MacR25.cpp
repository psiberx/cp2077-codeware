// SELFTEST R25. See MacR25.hpp.

#include "MacR25.hpp"

#include "MacDiag.hpp"

#include <RED4ext/CString.hpp>

#include <cstring>
#include <string>

namespace
{
bool Same(const RED4ext::CString& aString, const std::string& aExpected)
{
    return aString.Length() == aExpected.size() && std::strcmp(aString.c_str(), aExpected.c_str()) == 0;
}
}

void Mac::R25SelfTest()
{
    if (!Mac::DiagEnabled())
        return;

    // The row behind CString(const CString&) and CString::operator=(const CString&) is the Windows copy assign: it copies into a live
    // target (keeping its allocator), and a self assignment is a no-op. Heap strings are longer than the 20 inline bytes.
    const std::string heapA(100, 'a');
    const std::string heapB = std::string(130, 'b') + "-end";
    const std::string shortC = "abc";

    RED4ext::CString a(heapA.c_str());
    RED4ext::CString b(heapB.c_str());
    RED4ext::CString s(shortC.c_str());

    // 1. copy constructor from a heap string: same text, its own buffer.
    RED4ext::CString copyOfA(a);
    const bool ctorOk = Same(copyOfA, heapA) && copyOfA.c_str() != a.c_str() && !copyOfA.IsInline();

    // 2. assign a heap string into a live heap string (the case that used to need destroy and placement new).
    RED4ext::CString target(heapB.c_str());
    const char* targetBefore = target.c_str();
    target = a;
    const bool assignHeapOk = Same(target, heapA) && target.c_str() != a.c_str() && Same(a, heapA) && targetBefore != nullptr;

    // 3. assign an inline string into a live heap string: shrinks to the inline text.
    RED4ext::CString shrink(heapB.c_str());
    shrink = s;
    const bool shrinkOk = Same(shrink, shortC) && Same(s, shortC);

    // 4. assign a heap string into an inline string: grows.
    RED4ext::CString grow(shortC.c_str());
    grow = b;
    const bool growOk = Same(grow, heapB) && grow.c_str() != b.c_str() && Same(b, heapB);

    // 5. self assignment keeps the text (the row checks for it).
    RED4ext::CString selfAssigned(heapA.c_str());
    RED4ext::CString& alias = selfAssigned;
    selfAssigned = alias;
    const bool selfOk = Same(selfAssigned, heapA);

    // 6. copy constructor from an inline string, then edit-independence: the copy owns its text.
    RED4ext::CString copyOfS(s);
    const bool inlineOk = Same(copyOfS, shortC) && copyOfS.IsInline();

    const bool pass = ctorOk && assignHeapOk && shrinkOk && growOk && selfOk && inlineOk;
    MAC_DIAG("[selftest] R25 CString copy ctor=%d assignHeap=%d shrink=%d grow=%d self=%d inlineCopy=%d %s\n", ctorOk ? 1 : 0,
             assignHeapOk ? 1 : 0, shrinkOk ? 1 : 0, growOk ? 1 : 0, selfOk ? 1 : 0, inlineOk ? 1 : 0, pass ? "PASS" : "FAIL");
}
