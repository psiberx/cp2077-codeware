#pragma once

namespace App
{
struct CookedStaticDecalNodeEx : Red::worldCookedStaticDecalNode
{
    [[nodiscard]] int32_t GetInnerNodeCount()
    {
        auto innerNodes = GetInnerNodes();

        return static_cast<int32_t>(innerNodes.Size());
    }

    [[nodiscard]] Red::ScriptRef<Red::worldCookedStaticDecalInnerNode> GetInnerNode(int32_t aIndex)
    {
        auto innerNodes = GetInnerNodes();

        if (aIndex < 0 || aIndex >= innerNodes.Size())
            return {};

        return {innerNodes[aIndex]};
    }
};
}

RTTI_EXPAND_CLASS(Red::worldCookedStaticDecalNode, App::CookedStaticDecalNodeEx, {
    RTTI_PROPERTY(diffuseColorScales);
    RTTI_METHOD(GetInnerNodeCount);
    RTTI_METHOD(GetInnerNode);
});

RTTI_DEFINE_CLASS(Red::worldCookedStaticDecalInnerNode, {
    RTTI_PROPERTY(material);
    RTTI_PROPERTY(forcedAutoHideDistance);
    RTTI_PROPERTY(autoHideDistance);
    RTTI_PROPERTY(alpha);
    RTTI_PROPERTY(normalThreshold);
    RTTI_PROPERTY(roughnessScale);
    RTTI_PROPERTY(orderNo);
    RTTI_PROPERTY(diffuseColorScaleIndex);
    RTTI_PROPERTY(surfaceType);
    RTTI_PROPERTY(decalRenderMode);
    RTTI_PROPERTY(normalsBlendingMode);
    RTTI_PROPERTY(flags);
});
