# robot_preception_manager

ROS 2 Jazzy assignment: perception manager with a detection action, a runtime
confidence-threshold service, and a static camera TF broadcaster.

## Architecture

```
                        /robot1
                    +---------------------------------------------+
                    |                                              |
                    |  camera_tf_broadcaster                       |
                    |    publishes static TF once at startup       |
                    |    base_link -> camera_optical_frame         |
                    |                                              |
                    |  perception_manager                          |
                    |    action server : /start_detection          |
                    |    service server: /set_confidence            |
                    |    publisher     : /detections   (~10 Hz)    |
                    |    parameter     : confidence_threshold      |
                    |                                              |
                    +---------------------------------------------+
                              ^                    |
                     /set_confidence        /detections, feedback
                              |                    v
                       [ action/service clients, ros2 topic echo ]
```

## Packages

- `custom_interfaces` — Detection.msg, SetConfidenceThreshold.srv, StartDetection.action
- `perception_manager` — perception_manager_node, camera_tf_broadcaster, launch, config

## Build

```bash
source /opt/ros/jazzy/setup.bash
colcon build --symlink-install
source install/setup.bash
```

## Run

```bash
ros2 launch perception_manager perception_manager.launch.py namespace:=robot1
```

## Exercise it (separate terminals, each sourced with setup.bash / setup.zsh)

Send a goal and watch feedback:
```bash
ros2 action send_goal /robot1/start_detection custom_interfaces/action/StartDetection "{target_class: 'person'}" --feedback
```

Change the threshold mid-run:
```bash
ros2 service call /robot1/set_confidence custom_interfaces/srv/SetConfidenceThreshold "{threshold: 0.8}"
```

Cancel the running goal — `ros2 action cancel` does not exist as a CLI subcommand
in ROS 2, and Ctrl+C on `send_goal --feedback` can hit a known `Executor is
already spinning` bug that silently drops the cancel. Call the action server's
auto-generated cancel service directly instead:
```bash
ros2 service call /robot1/start_detection/_action/cancel_goal action_msgs/srv/CancelGoal "{goal_info: {goal_id: {uuid: [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]}, stamp: {sec: 0, nanosec: 0}}}"
```
An all-zero `goal_id` cancels every currently active goal.

Check the TF tree:
```bash
ros2 run tf2_tools view_frames
```

## Notes / things I got stuck on

- `Detection.msg` was missing `builtin_interfaces/Time stamp` from the original spec;
  added it plus the `builtin_interfaces` dependency in `custom_interfaces`'s
  `CMakeLists.txt` and `package.xml`.
- Renamed the interfaces package from `costum_interfaces` to `custom_interfaces`
  partway through — an old build of a differently-named `costum_interfaces` package
  in a general `~/ros2_ws` underlay was shadowing this repo's interfaces and causing
  `has no member named 'stamp'` errors even after the field was added. Renaming
  removed the naming collision entirely; the underlying fix was still adding the
  missing field.
- `ros2 action send_goal --feedback` does not reliably cancel on Ctrl+C — it can
  print `Executor is already spinning` and never actually send the cancel. The
  reliable way to cancel is calling the action server's built-in
  `<action_name>/_action/cancel_goal` service directly (see above).
- Random detection values use `rand()`/`srand()` rather than `<random>`'s
  engine+distribution API — simpler, and sufficient since nothing here depends on
  high-quality randomness.
- Not implementing goal preemption (a second goal replacing a running one); only
  explicit cancellation is supported.