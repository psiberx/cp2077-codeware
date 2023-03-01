// -----------------------------------------------------------------------------
// Codeware
// -----------------------------------------------------------------------------
//
// Allows for storing up to 32 boolean-like flags packed in a single integer
//

module Codeware

public class Bits {
  public static func ShiftRight(num: Uint32, n: Uint32) -> Uint32 {
    return num / Cast<Uint32>(RoundMath(PowF(2., Cast<Float>(n))));
  }

  public static func ShiftLeft(num: Uint32, n: Uint32) -> Uint32 {
    return num * Cast<Uint32>(RoundMath(PowF(2., Cast<Float>(n))));
  }

  public static func Invert(num: Uint32) -> Uint32 {
    let after = num;
    let i = 0u;
    while i < 32u {
      after = after ^ Bits.ShiftLeft(1u, i);
      i += 1u;
    }
    return after;
  }

  public static func Has(num: Uint32, n: Uint32) -> Bool {
    return Cast<Bool>(Bits.ShiftRight(num, n) & 1u);
  }
  
  public static func Set(num: Uint32, n: Uint32, value: Bool) -> Uint32 {
    let after = num;
    if value {
      // set bit to 1
      after |= Bits.ShiftLeft(1u, n);
    } else {
      // set bit to 0
      let shifted = Bits.ShiftLeft(1u, n);
      let inversed = Bits.Invert(shifted);
      after &= inversed;
    }
    return after;
  }
}