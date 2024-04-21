public native struct worldTrafficLightDefinition {
  native let positionOnLane: Float;
  native let groupIdx: Uint32;
  native let extent: Float;
  native let timeline: array<worldTrafficLightStage>;
}
