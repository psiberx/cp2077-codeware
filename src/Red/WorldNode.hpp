#pragma once

#include "Red/StreamingSector.hpp"

namespace Red
{
struct WorldNodeInstanceNodeState
{
    uint16_t isInitializing : 1; // 00
    uint16_t isInitialized : 1;  // 01
    uint16_t isAttaching : 1;    // 02
    uint16_t isDetaching : 1;    // 03
    uint16_t b04 : 1;            // 04
    uint16_t isAttached : 1;     // 05
    uint16_t b06 : 1;            // 06
    uint16_t b07 : 1;            // 07
    uint16_t b09 : 1;            // 08
    uint16_t isVisible : 1;      // 09
};
}

namespace Raw::WorldNodeInstance
{
// Game 2.5: worldMeshNodeInstance virtual 0x1A8 (0x28257E4) reads 0x30/0x50/0x60/0x70/0x88 like 2.31 (0x22759C4);
// the 12 shared slots that touch these offsets match. Subclass fields: mesh 0x98 (0x2825802), bended 0xA0
// (0x29745F2), decal 0xA0 (0x471874), foliage 0xB8 (0x62C56F), entity 0xA0 (0x29A610E), each in the same slot as 2.31.
using Transform = Core::OffsetPtr<0x30, Red::Transform>;
using Scale = Core::OffsetPtr<0x50, Red::Vector3>;
using Node = Core::OffsetPtr<0x60, Red::Handle<Red::worldNode>>;
using SetupInfo = Core::OffsetPtr<0x70, Red::CompiledNodeInstanceSetupInfo**>;
using NodeID = Core::OffsetPtr<0x80, uint64_t>;
using State = Core::OffsetPtr<0x88, Red::WorldNodeInstanceNodeState>;
}

namespace Raw::WorldMeshNodeInstance
{
using Mesh = Core::OffsetPtr<0x98, Red::Handle<Red::CMesh>>;
}

namespace Raw::WorldBendedMeshNodeInstance
{
using Mesh = Core::OffsetPtr<0xA0, Red::Handle<Red::CMesh>>;
}

namespace Raw::WorldStaticDecalNodeInstance
{
using Material = Core::OffsetPtr<0xA0, Red::Handle<Red::IMaterial>>;
}

namespace Raw::WorldFoliageNodeInstance
{
using Mesh = Core::OffsetPtr<0xB8, Red::Handle<Red::CMesh>>;
}

namespace Raw::WorldEntityNodeInstance
{
using Entity = Core::OffsetPtr<0xA0, Red::Handle<Red::Entity>>;
}
