// R16a. Mac RVAs for SDK address hashes that the vendored SDK table (RED4ext.SDK Relocation-inl.hpp, in the
// TweakXL fork) does not have. One source of truth for two consumers:
//   1. MacAddressResolver.cpp includes this file inside its row map (Core::RawFunc users).
//   2. CMakeLists.txt injects these rows into a generated copy of the SDK header, so the SDK's own
//      UniversalRelocFunc calls (CClass::GetProperty and friends, compiled into this plugin) resolve them too.
//      Those calls never go through MacAddressResolver.
// Format: { hash, RVA },  // name. RVA is relative to the Cyberpunk2077 image base. Entry and body checked against
// the Windows function (tools/addr-match, win-ref), see the R16a plan run.
        { 2399343890, 0x10C4C14 },  // CClass_GetProperty. CProperty*(CClass*, CName). Windows rtti::ClassType::FindProperty 0x148388. NCC value 0x219929C is mid-function, wrong.
        { 2257327441, 0x10C37D8 },  // CClass_InitializeProperties. void(CClass*, ScriptInstance). Windows InitializeScriptedProperties 0x147CB8.
        { 2547979664, 0x10C3934 },  // CClass_AssignDefaultValuesToProperties. void(CClass*, ScriptInstance). Windows InitializeScriptDefaultValues 0x147384.
        // R18 B0. The job runtime (one cluster 0x9D4020 .. 0x9D8E80 on Mac). Matched by a read-only agent, rated by check-rows.py.
        { 2627471740, 0x4DDF868 },   // JobHandle_Join. void(JobHandle*, const JobHandle&). Windows 0x142838.
        { 2655521326, 0x4DDF828 },   // JobHandle_dtor (ReleaseInternalHandle). Mac returns this. The caller-less twins are 0x9D498C and 0x9D49C4. Windows 0x1419A4.
        { 1862212562, 0x4DE2D7C },   // JobInternalHandle_Acquire. Mac JobInternalHandle*(ignored, const char* name, uintptr_t unk): one more argument than the SDK. Windows 0x142B20.
        { 242552139,  0x4DDF1C4 },   // JobQueue_ctor_FromGroup (job::Builder::Builder). JobQueue*(JobQueue*, const JobGroup&). Windows 0x142634.
        { 2193429752, 0x4DDEF64 },   // JobQueue_ctor_FromParams. JobQueue*(JobQueue*, uint8_t, uint8_t, uint64_t). Windows 0x218B54.
        { 69014212,   0x4DDF3C4 },   // JobQueue_Capture. Mac JobHandle(JobQueue*): the handle comes back through x8, no out pointer. Windows 0x218C38.
        { 1525942140, 0x4DDF488 },   // JobQueue_dtor. Body. The game calls it through the thunk 0x9D46EC. Windows 0x142F88.
        { 3651996672, 0x4DDF354 },   // JobQueue_SyncWait. void(JobQueue*). Windows 0x141B10.
        { 2621709954, 0x4DE3088 },   // JobDispatcher_DispatchJob. uint32_t(dispatcher, const JobInstance&, uint8_t, JobInternalHandle*, JobInternalHandle*). Not its tail target 0x9D8720. Windows 0x14299C.
        { 1508445968, 0x9D0E550 },  // JobDispatcher. Data: the cell that holds the dispatcher pointer. Windows .data 0x3438980.
        { 0xC0DE0010, 0x4DF0D14 },   // MacJobSetLocalThreadParam. void(uint8_t). Mac-only id: the SDK writes TLS::Get()->jobParam, and TLS::Get() is null on Mac. 2468 callers, all around job bodies.
        // R19 B2. Reflection, enums and serialization. Matched by read-only agents, rated by check-rows.py.
        { 55710513,   0x11E4964 },  // IScriptable_DestructValueHolder. void(IScriptable*). Replaces the TweakXL stand-in. Windows 0x14934C.
        { 1482886888, 0x10C3BC8 },  // TTypedClass_IsEqual. bool(CClass*, lhs, rhs, uint32). Behind 8241 one-instruction vtable thunks (0x93FCAC): hook the body. Windows 0x33A208.
        { 1652956141, 0x10c352c },  // CClass_GetProperties. void(CClass*, DynArray<CProperty*>&): returns nothing. Windows 0x2519E4.
        { 1087575974, 0x10CF100 },  // CEnum_Unserialize. bool(CEnum*, BaseStream*, instance, int64). Windows 0x1487A4.
        { 68817558,   0x10CF304 },  // CEnum_ToString. bool(CEnum*, instance, CString&). Windows 0x599BFC.
        { 566894273,  0x10CF45C },  // CEnum_FromString. bool(CEnum*, instance, const char* text and a size): the string comes as a StringView in x2/x3. Windows 0x59B204 (the address table says 0x75DF94, which is wrong).
        { 2794985748, 0x10C18F4 },  // CBitfield_Unserialize. Windows 0x33B6C0.
        { 1411585028, 0x10c1f6c },  // CBitfield_ToString. Windows 0x2076F18.
        { 2694518184, 0x10C2074 },  // CBitfield_FromString. Same StringView shape as the enum one. Windows 0x2076E00.
        { 3778157291, 0x109B16C },  // CBaseFunction_ExecuteNative. bool(CBaseFunction*, CStack*): builds its own frame. Windows 0x20668A0.
        { 2318998714, 0x1075718 },  // ObjectPackageExtractor_Initialize. void(this, params). Windows 0x46A1E8.
        { 114701897,  0x10b09a4 },  // ISerializable_sub_30. bool(this): true when there is no owning CResource. Shared by about 6700 vtables, never hook. Windows 0x2052B84.
        { 2293436409, 0x10B0860 },  // ISerializable_sub_40. bool(this, BaseStream*). Windows 0x148940.
        { 2715367827, 0x10B0C08 },  // ISerializable_sub_78. Mac: Handle(this, a1, a2 byte, a3, a4) with the Handle through x8 (the SDK signature models a hidden first argument). Windows 0x711A14.
        { 3978435378, 0x10b0b6c },  // ISerializable_sub_A0. The base default (GetType()->GetDefaultObject). The address table's Windows 0xB9A864 is a CResource override; the twin is 0x1247898.
        { 2149588021, 0x10b0b44 },  // ISerializable_sub_C0. The base default: the owning CResource's +0x30, returned in x0. The address table's Windows 0x81DA2C is unrelated; the twin is 0x4B0D9C.
        { 3689484881, 0x10b0b44 },  // ISerializable_sub_C0: the 2.5 hash of the same function (upstream 0f5eba42a renamed it)
        { 4175699423, 0x11e4da0 },  // IScriptable_sub_D8. void(this, unused, visitor). Windows 0x205FE10.
        // R19 B3. Resource loader and token. The SharedPtr, Handle and JobHandle results come back through x8 on Mac; the SDK
        // wrappers (ResourceLoader.hpp) are reshaped under __APPLE__.
        { 2017202228, 0x99DC690 },  // ResourceLoader. Data: the cell holding the ResourceLoader pointer. Windows .data 0x3426E58.
        { 1250309504, 0x10E7060 },  // ResourceLoader_IssueLoadingRequestByPath. SharedPtr<Token>(loader, path), result through x8. Windows 0x2253C8.
        { 2365013187, 0x10E710C },  // ResourceLoader_IssueLoadingRequest. SharedPtr<Token>(loader, const ResourceRequest&), result through x8. Windows 0x1DE50C.
        { 3362732471, 0x10E7F6C },  // ResourceLoader_FindTokenFast. SharedPtr<Token>(loader, path), result through x8, no lock inside. Windows 0x1DD5D8.
        { 2349406410, 0x10EF26C },  // ResourceToken_Fetch. Handle<T>&(token): returns token+0x28. Windows 0x261F24.
        { 3947570603, 0x10EF37C },  // ResourceToken_OnLoaded. JobHandle(token, LoadedCallback*), result through x8. Windows 0x9B44DC.
        { 4142009574, 0x4153D5C },  // ResourceToken_CancelUnk38. void(Unk38*) (IO::IOContext::RequestCancel). Windows 0xBC7E34.
        // MAC-NOT-YET: ResourceToken_DestructUnk38 (Windows 0x28B814) has no Mac function; the game inlines that release in ~ResourceToken (0x21C4A54 to 0x21C4ACC). The SDK ~ResourceToken skips it on Apple, so a token the SDK destroys leaks its Unk38 request object. Not applicable as a row.
        // R21 B5. The update registrar is called through the SDK's own UniversalRelocFunc (SystemUpdate-inl.hpp), so these two rows live here.
        { 4254156293, 0x4D74AB0 },  // UpdateRegistrar_RegisterGroupUpdate. void(registrar, group, CClass*, name, callback&&, w5 = 0xA): the last argument is live on Mac (all 128 game call sites pass 0xA). Windows 0x624D54.
        { 4259268103, 0x4D74AB0 },  // UpdateRegistrar_RegisterGroupUpdate: the 2.5 hash of the same function (upstream 0f5eba42a renamed it)
        { 422530722,  0x4D74C20 },  // UpdateRegistrar_RegisterBucketUpdate. void(registrar, mask, stage, CClass*, name, callback&&, w6 = 0xD): live on Mac (all 64 game call sites pass 0xD). Windows 0x62575C.
        { 427642532, 0x4D74C20 },  // UpdateRegistrar_RegisterBucketUpdate: the 2.5 hash of the same function (upstream 0f5eba42a renamed it)
        { 4125893577, 0x1215524 },  // DeferredDataBuffer_LoadAsync. LoadResult(DeferredDataBuffer*, int64 a3): a 16 byte result through x8 whose JobHandle is at result+8 (the game never writes result+0); Windows: JobHandle* out in rdx. R22 body twin of Windows 0xB0762C: lock byte at this+0x55 (xchg / swpalb), counter at this+0x50, a JobQueue, the load job; callers include the ArchiveXL resource patch (compiledData.LoadAsync).
