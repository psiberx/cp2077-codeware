public native class worldPatrolSplineNode extends worldSplineNode {
  native let patrolPointDefs: array<ref<worldPatrolSplinePointDefinition>>;
  native let patrolPoints: array<NodeRef>;
  native let spots: array<ref<worldTrafficSpotDefinition>>;
}
