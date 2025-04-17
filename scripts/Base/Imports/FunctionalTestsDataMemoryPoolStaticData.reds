@neverRef()
public native class FunctionalTestsDataMemoryPoolStaticData extends ISerializable {
  native let poolName: String;
  native let budget: Int64;
  native let childrenBudget: Int64;
  native let children: array<String>;
  native let parent: String;
}
