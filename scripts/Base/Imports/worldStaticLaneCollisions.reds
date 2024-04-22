public native struct worldStaticLaneCollisions {
  native let lane: worldTrafficLaneUID;
  native let collisions: array<worldTrafficStaticCollisionSphere>;
  native let deadEndStart: Float;
}
