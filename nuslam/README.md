# nuslam

This package implements the full Extended Kalman Filter (EKF) SLAM pipeline. It detects cylindrical landmarks from LiDAR scans, associates them with a persistent map, and fuses landmark observations with wheel odometry to maintain a real-time estimate of both the robot's pose and the landmark positions (the green robot).

---

## How It Works

```
LiDAR scan
    │
    ▼
┌─────────────────┐
│   Clustering    │  Group nearby scan points into clusters
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  Circle Fitting │  Fit a circle to each cluster (Taubin algorithm)
└────────┬────────┘
         │
         ▼
┌──────────────────────┐
│  Data Association    │  Match detections to known landmarks
│  (Mahalanobis dist.) │  or initialize new ones
└────────┬─────────────┘
         │
         ▼
┌─────────────────┐      ┌──────────────────────┐
│  EKF Correct    │◄─────│  EKF Predict         │
│  (measurement   │      │  (odometry/motion    │
│   update)       │      │   model update)      │
└────────┬────────┘      └──────────────────────┘
         │
         ▼
   Green robot pose + landmark map
```

---

## Nodes

### `slam`

The main EKF SLAM node. Subscribes to wheel joint states and LiDAR-based landmark detections, and publishes the SLAM-corrected pose and map.

**Parameters**

| Parameter | Type | Description |
|-----------|------|-------------|
| `body_id` | `string` | Robot body frame (e.g. `green/base_footprint`) |
| `odom_id` | `string` | Odometry frame (e.g. `odom`) |
| `wheel_left` | `string` | Left wheel joint name |
| `wheel_right` | `string` | Right wheel joint name |
| `wheel_radius` | `double` | Wheel radius (m) |
| `track_width` | `double` | Track width (m) |
| `obstacles.r` | `double` | Expected landmark radius (m) |
| `obstacles.h` | `double` | Expected landmark height (m) |

**Published Topics**

| Topic | Type | Description |
|-------|------|-------------|
| `/odom` | `nav_msgs/Odometry` | SLAM-corrected odometry |
| `/green/path` | `nav_msgs/Path` | SLAM trajectory for RViz |
| `~/obstacles` | `visualization_msgs/MarkerArray` | EKF landmark position estimates |

**Subscribed Topics**

| Topic | Type | Description |
|-------|------|-------------|
| `/joint_states` | `sensor_msgs/JointState` | Wheel encoder data (motion model) |
| `/nusim/fake_sensor` | `visualization_msgs/MarkerArray` | Landmark observations from simulator |

**Services**

| Service | Type | Description |
|---------|------|-------------|
| `/initial_pose` | `std_srvs/Empty` | Reset SLAM state to origin |

---

### `landmarks`

Processes raw LiDAR scans to detect cylindrical landmarks. Performs point clustering and circle fitting, then publishes the fitted circles for the SLAM node to consume.

**Parameters**

| Parameter | Type | Description |
|-----------|------|-------------|
| `obstacles.r` | `double` | Expected obstacle radius (m) |
| `obstacles.h` | `double` | Expected obstacle height (m) |

**Published Topics**

| Topic | Type | Description |
|-------|------|-------------|
| `~/clusters` | `visualization_msgs/MarkerArray` | Raw point clusters (debug visualization) |
| `~/circle_fit` | `visualization_msgs/MarkerArray` | Fitted circle centers and radii |

**Subscribed Topics**

| Topic | Type | Description |
|-------|------|-------------|
| `/nusim/fake_lidar_scan` | `sensor_msgs/LaserScan` | Simulated LiDAR scan |

---

## Launch Files

### `slam.launch.xml`

Launches the complete SLAM stack: simulator, controller, odometry, landmark detection, and EKF SLAM. This is the primary launch file for the full system.

```bash
ros2 launch nuslam slam.launch.xml
```

Starts:
- `nusim` (simulator — red robot, arena, obstacles)
- `nuturtle_control` (controller + blue robot odometry)
- `landmarks` (LiDAR clustering + circle fitting)
- `slam` (EKF SLAM — green robot)
- RViz with `nuslam_sim.rviz`

---

### `landmark_detect.launch.xml`

Launches only the landmark detection pipeline (without SLAM). Useful for tuning the clustering and circle fitting parameters.

```bash
ros2 launch nuslam landmark_detect.launch.xml
```

---

## RViz Color Convention

| Color | Robot | Meaning |
|-------|-------|---------|
| 🔴 Red | `nusim` | Ground truth simulated pose |
| 🔵 Blue | `odometry` | Dead-reckoning estimate (wheel odometry only) |
| 🟢 Green | `slam` | EKF SLAM estimate (odometry + landmarks) |

---

## EKF SLAM Details

The EKF state vector is defined as:

```
ξ = [ θ, x, y, mx₁, my₁, mx₂, my₂, ..., mxN, myN ]ᵀ
```

where `(θ, x, y)` is the robot pose and `(mxⱼ, myⱼ)` are landmark positions in the world frame. The filter runs at the wheel odometry rate and processes each landmark observation individually using the standard EKF correction equations.

**Data association** uses the Mahalanobis distance between each new detection and all known landmarks. A detection is assigned to the nearest landmark below a tunable threshold, or initialized as a new landmark if it is sufficiently far from all existing ones.

---

## License

MIT License — Copyright (c) 2024 Kyaw Linn Khant
