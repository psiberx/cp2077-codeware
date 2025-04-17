@addField(InteractionComponent)
native let definitionResource: ResourceRef; // rRef<gameinteractionsInteractionDescriptorResource>

@addField(InteractionComponent)
native let interactionRootOffset: Vector3;

@addField(InteractionComponent)
native let layerOverrides: array<gameinteractionsInteractionDefinitionOverrider>;

@addField(InteractionComponent)
native let layerOverridesTemp: array<gameinteractionsInteractionDefinitionOverrider>;

@addField(InteractionComponent)
native let isEnabled: Bool;
