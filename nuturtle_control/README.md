# nuturtle_control

This package handles low-level robot control and odometry for the NuTurtle. It bridges high-level velocity commands (geometry_msgs/Twist) to wheel-level hardware commands, reads encoder feedback, and computes a dead-reckoning pose estimate (the blue robot).

---

## Nodes

### `turtle_control`

Translates body-frame velocity commands into wheel motor commands, and converts raw encoder ticks back into joint states.

**Parameters**

| Parameter | Type | Description |
|-----------|------|-------------|
| `wheel_radius` | `double` | Wheel radius (m) |
| `track_width` | `double` | Distance between wheels (m) |
| `motor_cmd_max` | `double` | Maximum motor command (tick velocity) |
| `motor_cmd_per_rad_sec` | `double` | Conversion: motor cmd units per rad/s |
| `encoder_ticks_per_rad` | `double` | Conversion: encoder ticks per radian |
| `collision_radius` | `double` | Robot collision radius (m) |

**Published Topics**

| Topic | Type | Description |
|-------|------|-------------|
| `/wheel_cmd` | `nuturtlebot_msgs/WheelCommands` | Motor commands sent to hardware |
| `/joint_states` | `sensor_msgs/JointState` | Wheel joint positions from encoder data |

**Subscribed Topics**

| Topic | Type | Description |
|-------|------|-------------|
| `/cmd_vel` | `geometry_msgs/Twist` | Commanded body velocity |
| `/sensor_data` | `nuturtlebot_msgs/SensorData` | Raw wheel encoder ticks |

---

### `odometry`

Integrates wheel joint states using differential drive kinematics to produce a dead-reckoning odometry estimate. Publishes the blue robot's path and broadcasts the `odom → blue/base_footprint` TF.

**Parameters**

| Parameter | Type | Description |
|-----------|------|-------------|
| `body_id` | `string` | Body frame name (e.g. `blue/base_footprint`) |
| `odom_id` | `string` | Odometry frame name (e.g. `odom`) |
| `wheel_left` | `string` | Left wheel joint name |
| `wheel_right` | `string` | Right wheel joint name |
| `wheel_radius` | `double` | Wheel radius (m) |
| `track_width` | `double` | Track width (m) |

**Published Topics**

| Topic | Type | Description |
|-------|------|-------------|
| `/odom` | `nav_msgs/Odometry` | Dead-reckoning odometry (blue robot) |
| `/blue/path` | `nav_msgs/Path` | Odometry trajectory for RViz |

**Subscribed Topics**

| Topic | Type | Description |
|-------|------|-------------|
| `/joint_states` | `sensor_msgs/JointState` | Wheel joint positions |

**Services**

| Service | Type | Description |
|---------|------|-------------|
| `/initial_pose` | `nuturtle_control/InitialPose` | Reset odometry to a given pose |

---

### `circle`

Publishes a constant circular velocity command so the robot drives in a circle with a configurable radius and speed. Useful for open-loop trajectory testing.

**Parameters**

| Parameter | Type | Description |
|-----------|------|-------------|
| `frequency` | `int` | Command publish rate (Hz) |

**Published Topics**

| Topic | Type | Description |
|-------|------|-------------|
| `/cmd_vel` | `geometry_msgs/Twist` | Circular motion command |

**Services**

| Service | Type | Description |
|---------|------|-------------|
| `/control` | `nuturtle_control/Control` | Set circle radius and angular velocity |
| `/reverse` | `std_srvs/Empty` | Reverse direction of motion |
| `/stop` | `std_srvs/Empty` | Stop publishing and halt the robot |

---

## Launch Files

### `start_robot.launch.xml`

Launches the full robot stack: simulator, controller, and odometry.

```bash
ros2 launch nuturtle_control start_robot.launch.xml
```

### `start_controller.launch.xml`

Launches only `turtle_control` (without odometry). Used when another node handles joint states.

```bash
ros2 launch nuturtle_control start_controller.launch.xml
```

### `start_odometry.launch.xml`

Launches only the `odometry` node with TF broadcasting.

```bash
ros2 launch nuturtle_control start_odometry.launch.xml
```

### `start_circle.launch.xml`

Launches the `circle` node for open-loop circular trajectory testing.

```bash
ros2 launch nuturtle_control start_circle.launch.xml
```

---

## Custom Service Definitions

### `Control.srv`
```
float64 velocity    # Angular velocity (rad/s)
float64 radius      # Circle radius (m)
---
# (empty response)
```

### `InitialPose.srv`
```
float64 x       # X position (m)
float64 y       # Y position (m)
float64 theta   # Heading (rad)
---
# (empty response)
```

---

## License

MIT License — Copyright (c) 2024 Kyaw Linn Khant
