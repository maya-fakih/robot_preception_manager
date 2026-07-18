#include "rclcpp/rclcpp.hpp"
#include "costum_interfaces/msg/detection.hpp"
#include "costum_interfaces/srv/set_confidence_threshold.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "costum_interfaces/action/start_detection.hpp"
#include <thread>
using std::placeholders::_1;
using std::placeholders::_2;

class PerceptionManager: public rclcpp::Node
{
    public:
        using StartDetection = costum_interfaces::action::StartDetection;
        using GoalHandleStartDetection = rclcpp_action::ServerGoalHandle<StartDetection>;
 
        PerceptionManager(): Node("perception_manager")
        {
            declare_parameter<float>("confidence_threshold", 0.5f);

            // detections publisher
            // no need for wall timer here since it only fires when an action is running or is cancelled
            detections_pub_ = create_publisher<costum_interfaces::msg::Detection>("detections", 10);
            //set confidence service
            service_ = create_service<costum_interfaces::srv::SetConfidenceThreshold>(
                "set_confidence",
                std::bind(&PerceptionManager::handle_set_confidence, this, _1, _2));
            //action server start_detection (handle goal/cancel/accepted)
            action_server_ = rclcpp_action::create_server<StartDetection>(
                this,
                "start_detection",
                std::bind(&PerceptionManager::handle_goal, this, _1, _2),
                std::bind(&PerceptionManager::handle_cancel, this, _1),
                std::bind(&PerceptionManager::handle_accepted, this, _1)
            );

        }

    private:
        //handle goal
        rclcpp_action::GoalResponse handle_goal(
            const rclcpp_action::GoalUUID &,
            std::shared_ptr<const StartDetection::Goal>)
        {
            return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
        }
  
        //handle cancel
        rclcpp_action::CancelResponse handle_cancel(
            const std::shared_ptr<GoalHandleStartDetection>)
        {
            return rclcpp_action::CancelResponse::ACCEPT;
        }

        //handle accepted
        void handle_accepted(const std::shared_ptr<GoalHandleStartDetection> goal_handle)
        {
        std::thread(&PerceptionManager::execute, this, goal_handle).detach();
        }

        //handle_set_confidence
        void handle_set_confidence(
            const std::shared_ptr<costum_interfaces::srv::SetConfidenceThreshold::Request> request,
            std::shared_ptr<costum_interfaces::srv::SetConfidenceThreshold::Response>  response)
        {
            if (request->threshold <0.0f || request->threshold > 1.0f)
            {
                response->success = false;
                response->message = "Threshold must be within [0.0, 1.0]";
                return;
            }
            set_parameter(rclcpp::Parameter("confidence_threshold", request->threshold));
            response->success = true;
            response->message = "confidence_threshold updates successfully!";
        }
        //excute (main loop for action that we will bind the thread to)


        //publisher for Detection msgs
        rclcpp::Publisher<costum_interfaces::msg::Detection>::SharedPtr detections_pub_;
        //service server for SetConfidenceThreshold
        rclcpp::Service<costum_interfaces::srv::SetConfidenceThreshold>::SharedPtr service_;
        // action server for StartDetection
        rclcpp_action::Server<StartDetection>::SharedPtr action_server_;
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