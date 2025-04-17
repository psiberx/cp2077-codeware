@addField(HotSpotLayerDefinition)
native let group: gameinteractionsEGroupType;

@addField(HotSpotLayerDefinition)
native let priorityMultiplier: Float;

@addField(HotSpotLayerDefinition)
native let areaFilterDefinition: ref<gameinteractionsCHotSpotAreaFilterDefinition>;

@addField(HotSpotLayerDefinition)
native let gameLogicFilterDefinition: ref<gameinteractionsCHotSpotGameLogicFilterDefinition>;
