public native class DamagePack extends IScriptable {
  native let damageList: array<ref<Damage>>;

  public final native func AddDamage()
  public final native func GetDamageList()
  public final native func HasValidDamage()
}
