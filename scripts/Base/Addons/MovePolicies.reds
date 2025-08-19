@addField(MovePolicies)
public native let destination: Vector3;

@addField(MovePolicies)
public native let destinationTangent: Vector3;

@addField(MovePolicies)
public native let startTangent: Vector3;

@addField(MovePolicies)
public native let targetSmartObject: AIObjectId;

@addField(MovePolicies)
public native let targetWorkspot: ref<SetupWorkspotActionEvent>;

@addField(MovePolicies)
public native let targetSmartObjectHash: Uint64;

@addField(MovePolicies)
public native let targetObject: wref<GameObject>;

@addField(MovePolicies)
public native let strafingTarget: StrafingTarget;

@addField(MovePolicies)
public native let useFollowSlots: Bool;

@addField(MovePolicies)
public native let followSlotOverrides: [Vector3; 4];

@addField(MovePolicies)
public native let hasLocalTargetOffset: Bool;

@addField(MovePolicies)
public native let localTargetOffset: Vector3;

@addField(MovePolicies)
public native let desiredDistance: Float;

@addField(MovePolicies)
public native let toleranceRadius: Float;

@addField(MovePolicies)
public native let minMovementDistance: Float;

@addField(MovePolicies)
public native let strafingRotationOffset: Float;

@addField(MovePolicies)
public native let minFollowerDistance: Float;

@addField(MovePolicies)
public native let maxFollowerDistance: Float;

@addField(MovePolicies)
public native let movementType: moveMovementType;

@addField(MovePolicies)
public native let circlingDirection: moveCirclingDirection;

@addField(MovePolicies)
public native let stopOnObstacle: Bool;

@addField(MovePolicies)
public native let avoidObstacleWithinTolerance: Bool;

@addField(MovePolicies)
public native let useCollisionAvoidance: Bool;

@addField(MovePolicies)
public native let useDestReservation: Bool;

@addField(MovePolicies)
public native let inRestrictedArea: Bool;

@addField(MovePolicies)
public native let isSpline: Bool;

@addField(MovePolicies)
public native let startFromClosestPoint: Bool;

@addField(MovePolicies)
public native let ignoreNavigation: Bool;

@addField(MovePolicies)
public native let useStart: Bool;

@addField(MovePolicies)
public native let useStop: Bool;

@addField(MovePolicies)
public native let isEvaluated: Bool;

@addField(MovePolicies)
public native let useOffMeshAllowedTags: Bool;

@addField(MovePolicies)
public native let useOffMeshBlockedTags: Bool;
