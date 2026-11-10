public native struct CDistantLightsResourceEntry {
    public native let red: Uint8;
    public native let green: Uint8;
    public native let blue: Uint8;
    public native let unk03: Uint8;
    public native let intensity: Float;
    public native let unk08: Uint16;
    public native let unk10: Uint16;
    public native let unk0C: Uint16;
    public native let dirX: Uint8;
    public native let dirY: Uint8;
}

public native class CDistantLightsResource extends resStreamedResource {
    public native func GetEntryCount() -> Int32
    public native func GetEntry(index: Int32) -> script_ref<CDistantLightsResourceEntry>
}
