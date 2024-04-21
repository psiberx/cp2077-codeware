public native class inkStyleResource extends CResource {
  native let styles: array<inkStyle>;
  native let styleImports: array<ResourceRef>;
  native let themes: array<inkStyleTheme>;
  native let overrides: array<inkStyleOverride>;
  native let hideInInheritingStyles: Bool;
}
