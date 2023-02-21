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
 // define flags to store with Bits starting from index 1
 Consuming = 1,
 Rested = 2,
 Energized = 3,
 // ... up to 32
}

// create a new blackboard value on player
@addField(PlayerStateMachineDef)
public let MyState: BlackboardID_Int;

// in your custom system
public class MySystem extends ScriptableSystem {
 // don't forget to initialize it on player attached
 private let player: wref<PlayerPuppet>;

 // update any of your flags, e.g. State.Consuming
 public func UpdateConsuming(value: Bool) -> Void {
   let blackboard: ref<IBlackboard> = this.player.GetPlayerStateMachineBlackboard();
   let current = blackboard.GetInt(GetAllBlackboardDefs().PlayerStateMachine.MyState);
   let updated: Int32 = Bits.Set(current, EnumInt(State.Consuming), value);
   // notify blackboard listeners
   blackboard.SetInt(GetAllBlackboardDefs().PlayerStateMachine.MyState, updated);
  }
 }

 // retrieve any of your flags, e.g. State.Consuming
 @addMethod(PlayerPuppet)
 public func IsConsuming() -> Bool {
   let blackboard: ref<IBlackboard> = this.player.GetPlayerStateMachineBlackboard();
   let myState: Int32 = blackboard.GetInt(GetAllBlackboardDefs().PlayerStateMachine.MyState);
   return Bits.Has(myState, EnumInt(State.Consuming));
 }

 // you can also retrieve and/or update multiple flags at once
 // for better performances!
}
```