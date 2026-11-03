## Stand-ins and Mac-only fallbacks

What the Mac port replaces or stubs on purpose, and why. Everything else in this port is the real implementation.

| what | where | why it exists | what is lost |
|---|---|---|---|
| Script class `ArchiveXL` (`Version`, `Require`, `EnableGarmentOffsets`, `DisableGarmentOffsets`, `GetBodyType`) | `macos/ArchiveXLScripts.cpp` | fallback for a session without the ArchiveXL plugin (for example the closed NightCity Console build, which registers no script natives): a script cache that calls `ArchiveXL.Version()` needs the class to link | the three garment calls are no-ops and `GetBodyType` returns None. In a session with the ported ArchiveXL plugin the class comes from the plugin and this file registers nothing (a class is never registered twice). |
| `CGameEngine` slot and the `EngineTime` frequency (`macos/MacStandIns.inc`) | `macos/MacEngine.cpp` | the engine capture hook fills the slot, and the Mac tick frequency is computed from `mach_timebase_info` when the game's accessor returns 0 | none; checked by the engine self-test |
| Native test class `CodewareMacSelfTest` | `macos/MacR13.cpp` | the diagnostic scripts (`tools/diag-scripts`) call it; it is registered always so a cache with and without the diagnostic scripts both link | nothing runs unless `CODEWARE_MAC_DIAG=1` and the diagnostic scripts are in the cache |
| Windows-only script classes left out of the script cache | `tools/build-cache.exclude` | the Mac game has no such natives (editor, Win32 input, Jira and OAuth services, one struct whose field type differs) | scripts that use them cannot link on Mac |
| Service state save through the inline path | `src/App/Scripting/ScriptableServiceContainer.cpp` | the save hook runs `SaveState` inline; the job-group dispatch of the Windows code is behind `CODEWARE_MAC_SAVE_JOBS=1` because a job inside a real save adds risk and nothing else | none for the player |
| `ResourceToken` destructor | SDK row `ResourceToken_dtor` (trap) | the destructor calls a function the Mac game inlined (`DestructUnk38`) | a Codeware-owned token leaks its request object |
