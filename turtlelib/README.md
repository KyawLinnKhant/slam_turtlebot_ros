# turtlelib

A standalone C++ library providing mathematical primitives for 2D robot kinematics, rigid body transformations, and EKF SLAM. This library has no ROS dependencies and can be built independently with CMake.

---

## Components

| Module | File | Description |
|--------|------|-------------|
| `geometry2d` | `geometry2d.hpp/.cpp` | 2D points, vectors, angles, and normalization utilities |
| `se2d` | `se2d.hpp/.cpp` | SE(2) rigid body transforms — rotation + translation in 2D |
| `diff_drive` | `diff_drive.hpp/.cpp` | Forward and inverse kinematics for a differential drive robot |
| `ekf` | `ekf.hpp/.cpp` | Extended Kalman Filter for SLAM (predict + correct) |
| `circle_fitting` | `circle_fitting.hpp/.cpp` | Taubin algebraic circle fitting for landmark detection |
| `svg` | `svg.hpp/.cpp` | SVG drawing utilities for visualizing frames and transforms |
| `frame_main` | `src/frame_main.cpp` | CLI tool: computes frame compositions from standard input |

---

## Building

```bash
# From the turtlelib directory
mkdir build && cd build
cmake ..
make
```

To generate Doxygen documentation:
```bash
make doxygen
# Output in build/html/index.html
```

---

## Usage

### SE(2) Transforms

```cpp
#include "turtlelib/se2d.hpp"

// Create a transform: rotate 90 degrees, translate (1, 2)
turtlelib::Transform2D T{turtlelib::Vector2D{1.0, 2.0}, turtlelib::PI / 2.0};

// Compose two transforms
turtlelib::Transform2D T2{ turtlelib::Vector2D{0.5, 0.0} };
turtlelib::Transform2D T_composed = T * T2;

// Invert a transform
turtlelib::Transform2D T_inv = T.inv();
```

### Differential Drive Kinematics

```cpp
#include "turtlelib/diff_drive.hpp"

// Create robot with wheel_radius=0.033m, track_width=0.16m
turtlelib::DiffDrive robot{0.033, 0.16};

// Forward kinematics: wheel angle deltas -> body twist -> updated pose
turtlelib::wheelAngles delta{0.1, 0.2};       // left and right wheel rotation (rad)
turtlelib::Twist2D body_twist = robot.driveWheels(delta);

// Inverse kinematics: body twist -> required wheel velocities
turtlelib::Twist2D cmd{0.1, 0.5, 0.0};        // omega, vx, vy
turtlelib::wheelAngles wheels = robot.TwistToWheels(cmd);
```

### EKF SLAM

```cpp
#include "turtlelib/ekf.hpp"

turtlelib::EKFSlam ekf;

// Prediction step — called every time a new odometry twist arrives
turtlelib::Twist2D motion{0.05, 0.1, 0.0};
ekf.predict(motion);

// Correction step — called for each detected landmark
// x, y are relative landmark position; j is the landmark index
ekf.correct(0.3, 0.1, 1);

// Retrieve current pose estimate
turtlelib::Pose2D pose = ekf.pose();
```

---

## Design Decisions

### Why `normalize()` is a free function

`normalize(v)` is implemented as a free function rather than a member function or operator overload. Normalization produces a new value — it does not logically belong to the vector itself, and silently mutating `x`/`y` in place would be surprising to callers. A free function makes the intent explicit and keeps `Vector2D` a simple data carrier.

```cpp
// Returns a new unit vector; v is unchanged
Vector2D unit = normalize(v);
```

---

### Why `Vector2D` is a `struct` and `Transform2D` is a `class`

`Vector2D` is a plain data carrier: its `x` and `y` fields are fully independent and can be set freely. A `struct` with public members is the right fit.

`Transform2D` encapsulates a coupled rotation and translation. Allowing arbitrary direct writes to either component independently would break the invariant that the object represents a valid rigid body transform, so private members and controlled access via methods are necessary. Hence `class`.

---

### Why single-argument `Transform2D` constructors are `explicit`

Without `explicit`, a bare `double` or `Vector2D` could be silently coerced into a `Transform2D` wherever one is expected, producing hard-to-diagnose bugs. Marking them `explicit` forces callers to be intentional.

---

### Why `inv()` is `const` but `operator*=()` is not

`inv()` is a pure query — it computes and returns the mathematical inverse without touching the object's state, so `const` is correct and allows it to be called on `const` references.

`operator*=()` performs an in-place compound assignment and must mutate the object, so it cannot be `const`.

---

## License

MIT License — Copyright (c) 2024 Kyaw Linn Khant
