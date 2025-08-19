public native struct mpPersistentTestBoxState {
  public native let recordID: TweakDBID;
  public native let persistentID: Uint64;
  public native let isOn: Bool;
  public native let weakPersistentEntity: wref<mpPersistentTestBox>;
  public native let weakPersistentEntityComponent: wref<IComponent>;
  public native let weakDynamicEntity: wref<GameObject>;
  public native let weakDynamicEntityComponent: wref<IComponent>;
}
