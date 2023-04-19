@addField(inkGridController)
native let height: Uint32;

@addField(inkGridController)
native let width: Uint32;

@addField(inkGridController)
native let items: array<inkGridItem>;

@addField(inkGridController)
native let slotSize: Vector2;

@addField(inkGridController)
native let itemTemplates: array<inkGridItemTemplate>;

public native struct inkGridItem
{
	public native let rootIdx: Uint32;
}

public native struct inkGridItemTemplate
{
	public native let sizeX: Uint32;
	public native let sizeY: Uint32;
	public native let widget: inkWidgetLibraryReference;
}
