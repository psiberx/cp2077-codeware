public native class WidgetMenuComponentInterface extends WidgetBaseComponent {
  public native let widgetResource: ResourceRef; // rRef<inkWidgetLibraryResource>
  public native let cursorResource: ResourceRef; // rRef<inkWidgetLibraryResource>
  public native let externalMaterial: ResourceRef; // rRef<CMaterialTemplate>
  public native let meshTargetBinding: ref<worlduiMeshTargetBinding>;
}
