public native class physicsFilterData extends ISerializable {
  public native let simulationFilter: SimulationFilter;
  public native let queryFilter: QueryFilter;
  public native let preset: CName;
  public native let customFilterData: ref<physicsCustomFilterData>;
}
