@addField(MountEventData)
native persistent let setEntityVisibleWhenMountFinish: Bool;

@addField(MountEventData)
native persistent let switchRenderPlane: Bool;

@addField(MountEventData)
native persistent let isJustAttached: Bool;

@addField(MountEventData)
native persistent let isCarrying: Bool;

@addField(MountEventData)
native persistent let allowFailsafeTeleport: Bool;
