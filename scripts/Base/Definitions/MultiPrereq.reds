public importonly native class MultiPrereq extends IPrereq {
  native let aggregationType: gameAggregationType;
  native let nestedPrereqs: array<ref<IPrereq>>;
}
