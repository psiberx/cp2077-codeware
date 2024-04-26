@addMethod(Entity)
public native func GetTemplatePath() -> ResRef

@addMethod(Entity)
public native func GetComponents() -> array<ref<IComponent>>

@addMethod(Entity)
public native func FindComponentByType(type: CName) -> ref<IComponent>

@addMethod(Entity)
public native func AddComponent(component: ref<IComponent>)

@addMethod(Entity)
public native func ApplyMorphTarget(target: CName, region: CName, value: Float) -> Bool

@addMethod(Entity)
public native func SetWorldTransform(transform: WorldTransform)
