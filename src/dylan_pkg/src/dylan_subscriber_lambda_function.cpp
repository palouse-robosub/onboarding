#include <memory>

#include "onboarding_msgs/srv/echo_string.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

class MinimalSubscriber : public rclcpp::Node {
  public:
    MinimalSubscriber() : Node("minimal_subscriber") {
        client_ = this->create_client<onboarding_msgs::srv::EchoString>(
            "/echo_string"
        );

        auto topic_callback =
            [this](std_msgs::msg::Float32::UniquePtr msg) -> void {
            RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg->data);
            std::string summary =
                "Dylan received a float: " + std::to_string(msg->data);
            auto request =
                std::make_shared<onboarding_msgs::srv::EchoString::Request>();
            request->data = summary;
            if (!client_->wait_for_service(std::chrono::seconds(1))) {
                RCLCPP_WARN(
                    this->get_logger(), "/echo_string service not available"
                );
                return;
            }
            client_->async_send_request(request);
        };
        subscription_ = this->create_subscription<std_msgs::msg::Float32>(
            "topic", 10, topic_callback
        );
    }

  private:
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr     subscription_;
    rclcpp::Client<onboarding_msgs::srv::EchoString>::SharedPtr client_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalSubscriber>());
    rclcpp::shutdown();
    return 0;
}
