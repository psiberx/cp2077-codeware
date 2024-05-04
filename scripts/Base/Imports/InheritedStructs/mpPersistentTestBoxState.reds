public native struct mpPersistentTestBoxState {
  native let recordID: TweakDBID;
  native let persistentID: Uint64;

  native let isOn: Bool;
  native let weakPersistentEntity: wref<mpPersistentTestBox>;
  native let weakPersistentEntityComponent: wref<IComponent>;
  native let weakDynamicEntity: wref<GameObject>;
  native let weakDynamicEntityComponent: wref<IComponent>;
}
