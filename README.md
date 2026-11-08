<p align="center"><img src="logo.png" width="120" alt="Aliou's Buffer logo"></p>

# Aliou's Buffer

A predictive input-buffering [Geode](https://geode-sdk.org) mod for Geometry Dash. When you click or release a little too early, a hidden "ghost" player is simulated ahead; if it would crash, your input is held back by a few physics ticks so it lands safely. It understands orbs, pads, portals, moving objects and every game mode.

> **Practice use only.** Runs that use input assistance (buffering, auto-click, auto-release, non-240 TPS) are **not legitimate** and must never be submitted for verification or leaderboards. The mod shows an on-screen tag while it is active in normal runs.

## Features
- Trajectory prediction with orb, pad, portal and moving-object awareness
- Buffered presses and releases for cube, ship, ball, UFO, wave, robot, spider and swing
- Orb alignment and orb timing, plan-two-clicks-ahead, robust saves
- Level memory, death heatmap, per-level settings
- Percentage-based section learning: split a level into sections (0-25%, 25-50%, ...), pick several, and practise them. In practice mode the mod learns timings only inside the picked sections, saves them per level, and reuses them in later attempts and full runs. It never replays inputs; every click stays yours.
- Practice-only auto-click and auto-release (wave, robot, dash)
- Training mode (hints only), performance mode, low-latency mode, no-hitch searches
- Live path view with **ghost comparison**: your original input trajectory (thin dashed amber) and the buffered trajectory (cyan) shown at the same time, both fading along the run, with a translucent copy of your icon replaying the buffered run, with a verdict ("yours: crash, buffered: safe, held 2f"), and a **death review** that redraws the last decision after you die so you can see why it did or did not work
- Vision (sidebar): live hitboxes for the player and objects (opacity, per-category filters, custom colours, artwork-vs-collision difference), predicted contact marker with frames remaining, near-miss detection, future vision (2, 5, 10 or 30 seconds ahead if you do nothing), frame advance (F6 freeze, F7 step) and a last-attempt ghost with the gap to it.
- Timing (sidebar): pre-input control engine, practice mode only: immediate, millisecond delay, frame offset, step offset, pre-tick injection, click before event (collision or next portal) and adaptive, with latency compensation and a latency fingerprint. Methods only hold a click back, never earlier.
- FPS stability engine (Performance > FPS and Tools): frame-time monitor with FPS, frame time, stability %, 1% low and the display rate; a frame-time graph; spike killer, prediction overload protection and dynamic quality that pause only the mod's optional extras (ghost icons, branching, future vision); stutter history saved to a file; a 60 s stability benchmark; three saveable performance profiles; a long-session monitor and the mod's own cost per frame. It cannot change the game's own frame rate.
- Difficulty engine (Difficulty section, practice mode only): collision forgiveness, slower game speed and portal grace, with Insane / Hard / Medium / Easy / Normal starting points, per-mode strength, stronger forgiveness in the hardest-looking parts, remember-per-level and three custom presets. Client-side assists, never legitimate; a DIFFICULTY NERF tag shows.
- AI autopilot (Analyzer > Auto, practice mode only): a planner that learns the level. It simulates keep versus press a few ticks ahead, takes the safe future, and learns from every death and clear; the knowledge is saved per level. It holds and releases for ship and wave. Your own presses are ignored while it plays; a small tag shows in the corner and cannot be turned off. Runs made with it are never legitimate.
- Predictive branching: at each decision it simulates the click at several delays side by side (0 to 8 frames), draws each faintly and lists which are safe.
- Analyzer tools that only read, never play: collision forecast and hazard warning, instant death explanation, counterfactual review (would a frame earlier or later have saved it?), spam meter, object scanner, physics-change map and a rough section difficulty estimate
- Practice-only autopilot tools on the Analyzer page: **auto-analyze** (a session that auto-clicks and auto-releases, restarts and keeps trying until a run completes the level or the attempt limit is reached), route recording and route replay. They work only in practice mode, check it every tick, and show a big BOT tag on screen that cannot be turned off. Runs made with them are never legitimate.
- Spam engine (Analyzer > Spam): **optimal CPS finder** (learns, per 5% of a level, which spam rates got through and which died, and shows the best one), plus practice-only **rate limiter**, **stabilizer**, **rhythm lock** and **adaptive spam rate**. The practice-only parts re-time or add clicks, check practice mode every tick and show a big SPAM ENGINE tag. Never legitimate.
- Macro analyzer: put a replay in the mod's `macros` folder (Analyzer > Macro) and it reports the input count, duration, clicks per second, shortest gap, hold times and spam sections. It only reads the file; nothing is replayed. JSON replays (.gdr, .json) are decoded; binary .gdr2 files are detected but their layout is not decoded yet.
- Drift check, death log, in-game console and log export
- Update checker (GitHub releases)

## Screenshots
_Screenshots will be added here._

## Installation
1. Install Geode for Geometry Dash 2.2081.
2. Download `aliou.aliousbuffer.geode` from the [latest release](https://github.com/Zeptoreal1/-predictive-input-buffer/releases/latest).
3. Put it in the `geode/mods` folder (or install it from the Geode mods menu) and restart the game.

## Keyboard shortcuts
| Key | Action |
|---|---|
| 6 | Cycle stage |
| 7 | Open the Aliou's Buffer menu (pause-menu button on mobile) |
| F8 | Copy the console log |
| F9 | Show / hide the in-game console |
| F10 | Path view |
| F11 | Forget this level's memory |

All keys can be changed in the mod settings or Geode's keybinds.

## Configuration
Open the menu in a level (key 7 or the pause-menu button) or from the logo button on the main menu, or use the mod settings. The menu is a dashboard with a sidebar of fourteen sections (Overview, Prediction, Game Modes, Automation, Memory, Sections, Performance, Visuals, Tools, Analyzer, Vision, Timing, Difficulty, About) and a live status panel showing whether the buffer is on, the prediction mode, active features and performance. The **Menu theme** setting offers Graphite (clean dark, default), AMOLED (pure black), Light (white with dark text), Graphite, Midnight, Ocean, Forest, Rose, Paper and Custom (pick your own main, secondary, accent and text colours), and **Menu background** can show your own picture behind the menu. The menu uses the Poppins font. Settings marked experimental or practice-only say so in their descriptions.

## Supported platforms
Windows, macOS, Android and iOS (as configured in `mod.json` and the CI workflow). See "Build status" below for what has actually been tested.

## Build
```
export GEODE_SDK=/path/to/geode
cmake -B build && cmake --build build --config RelWithDebInfo
```
Requires the Geode SDK 5.11.2 and a C++23 compiler. CI builds all platforms via `.github/workflows/build.yml`.

## Troubleshooting
- No buffering: check the mod is enabled and, if "Practice mode only" is on, that you are in practice mode.
- Clicks feel late: turn on Low latency mode, or lower the prediction budget.
- FPS drops: turn on Performance mode.
- Bad saves near moving parts: turn off "Predict move triggers" or "Predict moving objects", then use F8 and the death log to report it.
- Startup crash: send the Geode log (it contains startup checkpoints).

## Build status
v3.1.0 (rebrand, dashboard menu, section learning) was written without a Geode SDK, so it has not been compiled or run in-game yet; the CI workflow is the first real build. Expect to fix small compile errors in the new menu code.

## Credits and licence
Developer: Aliou. Aliou's Buffer is a fork of the predictive input buffer mod originally published as "Click Before Frames" by BASU (https://github.com/raresdalas1009/-predictive-input-buffer). The prediction engine is inherited from that project. The upstream repository contains no licence file at the time of this fork; see NOTICE.md. Font: Poppins (SIL OFL, see `resources/fonts`).

## Changelog
- UI refresh: Graphite is the new clean default theme, with quieter panels, improved text legibility, larger touch-friendly option rows, more breathable spacing, subtler navigation, and a fixed header version position. Existing themes remain available.
- v2.8: the ghost copies the full player state (slopes, reverse, sideways, forces, dash), size portals are simulated and mirror portals no longer stop the prediction.
- v2.10: wave tries 3 turn-away points, stops runs as soon as they are good enough (faster), and centers saves with a 1-tick safety margin. Console is see-through.
- v2.12 robot: presses count as safe if some hold length survives; robot auto-release (practice only).
- v2.13 level memory: learns per spot from your runs (delays that worked are tried first, spots where saves failed are left alone, risky spots marked in the path view).
- v2.15 spider: flips are judged by landing on the new surface, and crashes you could flip away from count as safe.
- v2.16 orbs: orbs usable on any tick inside them in predictions, orb alignment picks the best tick inside the orb, dash orbs held through in predictions, dash releases buffered, dash auto-release.
- v2.23 unlocked FPS: all windows (look-ahead, delays, landing, spam gap, auto-release window, memory) are converted from 240/s ticks to the real physics step rate, and the ghost uses the average step length.
- v2.24 FPS: prediction ghosts no longer spawn visual effects or leave nodes/actions behind (the FPS used to sink a little with every save).
- v2.25 ship (opt-in): ship presses/releases buffered with recovery-aware scoring, own small max delay, feathering passes through.
- v2.26 orb timing: presses already inside an orb are re-timed within the orb if that survives, learned orb timings are tried first, predictions try later clicks inside orbs.
- v2.27: late cube/ball crashes skip the search; experimental moving-object prediction (straight-line motion).
- v2.28 robust saves: each save is checked with the player slightly ahead/behind; fragile edge saves are swapped for a nearby delay that survives all three.
- v2.31: hazards overlapping you at the click (player-following spikes, noclip) are ignored by predictions.
- v2.34: with noclip, being inside a spike no longer makes the mod re-press the held button every tick.
- v2.35: Click Between Frames sync is back; low latency mode (no chained delays, max 1 frame, 3 ms searches).
- v2.36 CBF: rest of a split tick is collision-checked like the game does; logs show where in the tick a CBF click landed (@0.43) and separate 'safe' from 'safe only if you react by tX'.
- v2.37: position read from the per-step node position (CBF sync actually active now, drift check / path view / memory slices correct; memory restarts per level).
- v2.39: CBF Extrapolate is detected and shown in the console/export (it's visual only; predictions are unaffected).
- v2.40 UFO: crashes you could have flapped away from count as safe, landing counts as safe, smallest delay wins, spam guard for fast flapping.
- v2.41 FPS: moving-object tracking drops far objects and keeps a short moving-now list (was checking up to 4096 objects every step and every prediction).
- v2.43: more time at death spots - where you keep dying, react-only-safe inputs get the delay that pushes the crash furthest away.
- v2.44: in-game menu (pause menu 'Buffer' button or F7): stage, main switches, status, all settings / copy log / forget level. Ship: own spam gap (feathering is buffered), max delay 4, on by default.
- v2.45 ball: short flips count as landings, landings must last 8 ticks, spam guard for fast flipping; menu switch.
- v2.46 watermark (always on, not configurable): 'Aliou's Buffer | stage' in the level while the buffer is on, and 'Aliou's Buffer was on' on the level complete screen if it was on during the attempt.
- v2.49: ghost no longer touches collision blocks (could break collision triggers); spam guard sends waiting inputs instead of dropping them (lost clicks broke click/event triggers).
- v2.50: cuter menu: pink theme, pulsing hearts, floating hearts and sparkles, your own icon in the corner; switches turn pink when on.
- v2.51: cube jumps that bump a ceiling count as landings (buffer works under blocks); smart swing (flip-back scoring + spam guard); per-level settings; practice stats (per attempt + Stats button); training mode (hints only, no delays); death heatmap on the progress bar.
- v2.52: no popup after a death; attempt stats stay in the console, the Stats button and the level complete screen.
- v2.53: ghosts respect 'disable controls' from Options triggers (a hidden Player 2 parked under spikes no longer jumps into them in predictions; fixes 'no save: press dies in 0t' on every jump in Relief).
- v2.54: when the level disables Player 1's controls and you play Player 2 (Relief's wave parts), Player 2 is predicted; death log shows both players' modes.
- v2.55: in two-player levels, P2-side inputs made outside dual mode move Player 1, and are now buffered as P1 inputs (Relief's wave parts were predicted on the idle Player 2).
- v2.56: ding when a click is saved (setting + menu switch, on by default); menu opens smaller (78%).
- v2.57: watermark hidden in practice mode (always shown in normal mode while the buffer is on).
- v2.58: fix v2.51 regression (every cube landing counted as a ceiling bump, so short hops were called safe too early); settings changed in the settings popup during a level are kept for that level; ding sound preloaded.
- v2.59: low latency on by default and on every level (not per level); the F6 stage is one setting for every level and is kept between levels and restarts.
- v2.60: low latency off by default and switched off once on every install (still one setting for all levels).
- v2.61: prediction back to v2.48 behaviour: collision objects collide again in predictions, spam drops waiting inputs again, no ceiling-bump landing rule.
- v2.62: per-level settings off by default (switched off once): every level uses the same switches, like v2.43.1.
- v2.63: late-crash rule only skips clicks whose jump already landed (long jumps like Acheron's first were never saved); cube saves prefer the smallest delay whose jump lands safely.
- v2.64: a spot memory marked as 'saves failed here' gets saves again after you die there with the input left alone (it no longer blocks a jump forever).
- v2.65: live path view (F10): between clicks the path keeps updating (blue = do nothing, yellow = click now); a click's own path stays up briefly.
- v2.66: spam guard no longer drops waiting clicks: they fire one per tick in order, then the new input (no lost wave turns).
- v2.67: 'more time' at death spots delays wave / ship inputs by at most 1 frame (was up to the full max delay, which made fast zigzags feel late).
- v2.68: moving-object prediction follows curved / circular paths (rotate triggers) and spinning objects, not only straight lines; objects are put back exactly after each prediction.
- v2.69: cube / ball jump saves must land safely (no more 8-10 frame 'saves' that only moved the crash later in the same jump); memory delays are only reused if they land safely.
- v2.70: performance: a click's extra runs (robust check, drift check, path view) are skipped once the click has used its time budget; live path view updates 20x a second instead of 40x.
- v2.71: performance mode (menu switch): 4 ms per click, no robustness runs, no late orb-click retries, no drift check / live path; in-game console redraws once per step instead of per line.
- v2.72: searches stop after 4 delays when the crash comes at the same moment however late you click (next obstacle, not this click): far fewer budget hits and frame drops, mostly for robot and UFO.
- v2.73: robot / UFO / spider searches do a quick pass over every delay first (plain runs only), then the full scoring with the time left: saves further out are no longer missed because the time ran out after a few delays.
- v2.74: predictions can never change the real level: group toggles / spawns, item pickups, counters and item triggers caused by the hidden ghost are blocked (toggle orbs etc. could break triggers).
- v2.75: run check (records your longest run from the start, replays it on the hidden player to compare versions); level memory starts fresh (v3 files) and fades after 12 h away; robot / UFO / swing saves must be fully safe; auto time budget from your FPS; eased moving objects predicted; toggle orbs switching groups off are followed in predictions; presets (Safe / Balanced / Aggressive); rebindable keys; menu themes (Pink / Blue / Green / Dark).
- v2.76: auto budget fixed: no longer caps every click at 45% of a frame (2 ms at 240 fps cut cube searches short); it only lowers the budget to 4 ms while the game is already dropping frames. 'No save' lines say when a click was too late.
- v2.77: frame drops: each click's prediction time is capped at about one frame at your FPS (at least 4 ms); the run-check recording is saved when you leave or finish the level instead of on every new-best death.
- v2.78: orb timing for hard orb levels (Orbit): every tick inside the orb is tried, later orbs are clicked in the prediction too (several timings), the middle of the safe timing window is picked, and it must survive being half a tick off.
- v2.79: auto-click (practice only, off by default: clicks for you when doing nothing would crash and a click now is fully safe; cube / ball / UFO / robot / spider / swing); predictions go through mode portals (the hidden ghost switches mode instead of stopping); 'Spam: inputs in a row' setting; Purple menu theme (new default); stage / menu keys default to 6 / 7, and the console hint shows your keys.
- v2.80 (merged from the other v2.80 build): physics TPS setting + menu slider (240-1000; anything but 240 isn't legit, the watermark shows it); a mode portal you're still inside at the click no longer stops every prediction at t0 (Amethyst's first pink orb); after a portal switch only surviving the look-ahead counts; orb timings compared by when they crash counted from now (ORBIT), orb scans get 1.75x the time; the whole click shares its time budget (wave saves on GRIEF took 2-3 frames); level memory reuses the last delay that worked instead of the average, and each working save takes back one old failure; ghosts no longer play orb / trigger / destroy effects or leave particles on the real level; low latency's overrides stick (the wave margin was read again after it).
- v2.81: keys are real Geode keybinds (mod settings or Geode's keybinds popup, modifiers like Shift+ work; defaults 6 / 7 / F8 / F9 / F10 / F11 - keys you changed before go back to these once); update check on game start (setting, on by default) with a popup on the main menu when a newer version is on GitHub.
- v2.82: Android support (32 and 64-bit builds); a Console button in the menu (phones have no F9); the separate Windows console setting only shows on Windows.
- v2.83: macOS builds. iOS isn't built yet: Geode's iOS bindings currently fail to compile (missing FMOD types in the generated bindings), so it waits for a Geode update.
- v2.84: fixed the icon holding by itself at the start of an attempt: a delayed release that was still waiting when you died (or restarted) was dropped, so the game kept the button down. The game now always gets the release.
- v2.85: the cube no longer jumps by itself at the start of an attempt: a release made while your icon was dead never reached the mod, which then pressed for you when the attempt started. Every attempt now starts from the game's own button state.
- v2.86: fixed a crash when leaving a level and opening one again (v2.84/v2.85 could send a button to a level that was still loading); leaving a level now also forgets the button state.
- v2.87: Android crash when leaving a level fixed: the hidden ghost players were deleted while the level was still being torn down; on Android they're now only let go of.
- v2.88: dash orbs no longer flash before you reach them: effects a prediction ghost added to the real level (the dash start effect) are removed after each prediction.
- v2.90: v2.89 reverted (the full "Aliou's Buffer" watermark is back, no progress bar end cap).
- v2.92 (merged from the other build): new menu: a draggable window with tabs (Buffer, Prediction, Modes, Custom, Tools) in a space theme (black sky full of twinkling stars, sparkles, shooting stars), Orbitron / Exo 2 fonts, and a heart button on the main menu to open it outside levels too. Custom tab: per-mode frames, a slider for each game mode (your own icons) to pick how many frames cube, ship, ball, UFO, wave, robot, spider and swing can be held back. Prediction: move / rotate / toggle / spawn triggers ahead of you are predicted (with easing, group-parent pivots and spawn delays) and a self-check turns it off on levels where it keeps being wrong; predictions go through teleport, dual and solo portals; plan two clicks ahead (a crash your next click would handle isn't blamed on this one); smarter robot (tries other hold lengths); no-hitch searches (a search out of time goes on next tick instead of giving up). Pads no longer animate before you reach them.
- v2.93: auto update: the update popup's "Update now" downloads the .geode from the latest GitHub release, checks it's this mod and newer, and installs it (restart to use it).
- v2.94: the pause menu has a button (purple heart, bottom right) for the menu again, so phones can open it inside a level.
- v2.95: watermark back (v2.92 had dropped it) and smaller: "CBF | stage" in the bottom left, smaller still on phones, hidden in practice mode.
- v2.97: v2.96 reverted (no per-frame time budget, TPS setting read every frame again).
- v2.98: auto update fixed: the update popup now comes from the newest GitHub release (the same file 'Update now' installs), not from the code's version, which could be ahead of the release and made the install fail.
- v2.99: iOS support. The iOS build needed the FMOD header forced into Geode's generated iOS bindings, arm64-only for iOS, and the menu's title shine no longer uses CCPlace (not available to mods on iOS).
- v2.99.1: startup checkpoints in the Geode log (to find where some iPhones crash on start); the main menu button is skipped instead of crashing if its image is missing.
- v3.0.0: rebranded as Aliou's Buffer: new mod ID (aliou.aliousbuffer), logo and menu icon, new update source. New dashboard menu: nine sections, icon sidebar, live status panel, Aliou Blue theme (default), fits small screens. Prediction logic unchanged.
- v3.1.0: percentage-based section learning: split a level into percentage sections, pick several, and practise them (Sections page). In practice mode, level memory only learns inside the picked sections and per-section saves/deaths are counted; learned timings are saved per level and reused in later attempts and full runs. Optional restart at section end (practice only). New settings: section-learning, section-loop.
- v3.2.0: menu revamp: flat, clean look instead of the space/neon theme. Themes: AMOLED (pure black), Light (white, dark text) and Graphite. Optional custom background picture, Poppins sans-serif font, repeated options removed.
- v3.3.0: ghost comparison: with the path view on, both trajectories are drawn at once, your input as pressed (dashed amber) and the buffered input (solid cyan), joined at matching moments, with a one-line verdict by the player. New setting: ghost-compare (on by default, only visible while the path view is on).
- v3.4.0: five new menu themes (Midnight, Ocean, Forest, Rose, Paper) and a Custom theme with your own main, secondary, accent and text colours; the menu updates live when you change them in the settings.
- v3.5.0: death review: after a death the last decision's ghost comparison is drawn again and stays up through the next attempt until you pass that spot (setting ghost-review). Fixed the Visuals page layout, where the Ghost comparison switch was drawn under the Menu theme card and could not be tapped properly.
- v3.6.0: Analyzer page and tools: collision forecast, death explanation, counterfactual review (one frame earlier / later), spam meter (clicks per second and rhythm jitter), level scan with a physics-change list and a section difficulty estimate. These read the level and your runs; none of them sends inputs or searches for a route.
- v3.7.0: practice-only autopilot: auto-analyze sessions with an attempt limit, route recording (a completed practice run from the level start is saved per level) and route replay. Always practice mode only, with a big BOT tag on screen that cannot be turned off. New settings: route-record, route-replay, analyze-attempt-limit.
- v3.8.0: macro analyzer on the Analyzer page: drop a replay file in the macros folder and it is analysed (inputs, duration, CPS, holds, spam sections). JSON replays work; binary .gdr2 layout still to be added.
- v3.9.0: spam engine: optimal CPS learning (per level, per 5%), spam rate limiter, stabilizer, rhythm lock and adaptive spam rate. The limiter, stabilizer and lock are practice mode only with a big SPAM ENGINE tag. New settings: spam-learn, spam-limiter, spam-min-gap, spam-stabilizer, spam-stabilizer-cap, spam-rhythm-lock, spam-adaptive.
- v3.10.0: predictive branching (setting predictive-branching): several delays simulated side by side at each decision, drawn faintly and listed on screen. Collision forecast now also says when a click right now would crash. The practice-only tag is now small and sits in the top right corner (still always shown while a practice-only feature is on).
- v3.11.0: cleaner path view: thin lines that fade along the run, a small x for a crash, and a translucent copy of your icon (cube, ship, ball, UFO, wave or swing) replaying the buffered run slowly on a loop with faint snapshots along the way. New setting: ghost-icon.
- v3.12.0: Vision and Timing sections: live hitboxes with filters, opacity and custom colours, hitbox difference view, predicted contact, near-miss detection, future vision, frame advance, last-attempt ghost; pre-input control engine (practice only) with latency fingerprint. Auto-click now stands down once you press a button yourself. Fixed a build error (two helper functions had been removed by mistake).
- (upstream) v2.99.2: iOS: the mod's file is now code-signed (ad-hoc), some iOS launchers refused to load it ("missing code signature").
- (upstream) v2.99.3: iOS/macOS: one orb hook was too short to patch safely on Apple chips and corrupted the next game function, so it is skipped there (orbs still wait for the real press); one more startup checkpoint in the log.
- (upstream) v2.99.4: iOS: the purple heart button in the pause menu was missing (the game builds the pause menu differently on iOS), it is now also added when the game pauses.
- (upstream) v2.99.5: iOS without JIT works: 8 ghost-visual hooks that crashed the no-JIT launcher on the loading screen are left out on iOS (no effect on buffering; other platforms unchanged).
- (upstream) v3.0.0: autoplay (route planner, pathfinder, macros from your folder or Hyperbolus, the global brain, 2-player levels), a new animated window with an Account tab linked to Discord, an online counter, updates from the Aliou's Buffer site, and lighter FPS.
- (upstream) v3.0.1: the autoplay trail is hidden by default (setting: Show Autoplay Trail), and the AUTOPLAY label can be small and see-through in the bottom corner for showcases (setting: Autoplay Label).
- v3.13.0: merged the upstream update (iOS fixes, autoplay engine, lighter FPS, macros, per-step improvements). Aliou's Buffer sends nothing to any server: the upstream's online counter, account link and global brain are switched off, and autoplay (which the upstream ties to an account on its own site) is therefore unavailable here. Updates come from this repository's GitHub releases.
- v3.14.0: FPS stability engine; adaptive difficulty engine (practice only); smoother menu: the window eases open and the tab highlight glides between sections.
- v3.15.0: AI autopilot: practice-mode planner that simulates keep vs. press ahead, learns from deaths and clears, and saves what it learned per level.
