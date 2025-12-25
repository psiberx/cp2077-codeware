public native struct SoundBankEntry {
    public native let name: CName;
    public native let isResident: Bool;
    public native let resourcePath: ResRef;
}

public native class SoundBanksJson extends CResource {
    public native let soundBanks: array<SoundBankEntry>;
}
