public native class EntityBuilderWrapper {
    public native func HasEntity() -> Bool
    public native func HasAppearance() -> Bool
    public native func HasCustomAppearances() -> Bool
    public native func GetRecordID() -> TweakDBID
    public native func GetTemplatePath() -> ResRef
    public native func GetAppearanceName() -> CName
    public native func GetEntityID() -> EntityID
    public native func GetEntityType() -> CName
    public native func GetEntityParams() -> ref<entEntityParametersStorage>
    public native func GetTemplate() -> ref<EntityBuilderTemplateWrapper>
    public native func GetAppearance() -> ref<EntityBuilderAppearanceWrapper>
    public native func GetCustomAppearances() -> array<ref<EntityBuilderAppearanceWrapper>>
}

public native class EntityBuilderTemplateWrapper {
    public native func GetResource() -> ref<entEntityTemplate>
    public native func GetAppearanceName() -> CName
    public native func GetEntity() -> ref<Entity>
    public native func GetComponents() -> array<ref<IComponent>>
    public native func AddComponent(component: ref<IComponent>)
}

public native class EntityBuilderAppearanceWrapper {
    public native func GetResource() -> ref<appearanceAppearanceResource>
    public native func GetDefinition() -> ref<appearanceAppearanceDefinition>
    public native func GetComponents() -> array<ref<IComponent>>
    public native func AddComponent(component: ref<IComponent>)
}
