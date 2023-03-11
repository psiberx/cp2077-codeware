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

public class ControllerDelayCallback extends DelayCallback {
    public let controller: wref<IScriptable>;
    public let event: ref<Event>;

    public func Call() {
        if IsDefined(this.controller) {
            // inkGameController
            if this.controller.IsA(n"gameuiWidgetGameController") {
                (this.controller as inkGameController).QueueEvent(this.event);
                return;
            }

            // inkLogicController
            if this.controller.IsA(n"inkWidgetLogicController") {
                (this.controller as inkLogicController).QueueEvent(this.event);
                return;
            }
        }
    }
}

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
