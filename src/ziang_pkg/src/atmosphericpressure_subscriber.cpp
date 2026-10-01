#include "onboarding_msgs/srv/echo_string.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/fluid_pressure.hpp"
#include <memory>

class AtmosphericPressureSubscriber : public rclcpp::Node {
  public:
    AtmosphericPressureSubscriber() : Node("AtmosphericPressure_Subscriber") {
        client_ = this->create_client<onboarding_msgs::srv::EchoString>(
            "echo_string"
        );

        auto topic_callback =
            [this](sensor_msgs::msg::FluidPressure::UniquePtr msg) -> void {
            auto request =
                std::make_shared<onboarding_msgs::srv::EchoString::Request>();
            request->data = "Ziang: current atmospheric pressure is "
                          + std::to_string(msg->fluid_pressure)
                          + " pascals at Pullman Regional Airport";
            client_->async_send_request(request);
        };

        subscription_ =
            this->create_subscription<sensor_msgs::msg::FluidPressure>(
                "ziang_topic", 10, topic_callback
            );
    }

  private:
    rclcpp::Subscription<sensor_msgs::msg::FluidPressure>::SharedPtr
                                                                subscription_;
    rclcpp::Client<onboarding_msgs::srv::EchoString>::SharedPtr client_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AtmosphericPressureSubscriber>());
    rclcpp::shutdown();
    return 0;
}
