public func OperatorAdd(a: Vector2, b: Vector2) -> Vector2 {
  a.X += b.X;
  a.Y += b.Y;
  return a;
}

public func OperatorSubtract(a: Vector2, b: Vector2) -> Vector2 {
  a.X -= b.X;
  a.Y -= b.Y;
  return a;
}

public func OperatorMultiply(a: Vector2, b: Vector2) -> Vector2 {
  a.X *= b.X;
  a.Y *= b.Y;
  return a;
}

public func OperatorDivide(a: Vector2, b: Vector2) -> Vector2 {
  if b.X != 0.0 {
    a.X /= b.X;
  }
  if b.Y != 0.0 {
    a.Y /= b.Y;
  }
  return a;
}

public func OperatorAssignAdd(out a: Vector2, b: Vector2) -> Vector2 {
  a = a + b;
  return a;
}

public func OperatorAssignSubtract(out a: Vector2, b: Vector2) -> Vector2 {
  a = a - b;
  return a;
}

public func OperatorAssignMultiply(out a: Vector2, b: Vector2) -> Vector2 {
  a = a * b;
  return a;
}

public func OperatorAssignDivide(out a: Vector2, b: Vector2) -> Vector2 {
  a = a / b;
  return a;
}

public func OperatorEqual(a: Vector2, b: Vector2) -> Bool {
  return a.X == b.X && a.Y == b.Y;
}

public func OperatorGreater(a: Vector2, b: Vector2) -> Bool {
  return a.X > b.X && a.Y > b.Y;
}

public func OperatorGreaterEqual(a: Vector2, b: Vector2) -> Bool {
  return a.X >= b.X && a.Y >= b.Y;
}

public func OperatorLess(a: Vector2, b: Vector2) -> Bool {
  return a.X < b.X && a.Y < b.Y;
}

public func OperatorLessEqual(a: Vector2, b: Vector2) -> Bool {
  return a.X <= b.X && a.Y <= b.Y;
}

public func Cast(value: Vector3) -> Vector2 {
  let result: Vector2;
  result.X = value.X;
  result.Y = value.Y;
  return result;
}

public func Cast(value: Vector2) -> Vector3 {
  let result: Vector3;
  result.X = value.X;
  result.Y = value.Y;
  return result;
}

public func Cast(value: Vector4) -> Vector2 {
  let result: Vector2;
  result.X = value.X;
  result.Y = value.Y;
  return result;
}

public func Cast(value: Vector2) -> Vector4 {
  let result: Vector4;
  result.X = value.X;
  result.Y = value.Y;
  return result;
}