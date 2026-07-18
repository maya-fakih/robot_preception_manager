#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"

class CameraTfBroadcaster : public rclcpp::Node
{
public:
    CameraTfBroadcaster() : Node("camera_tf_broadcaster")
    {
        //declare params
        // create static broadcaster
        // read params into local vars
        // build transform stamped msg
        // convert roll pitch yaw to a quanternion
        // broadcast transform
    }

private:
    // broadcaster_
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CameraTfBroadcaster>());
    rclcpp::shutdown();
    return 0;
}