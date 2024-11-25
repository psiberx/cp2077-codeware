public native class EntityTarget extends CallbackSystemTarget {
    public static native func ID(entityID: EntityID) -> ref<EntityTarget>
    public static native func Type(entityType: CName) -> ref<EntityTarget>
    public static native func RecordID(recordID: TweakDBID) -> ref<EntityTarget>
    public static native func Template(templatePath: ResRef) -> ref<EntityTarget>
    public static native func Appearance(appearanceName: CName) -> ref<EntityTarget>
    public static native func Definition(appearancePath: ResRef, opt definitionName: CName) -> ref<EntityTarget>
}
