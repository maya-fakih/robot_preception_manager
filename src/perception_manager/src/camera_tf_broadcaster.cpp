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
        declare_parameter<double>("tx", 0.0);
        declare_parameter<double>("ty", 0.0);
        declare_parameter<double>("tz", 0.0);
        declare_parameter<double>("roll", 0.0);
        declare_parameter<double>("pitch", 0.0);
        declare_parameter<double>("yaw", 0.0);
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