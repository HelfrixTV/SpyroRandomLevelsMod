# [SpyroRandomLevelsMod](https://github.com/HelfrixTV/SpyroRandomLevelsMod)
This is a random levels mod for Spyro the Dragon (ps1). This mod randomizes all the level portals of each homeworld, so walking into the Stone Hills portal could lead you to any level (including flight levels and Gnasty Gnorc!).

On first entering a new game a menu will appear for you to select a seed (if you accidentally close the menu you can re-open with `select`)

### A few notes - and possible fixes for the future
The moving wall outside of Sunny Flight will remain up when coming out of the portal, but you can just walk through it.

The dragon head leading to the Toasty portal has had it's requirments removed, this is because if you enter the level from behind (speedrun strat) you will get stuck inside the head when leaving the level.

The balloonist requirements have also been removed, this is because in the unlikely scenario where you get all flight levels in Artisans you won't have enough dragons freed to carry on. Same for the egg requirement.

All the dragon heads in Gnorc Gnexus have also had it's requirements removed for similar reasons (except for the dragon in the homeworld)

# Installation

1. Grab the latest xdelta release [here](https://github.com/HelfrixTV/SpyroRandomLevelsMod/releases)

2. Using an xdelta patcher (such as [kotcrab's patcher](https://kotcrab.github.io/xdelta-wasm/)), using spyro.bin and the spyroRandomLevels.xdelta.

3. You will need a cue sheet to run your new spyroRandomLevels.bin file. You can either clone the original spyro.cue file and edit it in any text editor yourself, or use a tool such as [duckstation's cue maker](https://www.duckstation.org/cue-maker/).

4. Put your spyroRandomLevels.bin and spyroRandomLevels.cue files into the same directory and launch like any other ps1 game in your emulator of choice!

Note for duckstation emulation: You need to set the settings->Console->CD-ROM Emulation->Seek Speedup to anything other than default

# Compiling

1. Install the [psx-modding-toolchain](https://github.com/mateusfavarin/psx-modding-toolchain) created by RedHot.

2. Clone the repo into your `path/to/psx-modding-toolchain/games/` folder.

3. Place your legally acquired `spyro.bin` into `build/`.

4. Open a terminal and navigate to `mods/randomLevels/` and run `MOD.BAT`.

5. Compile, then Build Iso. The output will be placed into `build/`.
