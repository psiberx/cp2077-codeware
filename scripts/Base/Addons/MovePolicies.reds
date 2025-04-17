@addField(MovePolicies)
native let destination: Vector3;

@addField(MovePolicies)
native let destinationTangent: Vector3;

@addField(MovePolicies)
native let startTangent: Vector3;

@addField(MovePolicies)
native let targetSmartObject: AIObjectId;

@addField(MovePolicies)
native let targetWorkspot: ref<SetupWorkspotActionEvent>;

@addField(MovePolicies)
native let targetSmartObjectHash: Uint64;

@addField(MovePolicies)
native let targetObject: wref<GameObject>;

@addField(MovePolicies)
native let strafingTarget: StrafingTarget;

@addField(MovePolicies)
native let useFollowSlots: Bool;

@addField(MovePolicies)
native let followSlotOverrides: [Vector3; 4];

@addField(MovePolicies)
native let hasLocalTargetOffset: Bool;

@addField(MovePolicies)
native let localTargetOffset: Vector3;

@addField(MovePolicies)
native let desiredDistance: Float;

@addField(MovePolicies)
native let toleranceRadius: Float;

@addField(MovePolicies)
native let minMovementDistance: Float;

@addField(MovePolicies)
native let strafingRotationOffset: Float;

@addField(MovePolicies)
native let minFollowerDistance: Float;

@addField(MovePolicies)
native let maxFollowerDistance: Float;

@addField(MovePolicies)
native let movementType: moveMovementType;

@addField(MovePolicies)
native let circlingDirection: moveCirclingDirection;

@addField(MovePolicies)
native let stopOnObstacle: Bool;

@addField(MovePolicies)
native let avoidObstacleWithinTolerance: Bool;

@addField(MovePolicies)
native let useCollisionAvoidance: Bool;

@addField(MovePolicies)
native let useDestReservation: Bool;

@addField(MovePolicies)
native let inRestrictedArea: Bool;

@addField(MovePolicies)
native let isSpline: Bool;

@addField(MovePolicies)
native let startFromClosestPoint: Bool;

@addField(MovePolicies)
native let ignoreNavigation: Bool;

@addField(MovePolicies)
native let useStart: Bool;

@addField(MovePolicies)
native let useStop: Bool;

@addField(MovePolicies)
native let isEvaluated: Bool;

@addField(MovePolicies)
native let useOffMeshAllowedTags: Bool;

@addField(MovePolicies)
native let useOffMeshBlockedTags: Bool;
