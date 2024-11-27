#pragma once

namespace Red
{
struct VisualController
{
    using AllocatorType = Memory::ComponentAllocator;

    struct AppearanceDependency
    {
        SharedPtr<ResourceToken<CMesh>> token; // 00
        Handle<meshMeshAppearance> appearance; // 10
        RaRef<CMesh> mesh;                     // 20
        CName appearanceName;                  // 28
    };
    RED4EXT_ASSERT_SIZE(AppearanceDependency, 0x30);
    RED4EXT_ASSERT_OFFSET(AppearanceDependency, mesh, 0x20);

    WeakPtr<VisualController> self;                         // 00
    DynArray<AppearanceDependency> dependencies;            // 10
    DynArray<SharedPtr<ResourceToken<>>> looseDependencies; // 20
    uint8_t unk30[0x50 - 0x30];                             // 30
    SharedPtr<ResourceToken<>> unk50;                       // 50
    SharedPtr<ResourceToken<>> unk60;                       // 60
    JobHandle job;                                          // 70
    volatile int32_t status;                                // 78
    SharedSpinLock lock;                                    // 7C
};
RED4EXT_ASSERT_SIZE(VisualController, 0x80);
RED4EXT_ASSERT_OFFSET(VisualController, dependencies, 0x10);
RED4EXT_ASSERT_OFFSET(VisualController, lock, 0x7C);
}

namespace Raw::VisualController
{
constexpr auto LoadDependencies = Core::RawFunc<
    /* addr = */ Red::AddressLib::VisualController_LoadDependencies,
    /* type = */ uintptr_t (*)(Red::VisualController* aController, Red::JobHandle& aOut, uint8_t a3)>();
}

namespace Raw::VisualControllerComponent
{
using Controller = Core::OffsetPtr<0xD8, Red::SharedPtr<Red::VisualController>>;
}
