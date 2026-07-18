#include "rclcpp/rclcpp.hpp"

class PerceptionManager: public rclcpp::Node
{
    public:
        PerceptionManager(): Node("perception_manager")
        {
            
        }

    private:

};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto perception_manager = std::make_shared<PerceptionManager>();
    rclcpp::spin(perception_manager);
    rclcpp::shutdown();
    return (0);
}