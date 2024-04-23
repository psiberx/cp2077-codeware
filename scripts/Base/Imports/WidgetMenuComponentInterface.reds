public native class WidgetMenuComponentInterface extends WidgetBaseComponent {
  native let widgetResource: ResourceRef; // rRef<inkWidgetLibraryResource>
  native let cursorResource: ResourceRef; // rRef<inkWidgetLibraryResource>
  native let externalMaterial: ResourceRef; // rRef<CMaterialTemplate>
  native let meshTargetBinding: ref<worlduiMeshTargetBinding>;
}
