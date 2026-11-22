# Perfect Works Build
Xenogears Perfect Works Build: Includes an improved translation, rebalanced gameplay, and other quality of life improvements.

Download the latest release here:

https://github.com/NoharOSP/Perfect_Works_Build/releases/tag/0.12.0

For more in-depth information about the build, visit the wiki:

https://github.com/NoharOSP/Perfect_Works_Build/wiki
  
## Instructions

### Patching

#### Windows

- Download Xenogears_Perfect_Works_Edition.X.X.X.7z. The Xs correspond to the release number.
- Open the Xenogears: Perfect Works Patcher.
- Open the bin file for either or both discs. 
- Select which patches you wish to apply.
- Press Patch. The script edits should take longer to patch as it has the most files to copy.
- Open the patched ROM on your chosen emulator. The file will be called Xenogears_PW_CDX. X corresponds to the disc number.

#### macOS/Linux

- Download Xenogears_Perfect_Works_Patches.X.X.X.7z. The Xs correspond to the release number.
- Apply a patch or the patches using xdelta. Make sure you are applying them to an unpatched ROM of the original game.
- If there are warnings when applying the patches, turn off checksum validation.

The patches provided are as follows:

- all_50_exp_gold_fast_text - Applies all patches besides story mode. 1.5x exp and gold are used.
- all_100_exp_gold_fast_text - Applies all patches besides story mode. 2x exp and gold are used.
- all_50_exp_gold_no_gfx - Applies all patches besides story mode and the graphical settings. 1.5x exp and gold are used.
- all_100_exp_gold_no_gfx - Applies all patches besides story mode and the graphical settings. 2x exp and gold are used.
- all_50_exp_gold_normal_text - Applies all patches besides story mode and fast text. 1.5x exp and gold are used.
- all_100_exp_gold_normal_text - Applies all patches besides story mode and fast text. 2x exp and gold are used.
- bug_fixes - Only bug fixes are applied.
- story_mode - Applies story mode.
- story_mode_script - Applies story mode and the script changes.

WARNING: When a ROM has been made, do not resume progress by loading a save state. As a different ROM is being used, the game will crash due to the changing of data positions. To resume a playthrough, load a hard save.

## Completion stats

- Name/terminology changes: 100%
- Main script: 100%
- NPC script: 40% (plus all name/terminology changes)

## Introduction

Xenogears: Perfect Works is a collaborative project aiming to make Xenogears a more complete experience. This does contain unmarked but mild spoilers, so readers are advised and warned not to scroll through this if they’re looking to use this mod to enjoy the game for the first time, or you simply never got to into it for various reasons we hope to address. These spoilers are primarily for certain story events in the story bits and lines are relegated to story specific changes and certain boss fights dungeons and all moves party members and availability are mentioned in the gameplay focused changes. 

~ Ryan (↙ ➡ ↘ ⬇ ↙ ⬅ ↘) Piccuito, character writer and handler for game balance on the Xenogears Perfect Works mod.

DISCLAIMER: 
* Some of the patches were designed to work in tandem with each other. The 2x exp and gold patches were designed to work with the lower encounter rate patch. The monster stats and party/item patch both act as a rebalancing hack. They can be used separately from each other, but they were designed with the mindset of using them together.
* We do not condone the use of Generative AI as a whole, though we take the creative process very seriously, and want to ensure AI touches this project as little as possible within the context of the modern internet. The use of AI in any aspect of the retranslation effort has been strictly forbidden. While code changes are manually engineered, in some cases their implementation was possible using tools that were created with AI assistance. If any projects dedicated to creating a PC port want to collaborate with us, they must prove that their output has not been vibe coded in their entirety.

## Options

### Graphics

- Face fixes (resize): Fixes bugs with portraits and resizes them when running the game at its native aspect ratio.
- Face fixes (normal): Fixes bugs with portraits without resizing.
- No battle flashes: Turns off battle flashes.
- Perfect Works Roni: Uses Roni's Perfect Works portrait.
- Emeralda cafe fix: Fixes an oversight where Emeralda used her nanomachine tube sprites when sitting down.

### Gameplay

- 1/2 encounters: Halves the game's encounter rate.
- Modify experience: Increase experience yield from enemies by 1.5x or 2x.
- Modify gold: Increase gold yield from enemies by 1.5x or 2x.
- Rebalanced gameplay: Changes stats of specific enemies and bosses to make them more challenging, while also modifying the stats and abilities of the party. New items have been added and existing ones have been adjusted.
- No Deathblow levels: All Deathblows are available to learn at level 1.
- No damage cap: The damage displayed can exceed 9999.

### Arena

- Normal: Battle Arena is unchanged.
- Basic mode: Rebalances the Battle Arena.
- Expert mode: Same as above, but additional tweaks are made for the PVP experience.

### Story

- Script/name changes: Retranslates the game's script.
- Fast text: Increases the text scroll speed.
- Instant text: Text displays instantly.
- Metric system: Converts lbs to kg.

### Audio

- FMV undub: Switches the FMVs to the Japanese versions using subtitles that are more accurate than the original translation.
- Battle undub: Switches voices heard during battles to the Japanese versions.
- Music changes: Changes music placement in specific scenes so that they're more appropriate.

### Modes

- Story mode: Eliminates any form of difficulty so the player can enjoy the story.
- JPN controls: Switches to the Japanese control scheme.
- Bug fix only: Only applies bug fixes.

## Version history

### Version 0.12.0

11/XX/2026

- Stars of Tears FMV can be accessed via the same method used for the Japanese only naming screen in Citan's House.
- An option to have autorun has been added.
- An option to switch to the metric system to show weight has been added.
- Rebalance items/spells and rebalanced monsters have been combined into one feature called "rebalanced gameplay".
- Subtitles have been added to the Speed minigame and in-battle voice clips.
- Elly's Ether spells have been rebalanced. Details are in the wiki.
- The playable Gears have had their attack outputs modified. Details are in the wiki.
- The patcher has been modified to accept disc dumps that are missing the 2 second postgap.
- Battle UI will now display Booster as On if the player turns it on.
- Fixed a bug where voiced lines from Fei, Elly, and Citan are cut off.
- Fixed a bug where instant text is used when no battle flashes is selected in disc 1.
- Fixed Merkabah FMV timings.
- Breidablik NPC script has been completed.
- Farrand has been changed to Vorland.
- Falkon has been changed to Falke.
- Vind has been corrected Wind.
- Av Castle mess hall fan events have been fixed.
- Nisan nun dialogue triggers have been fixed.
- Midori's Ring bug has been fixed.
- Fixed game freeze that can occur with Deathblows when Booster is used.

## Links

Join our discord if you have any issues or you want to communicate with us:
https://discord.gg/j4v6yCcWRK

Provide feedback here:
https://docs.google.com/forms/d/1KZAwqR70pABGXtuR7l8GVMjY487WKOn6Qrb3fUHHumw/viewform?edit_requested=true

DM or tag here if you want immediate feedback on Twitter:
@PWBuildTeam

## Credits

- Abathor (Xenocritus): Creator, translation, character balance, programming
- thefoolishflame: Translation, character balance, programming, icons
- Nohar: Translation, character balance, programming, patcher
- Ryan Piccuito ↙ ➡ ↘ ⬇ ↙ ⬅ ↘: Translation, character balance, testing
- ribbiwawa (@ribbiwawaaa): Translation
- rafael: Translation, character balance, testing
- rulv: Programming
- Rufas: Programming, graphical fixes, Xenogears and PSX tools
- krmine: Translation, programming
- edrovinhaz: Translation, programming, graphical fixes, icons, eboot themes
- cthuljew: Testing
- Streetwize (@StreetwizeJJ2): Character balance, battle arena, programming, fast text
- Siris: Story mode, translation, programming, graphical fixes, softsub text and timings
- ChrisGLink: Translation
- einlanzer: Testing
- linnaealyn: Testing, FMV font
- Opok: Documentation, decomp tools, trailing s bug fix, autorun code
- [An Eye for the Infinite](https://web.archive.org/web/20101225035716/http://moonreading.lunarpages.com/xeno/): Translation
- [Almagest](http://almagest712.blogspot.com/2017/11/xenogears-my-father-you-mean-my-dad.html): Translation
- cactusmomma: Translation
- ividyon: Translation
- CosmicFrame: Testing
- The Minester: Testing
- RayDreamer: Testing
- ChaoticBrave: Testing and dropdown menu code
- Aero JP: Testing
- Kiahnte: Testing
- wowbobwow: Testing
- FAY!!: Testing
- Ali: Testing
- Kaizoku85: Testing
- Lursga: Testing
- Dead Heart of Africa: Testing
- big4lil: Testing
- Jerry Rice: Testing
- [SadNES cITy Translations](https://sadnescity.it/): Xenogears translation tools
- Joshua MacDonald: xdelta
- FFMaster: Fast text code
- RyleFury: Deus bug fix, softsub tools
- Sephiroth1311: Deus bug fix, metric system patch
- FourthStrongest: Testing


