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
        broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
        // read params into local vars
        double tx, ty, tz, roll, pitch, yaw;
        get_parameter("tx", tx);
        get_parameter("ty", ty);
        get_parameter("tz", tz);
        get_parameter("roll", roll);
        get_parameter("pitch", pitch);
        get_parameter("yaw", yaw);
        // build transform stamped msg
        geometry_msgs::msg::TransformStamped transform;
        transform.header.stamp = now();
        transform.header.frame_id = "base_link";
        transform.child_frame_id = "camera_optical_frame";
        transform.transform.translation.x = tx;
        transform.transform.translation.y = ty;
        transform.transform.translation.z = tz;
        // convert roll pitch yaw to a quanternion
        // broadcast transform
    }

private:
    // broadcaster_
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> broadcaster_;
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CameraTfBroadcaster>());
    rclcpp::shutdown();
    return 0;
}