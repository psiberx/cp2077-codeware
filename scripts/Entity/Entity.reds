@addMethod(Entity)
public native func GetTemplatePath() -> ResRef

@addMethod(Entity)
public native func GetComponents() -> array<ref<IComponent>>

@addMethod(Entity)
public native func AddComponent(component: ref<IComponent>)
