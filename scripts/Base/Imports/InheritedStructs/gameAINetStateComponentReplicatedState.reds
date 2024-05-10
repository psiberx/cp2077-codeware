public native struct gameAINetStateComponentReplicatedState {
  native let componentName: CName;
  native let enabled: Bool;
  native let replHighLevelState: gameNetAIState;
  native let replUpperBodyState: gameNetAIState;
  native let replStanceState: gameNetAIState;
  native let replHitReactionModeState: gameNetAIState;
  native let replBehaviorState: gameNetAIState;
  native let replPhaseState: gameNetAIState;
  native let replDefenseMode: gameNetAIState;
  native let replLocomotionMode: gameNetAIState;
}
