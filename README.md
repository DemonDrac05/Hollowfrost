# Hollowfrost

A co-op survival horror game set on a quarantined island off the Nordic coast.
Built C++-first in Unreal Engine 5. *(Codename: Crescentia)*

![Early terrain prototype](docs/images/farm_topdown.png)
*Early procedural terrain prototype.*

## About
Stardew Valley, and Eric Barone's story behind it, are a big part of why I became a game programmer.
This is my long-term dream project. It started as a 3D farming sim (tagged `farm-prototype`)
and grew into something darker: a special-forces soldier, the lone survivor of an investigation
team, must uncover what was done to an island in the name of immortality.

It is also where I sharpen my C++ and Unreal Engine skills, the craft that will fund that dream.

- **Vision:** [docs/VISION.md](docs/VISION.md)
- **First milestone:** [docs/SLICE.md](docs/SLICE.md), a 2–3 hour vertical slice

## Current status
Pre-production. Implemented so far:
- Procedural terrain: fractal Perlin noise shaped by designer-editable curves
- Exact land shares by percentile ranking, with layout guarantees (border mountains, exit gap, clearing)
- Deterministic, seed-based generation with independent RNG streams per pass
- Data/view separation: world data is pure, rendering only reads it
- Live preview in the editor; placeholder rendering with instanced meshes (HISM)

## Architecture
```text
WorldGenSettings -> FarmGenerator -> FarmGrid (world data)
                                         ^
                                         |
                                      FarmMap (reads data, builds visuals)
```

## Key design decisions
- **Data/view separation.** World data is pure; visuals only read it, and all edits go through one
  owner so data and visuals never drift apart. A dedicated server can keep the data and skip the visuals.
- **Deterministic generation.** Every pass draws from its own `FRandomStream`, seeded from the world seed
  and a per-pass salt. The same seed and settings always rebuild the same world.
- **Exact shares, separate placement.** Region values are ranked into percentiles, so curve segments
  map to exact land shares. Placement biases are applied before ranking and never change those shares.
- **Units that rule out invalid states.** Heights are baked in cm, tree offsets are tile fractions,
  and trees are keyed by tile index.
- **Planned: changes over the network, not worlds.** Clients regenerate chunks from the seed;
  the server sends only player-made changes, verified by checksums.

## Roadmap
- [x] Procedural terrain prototype
- [ ] Pre-production: vision, vertical slice plan, performance baseline on a low-end laptop
- [ ] Networking foundation: first-person co-op over a listen server
- [ ] Chunk-streamed island with a low-poly terrain mesh
- [ ] First networked interaction and persistence
- [ ] Vertical slice: the village, the massacre, the first boss

## Building
Requirements: Unreal Engine 5.8, JetBrains Rider (or Visual Studio 2022 with the C++ game
development workload), Git LFS.

1. `git lfs install`, then clone the repository.
2. Open `Crescentia.uproject` directly in Rider, or right-click it and choose
   *Generate Visual Studio project files*.
3. Build the `CrescentiaEditor` target in *Development Editor* and run.
4. Open `Content/World/Lvl_MainWorld` and press Play.
   Generation settings live on `Content/World/Farm/BP_FarmMap`.

## Contact
- GitHub: https://github.com/DemonDrac05
- Email: thangphanfk@gmail.com
- LinkedIn: https://www.linkedin.com/in/thang-phan-3b702321b