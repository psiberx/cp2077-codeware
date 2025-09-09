public func OperatorAdd(a: Vector3, b: Vector3) -> Vector3 {
  a.X += b.X;
  a.Y += b.Y;
  a.Z += b.Z;
  return a;
}

public func OperatorSubtract(a: Vector3, b: Vector3) -> Vector3 {
  a.X -= b.X;
  a.Y -= b.Y;
  a.Z -= b.Z;
  return a;
}

public func OperatorMultiply(a: Vector3, b: Vector3) -> Vector3 {
  a.X *= b.X;
  a.Y *= b.Y;
  a.Z *= b.Z;
  return a;
}

public func OperatorDivide(a: Vector3, b: Vector3) -> Vector3 {
  if b.X != 0.0 {
    a.X /= b.X;
  }
  if b.Y != 0.0 {
    a.Y /= b.Y;
  }
  if b.Z != 0.0 {
    a.Z /= b.Z;
  }
  return a;
}

public func OperatorAssignAdd(out a: Vector3, b: Vector3) -> Vector3 {
  a = a + b;
  return a;
}

public func OperatorAssignSubtract(out a: Vector3, b: Vector3) -> Vector3 {
  a = a - b;
  return a;
}

public func OperatorAssignMultiply(out a: Vector3, b: Vector3) -> Vector3 {
  a = a * b;
  return a;
}

public func OperatorAssignDivide(out a: Vector3, b: Vector3) -> Vector3 {
  a = a / b;
  return a;
}

public func OperatorEqual(a: Vector3, b: Vector3) -> Bool {
  return a.X == b.X && a.Y == b.Y && a.Z == b.Z;
}

public func OperatorGreater(a: Vector3, b: Vector3) -> Bool {
  return a.X > b.X && a.Y > b.Y && a.Z > b.Z;
}

public func OperatorGreaterEqual(a: Vector3, b: Vector3) -> Bool {
  return a.X >= b.X && a.Y >= b.Y && a.Z >= b.Z;
}

public func OperatorLess(a: Vector3, b: Vector3) -> Bool {
  return a.X < b.X && a.Y < b.Y && a.Z < b.Z;
}

public func OperatorLessEqual(a: Vector3, b: Vector3) -> Bool {
  return a.X <= b.X && a.Y <= b.Y && a.Z <= b.Z;
}
