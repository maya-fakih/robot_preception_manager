# HOW TO ROS2
this file serves the sole purpose of telling you how to step by step build any ros2 project when needed 
it will not be the clearest at the start will work on a nicer polish once i have everything done.

for now i will add the needed examples to run things as a reference

cmake_minimum_required(VERSION 3.8)
project(costum_interfaces)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# only add the lines below if you actually used that type inside a .msg/.srv/.action field

find_package(std_msgs REQUIRED)        # Header, Bool, String, basic primitives wrapper
find_package(geometry_msgs REQUIRED)   # Point, Pose, Vector3, Twist, Transform
find_package(builtin_interfaces REQUIRED)  # Time, Duration (usually auto-pulled by actions, rarely needed manually)
find_package(sensor_msgs REQUIRED)     # Image, CameraInfo, PointCloud2, LaserScan (camera/sensor data)
find_package(std_srvs REQUIRED)        # only if you reuse std_srvs types instead of your own srv
find_package(action_msgs REQUIRED)     # GoalStatus (usually auto-pulled if you have any .action, rarely needed manually)
find_package(tf2_msgs REQUIRED)        # TFMessage, if a field literally carries a TF message type
find_package(nav_msgs REQUIRED)        # Odometry, Path, OccupancyGrid (robot navigation data)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Detection.msg"
  "srv/SetConfidenceThreshold.srv"
  "action/StartDetection.action"
  DEPENDENCIES std_msgs geometry_msgs sensor_msgs
  # ^ list only the packages you actually kept find_package lines for above
)

ament_package()