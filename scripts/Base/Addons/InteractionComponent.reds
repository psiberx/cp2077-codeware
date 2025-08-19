@addField(InteractionComponent)
public native let definitionResource: ResourceRef; // rRef<gameinteractionsInteractionDescriptorResource>

@addField(InteractionComponent)
public native let interactionRootOffset: Vector3;

@addField(InteractionComponent)
public native let layerOverrides: array<gameinteractionsInteractionDefinitionOverrider>;

@addField(InteractionComponent)
public native let layerOverridesTemp: array<gameinteractionsInteractionDefinitionOverrider>;

@addField(InteractionComponent)
public native let isEnabled: Bool;
