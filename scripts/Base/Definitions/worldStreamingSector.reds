public native class worldStreamingSector extends CResource {
  native let localInplaceResource: array<ResourceRef>;
  native let externInplaceResource: ResourceAsyncRef; // raRef<worldStreamingSectorInplaceContent>
  native let level: Uint8;
  native let category: worldStreamingSectorCategory;
}
