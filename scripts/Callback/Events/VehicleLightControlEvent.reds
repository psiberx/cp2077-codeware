public native class VehicleLightControlEvent extends EntityLifecycleEvent {
    public native func IsEnabled() -> Bool
    public native func IsLightType(lightType: vehicleELightType) -> Bool
}
