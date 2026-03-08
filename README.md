# ROS 2 EKF SLAM — TurtleBot3
**Author:** Kyaw Linn Khant

![ROS 2](https://img.shields.io/badge/ROS_2-Humble-22314E?logo=ros)
![C++](https://img.shields.io/badge/C++-17-00599C?logo=cplusplus)
![Python](https://img.shields.io/badge/Python-3.10-3776AB?logo=python)
![TurtleBot3](https://img.shields.io/badge/TurtleBot3-Burger-FF6600)
![License](https://img.shields.io/badge/License-MIT-green)
---

## Demo

[![EKF SLAM Demo](https://img.youtube.com/vi/RIUTl7c3cwI/0.jpg)](https://youtu.be/2M8OZtKfG7k)

---

## Overview

This repository implements **Extended Kalman Filter (EKF) SLAM** on a TurtleBot3 Burger using ROS 2. The robot simultaneously builds a map of cylindrical landmarks in its environment and localizes itself within that map — all in real time.

Three independent pose estimates are maintained and visualized side-by-side:

| Robot Color | Estimate Type | Description |
|-------------|--------------|-------------|
| 🔴 Red      | Ground Truth  | Simulated true pose (NuSim) |
| 🔵 Blue     | Odometry only | Dead-reckoning from wheel encoders |
| 🟢 Green    | EKF SLAM      | Fused odometry + landmark observations |

---

## Repository Structure
```
slam-project/
├── turtlelib/            # Core math library: SE2, kinematics, EKF, circle fitting
├── nuturtle_description/ # URDF/Xacro robot models and RViz configs
├── nusim/                # Simulator: arena, obstacles, sensor noise
├── nuturtle_control/     # Wheel control and odometry node
└── nuslam/               # EKF SLAM and landmark detection node
```

---

## Package Summaries

### [`turtlelib`](turtlelib/README.md)
A standalone CMake library providing all mathematical primitives needed for robot control and SLAM: 2D geometry, SE(2) transformations, differential drive kinematics, EKF SLAM state estimation, and Taubin circle fitting for landmark detection.

### [`nuturtle_description`](nuturtle_description/README.md)
URDF and Xacro models for the NuTurtle robot. Supports spawning multiple colored robot instances for simultaneous visualization of different pose estimates in RViz.

### [`nusim`](nusim/README.md)
The simulation environment. Renders a walled arena with cylindrical obstacles, simulates the red robot's motion, and publishes fake sensor data (encoder ticks, LiDAR scans) with configurable noise.

### [`nuturtle_control`](nuturtle_control/README.md)
Handles low-level robot control — receives velocity commands, converts them to wheel speeds, and computes dead-reckoning odometry from encoder feedback.

### [`nuslam`](nuslam/README.md)
The full SLAM stack. Clusters LiDAR returns, fits circles to identify landmarks, performs data association via Mahalanobis distance, and runs the EKF predict/correct loop to maintain a real-time map and pose estimate.

---

## Quick Start
```bash
# Full SLAM in simulation
ros2 launch nuslam slam.launch.xml

# Landmark detection only (no SLAM)
ros2 launch nuslam landmark_detect.launch.xml

# Simulation with robot control and odometry
ros2 launch nuturtle_control start_robot.launch.xml
```

---

## License

MIT License — Copyright (c) 2024 Kyaw Linn Khant
