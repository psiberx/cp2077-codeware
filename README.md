# Codeware Lib

## Features

- Global Registry
  * Store and retrieve objects by name
- Localization
  * Translate the mod based on the game language settings
  * Use different language packages for the interface and subtitles 
  * Vary translations based on player gender
- UI: Custom Widgets
  * Create composite widgets with logic
- UI: Buttons
- UI: Button Hints
- UI: Popups
- UI: Resolution Watcher
  * Apply scaling to widgets
  * Make adaptive layouts
- Hashing
  * TweakDBID
  * FNV1a64 (Experimental and ineffective)
- Delay System
  * Schedule events for UI controllers
- Native Extensions
  * Access native things that are not accessible by default

## Usage

The lib can be used in two ways: as a shared or internal lib. 

### Shared

You can add the lib as a dependency.

### Internal

You can include a full or partial copy of the lib with only features you need in your mod. 

To prevent conflicts with other mods and / or shared lib, you must give your copy a unique namespace.
For example, you can simply use your mod's namespace or prepend with it: `Codeware` → `MyMod.Codeware`. 
