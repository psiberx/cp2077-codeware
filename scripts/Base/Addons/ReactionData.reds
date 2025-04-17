@addField(ReactionData)
native let startDuration: Float;

@addField(ReactionData)
native let endDuration: Float;

@addField(ReactionData)
native let interactionDuration: Float;

@addField(ReactionData)
native let interactionType: CName;

@addField(ReactionData)
native let requiredEquips: array<RequestItemParam>;

@addField(ReactionData)
native let interactionPoint: Transform;

@addField(ReactionData)
native let useIK: Bool;

@addField(ReactionData)
native let IKPoint: Vector4;
