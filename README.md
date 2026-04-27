# ROS 2 EKF SLAM — TurtleBot3

> Full SLAM stack in C++17: Taubin circle fitting for landmark detection, Mahalanobis data association, and EKF predict/correct cycle — with three simultaneous pose estimates visualised in RViz.

![ROS 2](https://img.shields.io/badge/ROS_2-Humble-22314E?logo=ros)
![C++](https://img.shields.io/badge/C++-17-00599C?logo=cplusplus)
![Python](https://img.shields.io/badge/Python-3.10-3776AB?logo=python)
![TurtleBot3](https://img.shields.io/badge/TurtleBot3-Burger-FF6600)
![License](https://img.shields.io/badge/License-MIT-green)

---

## Demo

[![EKF SLAM Demo](https://img.youtube.com/vi/RIUTl7c3cwI/maxresdefault.jpg)](https://youtu.be/RIUTl7c3cwI)

---

## What this demonstrates

| Capability | Implementation |
|------------|---------------|
| Landmark extraction from LiDAR | Taubin algebraic circle fitting |
| Data association | Mahalanobis distance threshold |
| State estimation | EKF with augmented landmark states |
| Localization accuracy | <5 cm average positional error vs ground truth |
| Real-time performance | 10 Hz SLAM cycle on TurtleBot3 compute |

Three pose estimates run **simultaneously** and are colour-coded in RViz:

| Colour | Source | Method |
|--------|--------|--------|
| Red | NuSim | Ground truth (simulated) |
| Blue | Odometry | Dead-reckoning — encoder ticks only |
| Green | EKF SLAM | Fused odometry + landmark corrections |

The gap between blue and green is the observable benefit of sensor fusion closing over time.

---

## Algorithm pipeline

```
LiDAR scan
    │
    ▼
Cluster returns (range-distance threshold)
    │
    ▼
Taubin circle fit per cluster → (x, y, radius)
    │
    ▼
Data association — Mahalanobis distance to known landmarks
    ├── Known landmark → EKF update (correct)
    └── New landmark   → State augmentation (initialise)
    │
    ▼
EKF predict step — motion model from encoder ticks
    │
    ▼
Robot pose + landmark map (maintained jointly)
```

---

## Why EKF over alternatives?

- **vs. Particle filter (AMCL):** EKF gives a closed-form solution and scales O(N²) in landmark count — fine for structured indoor environments with <50 landmarks. No particle degeneracy.
- **vs. Graph SLAM:** No loop-closure in this version — incremental EKF is sufficient for the scale of the demo environment.
- **vs. ORB-SLAM2:** No camera dependency; pure 2D LiDAR is more robust to lighting and texture-free walls in lab settings.

---

## Package structure

```
slam_turtlebot_ros/
├── turtlelib/              C++ math library: SE(2), EKF, Taubin fit
├── nuturtle_description/   URDF/Xacro + multi-robot RViz configs
├── nusim/                  Simulator: arena, obstacles, noise injection
├── nuturtle_control/       Velocity → wheel speeds → odometry
└── nuslam/                 Full SLAM node: detect → associate → fuse
```

---

## Quick start

```bash
# Full EKF SLAM in simulation
ros2 launch nuslam slam.launch.xml

# Landmark detection only (no full SLAM)
ros2 launch nuslam landmark_detect.launch.xml

# Robot control + odometry (no SLAM)
ros2 launch nuturtle_control start_robot.launch.xml
```

---

## Author

**Kyaw Linn Khant** — Robotics & AI Engineer  
[Portfolio](https://kyawlinnkhant.github.io/my_portfolio/) · [LinkedIn](https://linkedin.com/in/kyawlinnkhant)
