#include "rclcpp/rclcpp.hpp"

class PerceptionManager: public rclcpp::Node
{
    public:
        PerceptionManager(): Node("perception_manager")
        {
            declare_parameter<float>("confidence_threshold", 0.5f);
            // detections publisher
            //set confidence service
            //action server start_detection (handle goal/cancel/accepted)
            
        }

    private:
        //handle goal
        //handle cancel
        //handle accepted
        //handle_set_confidence
        //excute (main loop for action that we will bind the thread to)


        //publisher for Detection msgs
        //service server for SetConfidenceThreshold
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