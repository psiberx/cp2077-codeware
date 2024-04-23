public native class physicsSystemResource extends CResource {
  native let bodies: array<ref<physicsSystemBody>>;
  native let joints: array<ref<physicsSystemJoint>>;
}
