@neverRef() public native class worldStreamingSector extends CResource {
    native let localInplaceResource: array<ResourceRef>;
    native let externInplaceResource: ResourceAsyncRef; // raRef<worldStreamingSectorInplaceContent>
    native let level: Uint8;
    native let category: worldStreamingSectorCategory;

    public native func GetNodes() -> array<ref<worldNode>>
    public native func GetNodeCount() -> Int32
    public native func GetNode(index: Int32) -> ref<worldNode>

    public native func GetNodeSetupCount() -> Int32
    public native func GetNodeSetup(index: Int32) -> ref<WorldNodeSetupWrapper>

    public native func GetNodeRefs() -> array<NodeRef>
    public native func GetNodeRefCount() -> Int32
    public native func GetNodeRef(index: Int32) -> NodeRef
}

