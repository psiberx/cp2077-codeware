@addField(vehicleControllerPS)
native persistent let vehicleDoors: [VehicleSlotsState; 6];

@addField(vehicleControllerPS)
native persistent let state: vehicleEState;

@addField(vehicleControllerPS)
native persistent let lightMode: vehicleELightMode;

@addField(vehicleControllerPS)
native persistent let isAlarmOn: Bool;

@addField(vehicleControllerPS)
native persistent let lightTypeMask: Int32;

@addField(vehicleControllerPS)
native persistent let allowPassengerCameraSwitch: Bool;
