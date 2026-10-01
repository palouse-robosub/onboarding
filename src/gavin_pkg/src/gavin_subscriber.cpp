// includes
#include <memory>

#include "onboarding_msgs/srv/echo_string.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

class GavinSubscriber : public rclcpp::Node {
  public:
    GavinSubscriber() : Node("gavin_subscriber") {
        this->client_ = this->create_client<onboarding_msgs::srv::EchoString>(
            "echo_string"
        );
        auto topic_callback =
            [this](std_msgs::msg::Bool::UniquePtr msg) -> void {
            auto request =
                std::make_shared<onboarding_msgs::srv::EchoString::Request>();
            if (msg->data)
                request->data = "Gavin thinks this is true";
            else
                request->data = "Gavin thinks this is false";
            client_->async_send_request(request);
        };
        this->subscription_ = this->create_subscription<std_msgs::msg::Bool>(
            "gavin_topic", 10, topic_callback
        );
    }

  private:
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr        subscription_;
    rclcpp::Client<onboarding_msgs::srv::EchoString>::SharedPtr client_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GavinSubscriber>());
    rclcpp::shutdown();
    return 0;
}
