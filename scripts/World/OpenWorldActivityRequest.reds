public native struct OpenWorldActivityRequest {
    public native let kind: CName;
    public native let districts: array<gamedataDistrict>;
    public native let cooldown: Float; // seconds
}
