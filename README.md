<p align="center">
  <img src="logo.png" width="120" alt="Aliou's Buffer logo">
</p>Aliou's Buffer

Predictive input buffering and gameplay analysis for Geometry Dash.

Aliou's Buffer is a "Geode" (https://geode-sdk.org) mod that predicts upcoming player movement and adjusts input timing to help prevent avoidable collisions.

When a press or release is predicted to cause a collision, the mod can delay that input by a configurable number of physics ticks. Its prediction system accounts for orbs, pads, portals, moving objects, triggers, and all supported game modes.

---

Important: Fair-play notice

Some features provide gameplay assistance and are intended for practice and experimentation.

Runs using automated inputs, route replay, input assistance, or a physics rate other than 240 TPS may not qualify as legitimate completions. Do not submit assisted runs for verification or leaderboard placement.

Practice-only features are restricted to practice mode and display an on-screen indicator while active. Features that only analyse gameplay without sending inputs are separate from automated assistance.

Features

1. Predictive input buffering

- Predicts player trajectories before an input is processed.
- Buffers presses and releases when the predicted input would cause a collision.
- Supports cube, ship, ball, UFO, wave, robot, spider, and swing.
- Accounts for orbs, pads, portals, moving objects, and relevant triggers.
- Supports orb alignment and timing adjustments.
- Plans multiple clicks ahead to avoid unnecessary delays.
- Uses robust prediction checks to avoid fragile saves.
- Includes per-level memory and configurable delay limits.

2. Prediction and visualisation

- Live path view: Displays predicted player movement.
- Ghost comparison: Compares the original input trajectory with the buffered trajectory.
- Death review: Reconstructs the last important prediction after a death.
- Predictive branching: Simulates multiple possible input delays side by side and identifies which predictions survive.
- Future vision: Previews predicted movement up to 2, 5, 10, or 30 seconds ahead.
- Hitbox visualisation: Displays player and object collision boxes.
- Collision markers: Shows predicted contact points and remaining frames.
- Near-miss detection: Identifies close calls.
- Frame advance: Freeze gameplay with F6 and advance one frame at a time with F7.
- Last-attempt ghost: Displays a previous attempt and the difference from the current run.

3. Timing and latency tools

The Timing section contains the Pre-Input Control Engine.

Available timing methods include:

- Immediate input — no intentional delay.
- Millisecond delay — adds a configurable delay.
- Frame offset — schedules input relative to a target frame.
- Step offset — schedules input relative to a physics step.
- Pre-tick injection — attempts to schedule input before a relevant game update.
- Click Before Event — schedules input relative to a predicted event, such as a collision or portal transition.
- Adaptive timing — adjusts scheduling using measured latency.

Additional tools:

- Latency compensation.
- Latency fingerprinting.
- Input timing analysis.
- Configurable timing offsets.

These methods control when an input is processed; they cannot send an input into the past. Actual scheduling precision depends on the game's update and input-processing pipeline.

4. Level memory and section learning

- Remembers successful and unsuccessful input timings.
- Stores settings and timing information per level.
- Tracks deaths and successful saves.
- Displays a death heatmap.
- Splits levels into percentage-based sections.
- Lets you select individual sections for focused practice.
- Learns timings inside selected sections in practice mode.
- Saves section-specific information for later attempts.
- Optionally restarts at the end of a selected section.

Section learning does not replay your inputs. It learns timing information from your attempts.

5. Practice automation

These features are restricted to practice mode.

Auto-click and auto-release

- Automatically handles supported inputs when configured.
- Supports relevant game modes, including wave, robot, and dash interactions.
- Stops assisting when manual input takes over.

Auto-analysis

- Runs automated practice attempts.
- Restarts after deaths.
- Continues until a run completes or the configured attempt limit is reached.

Route recording and replay

- Records completed routes from the level start.
- Saves routes per level.
- Replays recorded inputs in practice mode.

Automated features display a persistent BOT indicator while active.

6. Spam engine

Available under Analyzer → Spam.

- Optimal CPS finder: Learns which spam rates succeed or fail in each 5% level segment.
- Rate limiter: Controls the minimum interval between inputs.
- Stabilizer: Reduces inconsistent spam timing.
- Rhythm lock: Maintains a more consistent input rhythm.
- Adaptive spam rate: Adjusts spam timing based on observed results.

The rate limiter, stabilizer, rhythm lock, and adaptive spam features are practice-only and display a persistent SPAM ENGINE indicator.

7. Analyzer tools

The Analyzer section provides tools that inspect gameplay and level data.

- Collision forecast.
- Instant death explanations.
- Counterfactual review: checks whether an input one frame earlier or later would have changed the result.
- Spam and click-rate analysis.
- Object scanner.
- Physics-change map.
- Estimated section difficulty.
- Macro analysis.

Macro analyzer

Place a replay file in the mod's "macros" folder and open Analyzer → Macro.

It reports:

- Input count.
- Replay duration.
- Clicks per second.
- Shortest input gap.
- Hold durations.
- Spam-heavy sections.

JSON replay formats, including ".gdr" and ".json", are decoded. Binary ".gdr2" files are detected, but their internal layout is not yet decoded.

Macro analysis only reads replay files. It does not execute or replay them.

8. Performance and diagnostics

- Low-latency mode.
- Performance mode.
- Configurable prediction budgets.
- No-hitch prediction searches.
- Frame-drift checks.
- Death logs.
- In-game console.
- Log export.
- Update checker using GitHub releases.

---

Screenshots

Screenshots will be added here.

---

Installation

1. Install "Geode" (https://geode-sdk.org) for Geometry Dash 2.2081.
2. Download "aliou.aliousbuffer.geode" from the "latest GitHub release" (https://github.com/Zeptoreal1/-predictive-input-buffer/releases/latest).
3. Place the file in your "geode/mods" folder, or install it through Geode's mod menu.
4. Restart Geometry Dash.

---

Keyboard shortcuts

Key| Action
"6"| Cycle prediction stage
"7"| Open Aliou's Buffer menu
"F6"| Freeze gameplay
"F7"| Advance one frame
"F8"| Copy console log
"F9"| Show or hide the in-game console
"F10"| Toggle live path view
"F11"| Forget the current level's memory

On mobile, use the pause-menu button to open the mod menu.

All supported shortcuts can be changed through the mod settings or Geode's keybind settings.

---

Configuration

Open the dashboard using:

- "7" during a level.
- The Buffer button in the pause menu.
- The logo button on the main menu.
- Geode's mod settings.

Dashboard sections

The dashboard is organised into thirteen sections:

Section| Purpose
Overview| Main controls and live status
Prediction| Prediction engine configuration
Game Modes| Individual mode settings
Automation| Automated practice features
Memory| Per-level learning and saved data
Sections| Percentage-based section learning
Performance| Prediction budgets and performance controls
Visuals| Path view and visual settings
Tools| Additional utilities
Analyzer| Level, input, and macro analysis
Vision| Hitboxes, future vision, and frame advance
Timing| Input scheduling and latency tools
About| Version and mod information

The dashboard includes a live status panel showing whether buffering is enabled, the current prediction stage, active features, and performance information.

Menu customisation

Available themes:

- AMOLED
- Light
- Graphite
- Midnight
- Ocean
- Forest
- Rose
- Paper
- Custom

The Custom theme lets you choose your own main, secondary, accent, and text colours.

You can also set a custom background image behind the menu. The interface uses the Poppins font.

Settings marked Experimental or Practice-only are identified in their descriptions.

---

Supported platforms

The project is configured for:

- Windows
- macOS
- Android
- iOS

Actual build and runtime support depends on the current Geode SDK, platform bindings, and CI build results.

---

Building from source

Requirements

- Geode SDK 5.11.2
- C++23-compatible compiler
- CMake

Build commands

export GEODE_SDK=/path/to/geode

cmake -B build
cmake --build build --config RelWithDebInfo

The GitHub Actions workflow in ".github/workflows/build.yml" handles platform builds.

---

Troubleshooting

Problem| Suggested fix
Buffering does not work| Check that the mod is enabled and review any practice-mode restrictions.
Inputs feel delayed| Try Low Latency mode or reduce the prediction budget.
FPS drops| Enable Performance mode.
Predictions are inaccurate around moving objects| Try disabling Predict Move Triggers or Predict Moving Objects.
Saves fail near moving objects| Review the death log and export the console log with F8.
Game crashes during startup| Check the Geode log for startup checkpoints.

When reporting an issue, include the Geometry Dash version, Geode version, mod version, relevant settings, and log output.

---

Credits and licence

Developer: Aliou

Aliou's Buffer is a fork of the predictive input buffer project originally published as Click Before Frames by BASU.

- Original repository: https://github.com/raresdalas1009/-predictive-input-buffer
- Font: Poppins, licensed under the SIL Open Font License.
- See "NOTICE.md" for upstream attribution and licensing information.

The upstream repository did not contain a licence file at the time this fork was created.

---

Changelog

v3.12.0

- Added Vision and Timing dashboard sections.
- Added live hitboxes, hitbox filters, opacity controls, custom colours, and collision-difference view.
- Added predicted contact markers, near-miss detection, future vision, frame advance, and last-attempt ghost.
- Added the Pre-Input Control Engine and latency fingerprinting.
- Auto-click now stops assisting when manual input is detected.
- Fixed a build error involving two removed helper functions.

v3.11.0

- Improved live path visualisation with thinner fading trajectories and crash markers.
- Added a translucent ghost icon that replays the buffered trajectory.
- Added the "ghost-icon" setting.

v3.10.0

- Added predictive branching to simulate multiple delays side by side.
- Improved collision forecasts.
- Reduced the size of the practice-only indicator and moved it to the top-right corner.

v3.9.0

- Added the Spam Engine.
- Added optimal CPS learning, rate limiting, stabilisation, rhythm lock, and adaptive spam timing.
- Practice-only spam controls display a persistent indicator.

v3.8.0

- Added macro analysis for input count, duration, CPS, hold times, and spam sections.
- Added JSON replay decoding.
- ".gdr2" detection added; binary decoding remains unfinished.

v3.7.0

- Added practice-only automated analysis, route recording, and route replay.
- Added configurable attempt limits and a persistent BOT indicator.

v3.6.0

- Added the Analyzer section.
- Added collision forecasts, death explanations, counterfactual review, spam analysis, object scanning, physics-change mapping, and section difficulty estimates.

v3.5.0

- Added death review to reconstruct the last prediction after a death.
- Fixed the Ghost Comparison settings layout.

v3.4.0

- Added Midnight, Ocean, Forest, Rose, Paper, and Custom menu themes.

v3.3.0

- Added simultaneous original and buffered trajectory comparison.
- Added the "ghost-compare" setting.

v3.2.0

- Reworked the dashboard with a cleaner interface.
- Added AMOLED, Light, and Graphite themes.
- Added custom background images and the Poppins font.

v3.1.0

- Added percentage-based section learning.
- Added per-section memory, save/death tracking, and optional practice-mode section restarts.

v3.0.0

- Rebranded the project as Aliou's Buffer.
- Introduced the "aliou.aliousbuffer" mod ID.
- Added a new dashboard, logo, menu icon, and update source.

Earlier releases: v2.8–v2.99.1

The v2 series introduced the core prediction engine and progressively added support for game modes, moving objects, orbs, portals, level memory, performance controls, automation, and platform compatibility.

Major milestones included:

- v2.8–v2.16: Improved ghost physics, wave prediction, robot support, level memory, spider flips, and orb timing.
- v2.23–v2.28: Added unlocked-FPS timing conversion, ship support, moving-object prediction, and robust save checks.
- v2.31–v2.40: Improved noclip handling, Click Between Frames synchronisation, UFO support, and input timing.
- v2.41–v2.50: Improved moving-object tracking, performance, the in-game dashboard, Android support, and menu customisation.
- v2.51–v2.69: Added per-level settings, practice statistics, death heatmaps, dual-player prediction, smarter swing handling, and improved orb and landing logic.
- v2.70–v2.80: Major performance improvements, adaptive prediction budgets, automated practice tools, expanded trigger prediction, and configurable physics TPS.
- v2.81–v2.90: Added real Geode keybinds, update installation, Android and macOS support, and fixes for input-state and lifecycle issues.
- v2.92–v2.99.1: Added the redesigned dashboard, per-mode delay controls, advanced trigger prediction, improved update handling, iOS support, and startup diagnostics.

For detailed historical changes, consult the repository's commit history and releases.

---

<p align="center">
  <b>Aliou's Buffer</b><br>
  Predict ahead. Understand every input. Improve your consistency.
</p>
