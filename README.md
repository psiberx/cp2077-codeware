# Codeware Lib

## Features

- _Global Registry_
  * Store and retrieve objects by name
- _Localization System_
  * Translate the mod based on the game language settings
  * Use different language packages for the interface and subtitles 
  * Vary translations based on player gender
- _UI: Custom Widgets_
  * Create composite widgets with logic
- _UI: Buttons_
  * Generic button template
  * Simple and Hub buttons
- _UI: Popups_
  * Generic popup template
  * In-game style popup (like Radio, Call Vehicle, Messenger)
- _UI: Button Hints_
  * Spawn and manage input hints
- _UI: Resolution Watcher_
  * Apply scaling to widgets
  * Make adaptive layouts
- _Hashing_
  * TweakDBID
  * FNV1a64 (Experimental and ineffective)
- _Delay System_
  * Schedule events for UI controllers
- _Native Extensions_
  * Access native things that are not accessible by default

## In Progress

- _Text Input_ – For text search, custom notes, chatbots? :)
- _Freeform Widgets_ – For drawing vector icons from scripts
- _Scroll Pane / Scroll Bar_ – For large content and lists
- _Menu Style Popup_ – Like in the Hub menu

## Usage

The lib can be used in two ways: as a shared or internal lib. 

### Shared

You can add the lib as a dependency.

:exclamation: Not published on Nexus yet.

### Internal

You can include a full or partial copy of the lib only with features you need in your mod. 

To prevent conflicts with other mods and / or shared lib, you must give your copy a unique namespace.
For example, you can simply use your mod's namespace or prepend with it: `Codeware` → `MyMod.Codeware`. 
