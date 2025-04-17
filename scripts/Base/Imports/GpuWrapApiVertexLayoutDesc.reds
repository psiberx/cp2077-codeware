public native struct GpuWrapApiVertexLayoutDesc {
  native let elements: [GpuWrapApiVertexPackingPackingElement; 32];
  native let slotStrides: [Uint8; 8];
  native let slotMask: Uint32;
  native let hash: Uint32;
}
