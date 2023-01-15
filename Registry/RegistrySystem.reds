// -----------------------------------------------------------------------------
// Codeware.Registry.RegistrySystem
// -----------------------------------------------------------------------------
//
// - Global object registry / singleton container
//
// -----------------------------------------------------------------------------
//
// public class RegistrySystem extends ScriptableSystem {
//   public func Get(name: CName) -> ref<IScriptable>
//   public func Put(name: CName, instance: ref<IScriptable>)
//   public func Put(instance: ref<IScriptable>)
//   public func Remove(name: CName)
//   public func Remove(instance: ref<IScriptable>)
//   public static func GetInstance(game: GameInstance) -> ref<RegistrySystem>
// }
//

module Codeware.Registry

public class RegistrySystem extends ScriptableSystem {
    private let m_container: ref<inkHashMap>;

    private func OnAttach() {
        this.m_container = new inkHashMap();
    }

    private func Key(name: CName) -> Uint64 {
        return TDBID.ToNumber(TDBID.Create(NameToString(name)));
    }

    public func Get(name: CName) -> ref<IScriptable> {
        let key: Uint64 = this.Key(name);

        return this.m_container.Get(key);
    }

    public func Put(name: CName, instance: ref<IScriptable>) {
        let key: Uint64 = this.Key(name);

        if this.m_container.KeyExist(key) {
            this.m_container.Set(key, instance);
        } else {
            this.m_container.Insert(key, instance);
        }
    }

    public func Put(instance: ref<IScriptable>) {
        this.Put(instance.GetClassName(), instance);
    }

    public func Remove(name: CName) {
        let key: Uint64 = this.Key(name);

        if this.m_container.KeyExist(key) {
            this.m_container.Remove(key);
        }
    }

    public func Remove(instance: ref<IScriptable>) {
        this.Remove(instance.GetClassName());
    }

    public static func GetInstance(game: GameInstance) -> ref<RegistrySystem> {
        return GameInstance.GetScriptableSystemsContainer(game).Get(n"Codeware.Registry.RegistrySystem") as RegistrySystem;
    }
}
