public native class gameinteractionsCHotSpotAreaFilterDefinition extends gameinteractionsNodeDefinition {
  native let slotName: CName;
  native let transform: Transform;
  native let functor: ref<gameinteractionsCFunctorDefinition>;
  native let shapes: array<ref<gameinteractionsIShapeDefinition>>;
  native let negativeShapes: array<ref<gameinteractionsIShapeDefinition>>;
}
