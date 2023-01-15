// -----------------------------------------------------------------------------
// DelaySystem
// -----------------------------------------------------------------------------
//
// - Delayed events for UI controllers
//
// -----------------------------------------------------------------------------
//
// class DelaySystem extends IDelaySystem {
//   public func DelayEvent(controller: wref<inkGameController>, eventToDelay: ref<Event>, timeToDelay: Float, opt isAffectedByTimeDilation: Bool) -> DelayID
//   public func DelayEvent(controller: wref<inkLogicController>, eventToDelay: ref<Event>, timeToDelay: Float, opt isAffectedByTimeDilation: Bool) -> DelayID
//   public func DelayEventNextFrame(controller: wref<inkGameController>, eventToDelay: ref<Event>)
//   public func DelayEventNextFrame(controller: wref<inkLogicController>, eventToDelay: ref<Event>)
// }
//

module Codeware.Scheduling

@addMethod(DelaySystem)
public func DelayEvent(controller: wref<inkGameController>, eventToDelay: ref<Event>, timeToDelay: Float, opt isAffectedByTimeDilation: Bool) -> DelayID {
    let callback = new ControllerDelayCallback();
    callback.controller = controller;
    callback.event = eventToDelay;

    return this.DelayCallback(callback, timeToDelay, isAffectedByTimeDilation);
}

@addMethod(DelaySystem)
public func DelayEventNextFrame(controller: wref<inkGameController>, eventToDelay: ref<Event>) {
    let callback = new ControllerDelayCallback();
    callback.controller = controller;
    callback.event = eventToDelay;

    this.DelayCallbackNextFrame(callback);
}

@addMethod(DelaySystem)
public func DelayEvent(controller: wref<inkLogicController>, eventToDelay: ref<Event>, timeToDelay: Float, opt isAffectedByTimeDilation: Bool) -> DelayID {
    let callback = new ControllerDelayCallback();
    callback.controller = controller;
    callback.event = eventToDelay;

    return this.DelayCallback(callback, timeToDelay, isAffectedByTimeDilation);
}

@addMethod(DelaySystem)
public func DelayEventNextFrame(controller: wref<inkLogicController>, eventToDelay: ref<Event>) {
    let callback = new ControllerDelayCallback();
    callback.controller = controller;
    callback.event = eventToDelay;

    this.DelayCallbackNextFrame(callback);
}
