public native class worldAcousticSectorNode extends worldNode {
  native let data: ResourceAsyncRef; // raRef<worldAcousticDataResource>
  native let inSectorCoordsX: Uint32;
  native let inSectorCoordsY: Uint32;
  native let inSectorCoordsZ: Uint32;
  native let generatorId: Uint32;
  native let edgeMask: Uint8;
}
