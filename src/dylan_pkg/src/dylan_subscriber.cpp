#include <memory>

#include "onboarding_msgs/srv/echo_string.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

class DylanSubscriber : public rclcpp::Node {
  public:
    DylanSubscriber() : Node("dylan_subscriber") {
        client_ = this->create_client<onboarding_msgs::srv::EchoString>(
            "/echo_string"
        );

        auto topic_callback =
            [this](std_msgs::msg::Float32::UniquePtr msg) -> void {
            auto request =
                std::make_shared<onboarding_msgs::srv::EchoString::Request>();
            if (!client_->wait_for_service(std::chrono::seconds(1))) {
                RCLCPP_WARN(
                    this->get_logger(), "/echo_string service not available"
                );
                return;
            }
            client_->async_send_request(request);
        };
        subscription_ = this->create_subscription<std_msgs::msg::Float32>(
            "dylan_topic", 10, topic_callback
        );
    }

  private:
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr     subscription_;
    rclcpp::Client<onboarding_msgs::srv::EchoString>::SharedPtr client_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DylanSubscriber>());
    rclcpp::shutdown();
    return 0;
}
