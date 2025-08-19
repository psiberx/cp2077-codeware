// @neverRef()

@addField(ReactionData)
public native let startDuration: Float;

@addField(ReactionData)
public native let endDuration: Float;

@addField(ReactionData)
public native let interactionDuration: Float;

@addField(ReactionData)
public native let interactionType: CName;

@addField(ReactionData)
public native let requiredEquips: array<RequestItemParam>;

@addField(ReactionData)
public native let interactionPoint: Transform;

@addField(ReactionData)
public native let useIK: Bool;

@addField(ReactionData)
public native let IKPoint: Vector4;
