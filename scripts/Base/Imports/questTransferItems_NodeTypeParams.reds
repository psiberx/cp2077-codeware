public native struct questTransferItems_NodeTypeParams {
  native let giver: ref<questUniversalRef>;
  native let receiver: ref<questUniversalRef>;
  native let transferAllOperation: ref<questTransferItems_NodeTypeParams_TransferAllOperationData>;
  native let itemOperations: array<questTransferItems_NodeTypeParams_OperationData>;
  native let tagOperations: array<questTransferItems_NodeTypeParams_TagOperationData>;
}
