#pragma once

RTTI_EXPAND_CLASS(Red::CMaterialInstance, {
    RTTI_PROPERTY(params);
});

RTTI_EXPAND_CLASS(Red::CMeshMaterialEntry, {
    RTTI_PROPERTY(materialWeak, "material");
});
