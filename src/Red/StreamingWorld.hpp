#pragma once

namespace Raw::RuntimeSystemWorldStreaming
{
// Game 2.5: worldRuntimeSystemWorldStreaming virtual 0x128 (0x4C3BD4) `mov rax,[rcx+0x270]`, same slot as 2.31.
using StreamingWorld = Core::OffsetPtr<0x270, Red::Handle<Red::worldStreamingWorld>>;
}
