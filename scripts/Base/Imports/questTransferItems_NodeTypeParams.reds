public native struct questTransferItems_NodeTypeParams {
  public native let giver: ref<questUniversalRef>;
  public native let receiver: ref<questUniversalRef>;
  public native let transferAllOperation: ref<questTransferItems_NodeTypeParams_TransferAllOperationData>;
  public native let itemOperations: array<questTransferItems_NodeTypeParams_OperationData>;
  public native let tagOperations: array<questTransferItems_NodeTypeParams_TagOperationData>;
}
