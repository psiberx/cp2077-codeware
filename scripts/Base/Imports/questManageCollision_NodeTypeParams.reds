public native struct questManageCollision_NodeTypeParams {
  native persistent let objectRef: NodeRef;
  native persistent let enableCollision: Bool;
  native persistent let enableQueries: Bool;
  native persistent let components: array<CName>;
}
