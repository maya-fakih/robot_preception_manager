#include "rclcpp/rclcpp.hpp"
#include "costum_interfaces/msg/detection.hpp"
#include "costum_interfaces/srv/set_confidence_threshold.hpp"

class PerceptionManager: public rclcpp::Node
{
    public:
        PerceptionManager(): Node("perception_manager")
        {
            declare_parameter<float>("confidence_threshold", 0.5f);

            // detections publisher
            // no need for wall timer here since it only fires when an action is running or is cancelled
            detections_pub_ = create_publisher<costum_interfaces::msg::Detection>("detections", 10);
            //set confidence service
            service_ = create_service<costum_interfaces::srv::SetConfidenceThreshold>(
                "set_confidence",
                std::bind(&PerceptionManager::handle_set_confidence, this,
                    std::placeholders::_1, std::placeholders::_2));
            //action server start_detection (handle goal/cancel/accepted)
        }

    private:
        //handle goal
        //handle cancel
        //handle accepted
        //handle_set_confidence
        //excute (main loop for action that we will bind the thread to)


        //publisher for Detection msgs
        rclcpp::Publisher<costum_interfaces::msg::Detection>::SharedPtr detections_pub_;
        //service server for SetConfidenceThreshold
        rclcpp::Service<costum_interfaces::srv::SetConfidenceThreshold>::SharedPtr service_;
        // action server for StartDetection
        // can add var for current goal track for bonus :D

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto perception_manager = std::make_shared<PerceptionManager>();
    rclcpp::spin(perception_manager);
    rclcpp::shutdown();
    return (0);
}