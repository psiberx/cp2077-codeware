public native struct worldStaticLaneCollisions {
  public native let lane: worldTrafficLaneUID;
  public native let collisions: array<worldTrafficStaticCollisionSphere>;
  public native let deadEndStart: Float;
}
