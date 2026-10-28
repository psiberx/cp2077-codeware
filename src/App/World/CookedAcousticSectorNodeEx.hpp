#pragma once

namespace App
{
struct CookedAcousticSectorNodeEx : Red::worldCookedAcousticSectorNode
{
    [[nodiscard]] int32_t GetInnerNodeCount()
    {
        auto innerNodes = GetInnerNodes();

        return static_cast<int32_t>(innerNodes.Size());
    }

    [[nodiscard]] Red::ScriptRef<Red::worldCookedAcousticSectorInnerNode> GetInnerNode(int32_t aIndex)
    {
        auto innerNodes = GetInnerNodes();

        if (aIndex < 0 || aIndex >= innerNodes.Size())
            return {};

        return {innerNodes[aIndex]};
    }
};
}

RTTI_EXPAND_CLASS(Red::worldCookedAcousticSectorNode, App::CookedAcousticSectorNodeEx, {
    RTTI_PROPERTY(generatorId);
    RTTI_METHOD(GetInnerNodeCount);
    RTTI_METHOD(GetInnerNode);
});

RTTI_DEFINE_CLASS(Red::worldCookedAcousticSectorInnerNode , {
    RTTI_PROPERTY(data);
    RTTI_PROPERTY(inSectorCoordsX);
    RTTI_PROPERTY(inSectorCoordsY);
    RTTI_PROPERTY(inSectorCoordsZ);
    RTTI_PROPERTY(edgeMask);
});
