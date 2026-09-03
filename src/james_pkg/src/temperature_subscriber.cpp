// includes

#include "onboarding_msgs/srv/echo_string.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/temperature.hpp"

class TemperatureSubscriber : public rclcpp::Node {
  public:
    TemperatureSubscriber() : Node("temperature_subscriber") {
        auto topic_callback =
            [this](sensor_msgs::msg::Temperature::UniquePtr msg) -> void {
            auto request =
                std::make_shared<onboarding_msgs::srv::EchoString::Request>();
            request->data = "james figures " + std::to_string(msg->temperature)
                          + " degrees isn't too hot";
            client->async_send_request(request);
        };
        subscription = this->create_subscription<sensor_msgs::msg::Temperature>(
            "temperature", 10, topic_callback
        );
        client = this->create_client<onboarding_msgs::srv::EchoString>(
            "echo_string"
        );
        // constructor
    };

  private:
    rclcpp::Subscription<sensor_msgs::msg::Temperature>::SharedPtr subscription;
    rclcpp::Client<onboarding_msgs::srv::EchoString>::SharedPtr    client;
};

int main(int argc, char* argv[]) {
    // setup and spin
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TemperatureSubscriber>());
    rclcpp::shutdown();
    return 0;
};
