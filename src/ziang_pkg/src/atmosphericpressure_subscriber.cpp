#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/fluid_pressure.hpp"


class AtmosphericPressureSubscriber : public rclcpp::Node {
  public:
    AtmosphericPressureSubscriber() : Node("AtmosphericPressure_Subscriber") {
        auto topic_callback =
            [this](sensor_msgs::msg::FluidPressure::UniquePtr msg) -> void {
            RCLCPP_INFO(
                this->get_logger(),
                "Ziang: current atmospheric pressure is %f pascals at Pullman Regional Airport",
                msg->fluid_pressure
            );
        };
        subscription_ =
            this->create_subscription<sensor_msgs::msg::FluidPressure>(
                "topic", 10, topic_callback
            );
    }

  private:
    rclcpp::Subscription<sensor_msgs::msg::FluidPressure>::SharedPtr subscription_;
};



int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AtmosphericPressureSubscriber>());
    rclcpp::shutdown();
    return 0;
}
