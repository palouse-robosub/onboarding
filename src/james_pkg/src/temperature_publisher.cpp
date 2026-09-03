// includes

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/temperature.hpp"
#include <chrono>

using namespace std::chrono_literals;

class TemperaturePublisher : public rclcpp::Node {
  public:
    TemperaturePublisher() : Node("temperature_publisher"), count_(0) {
        publisher_ = this->create_publisher<sensor_msgs::msg::Temperature>(
            "temperature", 10
        );
        auto timer_callback = [this]() -> void {
            auto message        = sensor_msgs::msg::Temperature();
            message.temperature = 200.0;
            RCLCPP_INFO(
                this->get_logger(), "Publishing: '%f'", message.temperature
            );
            this->publisher_->publish(message);
        };
        timer_ = this->create_wall_timer(2000ms, timer_callback);
    };

  private:
    rclcpp::TimerBase::SharedPtr                                timer_;
    rclcpp::Publisher<sensor_msgs::msg::Temperature>::SharedPtr publisher_;
    size_t                                                      count_;
};

int main(int argc, char* argv[]) {
    // setup and spin
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TemperaturePublisher>());
    rclcpp::shutdown();
    return 0;
};
