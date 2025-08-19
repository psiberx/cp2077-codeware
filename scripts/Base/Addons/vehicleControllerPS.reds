@addField(vehicleControllerPS)
public native persistent let vehicleDoors: [VehicleSlotsState; 6];

@addField(vehicleControllerPS)
public native persistent let state: vehicleEState;

@addField(vehicleControllerPS)
public native persistent let lightMode: vehicleELightMode;

@addField(vehicleControllerPS)
public native persistent let isAlarmOn: Bool;

@addField(vehicleControllerPS)
public native persistent let lightTypeMask: Int32;

@addField(vehicleControllerPS)
public native persistent let allowPassengerCameraSwitch: Bool;
