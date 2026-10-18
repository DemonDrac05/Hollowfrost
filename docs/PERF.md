# Performance Test Results

Conditions: Development build, plugged in, Best performance power mode,
10-minute warm-up before measuring, 1080p fullscreen.

## 1. Baseline: default Basic level (with volumetric clouds)

| Device   | Settings               | Frame     | Game      | Draw      | GPU       | FPS       |
| -------- | ---------------------- | --------- | --------- | --------- | --------- | --------- |
| HP       | Low, 50%               | 27 - 29   | 6 - 7     | 27 - 29   | 27 - 29   | 32 - 33   |
| HP       | Low, 67%               | 51 - 52   | 6 - 7     | 51 - 52   | 51 - 52   | 18 - 19   |
| HP       | Low, 67%, after 15 min | 54 - 55   | 5 - 7     | 54 - 55   | 54 - 55   | 17 - 18   |
| ThinkPad | Low, 50%               | 9.2 - 9.7 | 2.2 - 2.3 | 9.2 - 9.7 | 9.2 - 9.7 | 101 - 103 |

Finding: `scalability 0` sets r.ScreenPercentage to 50. Volumetric clouds cost about 80% of GPU time.

## 2. Without volumetric clouds: resolution

| Device | Settings  | Frame | Game | GPU | FPS |
| ------ | --------- | ----- | ---- | --- | --- |
| HP     | Low, 50%  | 3.9 - 4.1 | 2.6 - 2.7  | 3.9 - 4.1 | 250 - 260 |
| HP     | Low, 67%  | 4.2 - 4.5 | 2.9 - 3.0 | 4.2 -4.5 | 220 - 230 |
| HP     | Low, 100% | 5.6 - 6.3 | 3.1 - 3.9| 5.6 - 6.3 | 170 - 180 |

## 3. Without volumetric clouds: feature cost (HP, Low, 100%)

| Experiment                      | GPU (ms)  | Saved vs. baseline (ms) |
| ------------------------------- | --------- | ----------------------- |
| Baseline (clouds off)           | 5.6 - 6.3 | -                       |
| Virtual Shadow Maps off         | 5.6 - 6.3 | ~0                      |
| TSR -> FXAA                     | 5.6 - 6.3 | ~0                      |
| Lumen GI off                    | 5.6 - 6.3 | ~0                      |
| Real-time Sky Light capture off | 5.6 - 6.3 | ~0                      |
| All of the above off            | 5.6 - 6.3 | ~0                      |

Finding: at Low these features are already off or negligible in an empty scene.
Re-measure once real content exists: shadow and anti-aliasing costs grow with scene complexity.

## 4. Two-player co-op over LAN (first-person template, clouds off)

| Device              | Role          | Frame (ms) | Game (ms) | GPU (ms) | FPS | Ping (ms) | In / Out (B/s) |
| ------------------- | ------------- | ---------- | --------- | -------- | --- | --------- | -------------- |
| ThinkPad            | Listen server | 6.65       | 6.60      | 3.54     | 150 | -         | 4,336 / 2,903  |
| HP                  | Client        | 11.39      | 8.06      | 11.53    | 88  | 17        | 3,284 / 4,649  |

Finding: characters (skeletal mesh, animation, shadows) roughly double the HP frame time.
Measure the cost of one enemy before designing enemy counts.