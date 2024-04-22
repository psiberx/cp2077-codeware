public native struct gameHitShapeBVH {
  native let nodeName: CName;
  native let childrenNodes: array<gameHitShapeBVH>;
  native let childrenShapeNames: array<CName>;
}
