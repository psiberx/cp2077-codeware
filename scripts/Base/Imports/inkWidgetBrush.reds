public native class inkWidgetBrush extends IScriptable {
  public native let textureAtlas: ResourceRef; // rRef<inkTextureAtlas>
  public native let texturePartId: CName;
  public native let tileType: inkBrushTileType;
  public native let mirrorType: inkBrushMirrorType;

  public final native func GetMirrorType()
  public final native func GetTexturePart()
  public final native func GetTileType()
  public final native func IsTexturePartExist()
  public final native func SetTexturePart()
}
