public native class inkWidgetBrush extends IScriptable {
  native let textureAtlas: ResourceRef; // rRef<inkTextureAtlas>
  native let texturePartId: CName;
  native let tileType: inkBrushTileType;
  native let mirrorType: inkBrushMirrorType;

  public final native func GetMirrorType()
  public final native func GetTexturePart()
  public final native func GetTileType()
  public final native func IsTexturePartExist()
  public final native func SetTexturePart()
}
