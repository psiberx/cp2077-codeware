# Bits

Store up to 32 boolean-like flags as a single integer.

Useful and way more performant whenever you need to keep track of a state with numerous booleans.

## usage

```swift
import Codeware.Bits

enum State {
 // it's perfectly fine to reserve other variants index(es) for different purposes
 // but you CANNOT store them as flags with Bits (out-of-range)
 Invalid = -1,
 // define flags to store with Bits starting from index 0
 Consuming = 0,
 Rested = 1,
 Energized = 2,
 // ... up to 31
}

// create a new blackboard value on player
@addField(PlayerStateMachineDef)
public let MyState: BlackboardID_Uint;

// in your custom system
public class MySystem extends ScriptableSystem {
 // don't forget to initialize it on player attached
 private let player: wref<PlayerPuppet>;

 // update any of your flags, e.g. State.Consuming
 public func UpdateConsuming(value: Bool) -> Void {
  let blackboard: ref<IBlackboard> = this.player.GetPlayerStateMachineBlackboard();
  let current = blackboard.GetUint(GetAllBlackboardDefs().PlayerStateMachine.MyState);
  let updated: Uint32 = Bits.Set(current, Cast<Uint32>(EnumInt(State.Consuming)), value);
  // notify blackboard listeners
  blackboard.SetUint(GetAllBlackboardDefs().PlayerStateMachine.MyState, updated);
 }
}

// retrieve any of your flags, e.g. State.Consuming
@addMethod(PlayerPuppet)
public func IsConsuming() -> Bool {
  let blackboard: ref<IBlackboard> = this.GetPlayerStateMachineBlackboard();
  let myState: Uint32 = blackboard.GetUint(GetAllBlackboardDefs().PlayerStateMachine.MyState);
  return Bits.Has(myState, Cast<Uint32>(EnumInt(State.Consuming)));
}

// you can also retrieve and/or update multiple flags at once
// for better performances!
```
