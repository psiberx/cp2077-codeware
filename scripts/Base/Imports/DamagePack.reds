public native class DamagePack extends IScriptable {
  public native let damageList: array<ref<Damage>>;

  public final native func AddDamage()
  public final native func GetDamageList()
  public final native func HasValidDamage()
}
