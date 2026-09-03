// includes

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/temperature.hpp"

class TemperatureSubscriber : public rclcpp::Node {
  public:
    TemperatureSubscriber() : Node("temperature_subscriber") {
        auto topic_callback =
            [this](sensor_msgs::msg::Temperature::UniquePtr msg) -> void {
            RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg->temperature);
        };
        subscription = this->create_subscription<sensor_msgs::msg::Temperature>(
            "temperature", 10, topic_callback
        );

        // constructor
    };

  private:
    rclcpp::Subscription<sensor_msgs::msg::Temperature>::SharedPtr subscription;
};

int main(int argc, char* argv[]) {
    // setup and spin
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TemperatureSubscriber>());
    rclcpp::shutdown();
    return 0;
};
