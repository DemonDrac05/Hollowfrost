# Hollowfrost: Vision
(codename: Crescentia)

## Premise
A special-forces soldier is sent with a team of scientists to investigate a mysterious illness
in an old village on an island far off the Nordic coast. On the way in, the team is torn apart
by unknown creatures. The lone survivor must endure the cold and the infected, uncover what was
done to the island in the name of immortality, and find a way out of a quarantine that destroys
anything trying to leave.

## Pillars
Every feature must serve at least one pillar.
1. **Uncover the truth.** Exploration is driven by evidence: notes, recordings, photos and
   remains lead from the first region to the laboratories deep in the valley.
2. **The island is hostile.** Cold, darkness, toxic fog, infected villagers and experiment subjects.
3. **Power has a price.** Crafting and serums make you stronger; permanent serums also bring
   you closer to what you fight.
4. **Survive together.** Co-op for up to 4 players; downed allies can be revived.

## Core loop
Explore and gather → craft and build → fight and survive → upgrade and progress.
Evidence found in each region opens the way to the next.

## Progression and gating
- Regions are separated by toxic fog, vines or rock walls. Passing requires progress:
  keys, equipment, evidence.
- Toxic fog warns first (coughing, blurred vision, rising sound), drains health fast,
  and only kills those who push on.
- Evidence board in the base: pinned clues connect and reveal the next location.
- No GPS: the island's map is recovered from a dead cartographer; the player has a compass.

## Survival
- Hunger, thirst, body temperature; wet clothing loses its insulation.
- Status effects, Green Hell as the baseline (bleeding, infection, poisoning, hypothermia),
  plus the immortality curse. <Special effects: to be designed.>
- Gear: the team came equipped for the cold, but most of it was lost in the massacre. 
  Recovering kit from fallen teammates is the first progression.
- Serums: cures (infection, curse) and permanent enhancements (strength, stamina, little speed).
- Plants: medicinal and stamina herbs, seasonal; plants die off-season, seeds must be saved.
- Farming and base building support survival; they are not the main genre.
- Eating infected meat causes worsening effects; a forest plant cures it. It also brings exhaustion 
  and headaches with strange sounds.

## Combat
- Early creatures are near boss-level: stealth and evasion come first.
- Noise: running and fighting attract enemies.
- Assassination with readable rules (from behind, unaware); weak or infected targets always die.
- Parry and critical finishers; the finisher chance grows with enhancement serums.

## Death and difficulty
- Checkpoints: explorer camps and player-built beds.
- Solo: respawn at a checkpoint and return to recover belongings; some items are lost,
  permanent items are kept.
- Co-op: downed state, allies can revive.
- Hard mode: tougher enemies and bosses, random status effects on hit.
  Enemy scaling by player count: to be tested.

## Time
- 1 day = 20 real minutes. Day/night ratio follows the season (midnight sun ↔ polar night).
- 1 season = 14 days (~4.7 h of play); 1 year ≈ 19 h.
- Survival rates are measured in game time, so day length can be tuned freely.

## World
- One fixed island, bounded by the sea. Designers paint the macro layout (region map image);
  algorithms generate the details. Chunk-streamed.
- First region: Nordic forest. Deeper regions have anomalous climates caused by the experiments.
- Lakes freeze in winter. Four seasons shared by all players.
- World state is derived (never stored), player-made (stored per chunk) or living
  (stored with a timestamp, fast-forwarded on load).
- The island is sealed: radar detects and destroys anything that leaves. Escape means reaching the labs, 
  to expose the truth or to disable the defence system.

## Art and audio direction
- Low-poly, flat-shaded; muted, washed-out palette; fog. Slope decides snow, rock and moss.
- Readability: enemies and interactables must read through fog (silhouette, contrast,
  subtle highlights). Brightness option.
- First-person hands and tools are the hero assets.
- Audio: dark and oppressive. Sound carries the horror: footsteps, breathing, wind, silence.
  <More references needed.>
- UI: minimal, diegetic where possible.

## Team
- Tien Thang Phan: programming, systems, tools.
- Other art and audio: learned, bought or contracted.
- Time: about 2–4 hours per day.

## Technical constraints
- Unreal Engine 5.8, C++-first; Blueprints for data and tuning only.
- Server-authoritative. Listen server now, dedicated-server-ready code.
- Clients generate chunks from the seed and layout; the server sends only changes,
  verified by checksums.
- Co-op PvE: client hit detection is trusted, the server sanity-checks.
- Minimum spec: Intel Iris Xe, 16 GB RAM, Low settings at full resolution, 30 FPS stable.
- No volumetric clouds on Low/Medium: sky dome + Sky Atmosphere. Weather is data, the sky only renders it.

## Non-goals (for now)
- PvP, more than 4 players, realistic graphics, vehicles, an infinite world.
- Content for multiple endings (ideas are kept, nothing is built).
- Structural integrity for buildings; voxel terrain (reserved for caves later).

## Open questions
- Ending structure: 5–6 endings tied to how far the player embraces immortality?
- The special status effects of the curse.