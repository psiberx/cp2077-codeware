@neverRef()
public native class FunctionalTestsDataMemoryPoolStaticData extends ISerializable {
  public native let poolName: String;
  public native let budget: Int64;
  public native let childrenBudget: Int64;
  public native let children: array<String>;
  public native let parent: String;
}
