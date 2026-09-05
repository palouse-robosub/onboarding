#include "onboarding_msgs/msg/adrian_message.hpp"
#include "onboarding_msgs/srv/echo_string.hpp"
#include "rclcpp/rclcpp.hpp"

class AdrianSubscriber : public rclcpp::Node {
  private:
    rclcpp::Subscription<onboarding_msgs::msg::AdrianMessage>::SharedPtr
                                                                subscription_;
    rclcpp::Client<onboarding_msgs::srv::EchoString>::SharedPtr client_;

  public:
    AdrianSubscriber() : Node("AdrianSubscriber") {
        auto topic_callback =
            [this](onboarding_msgs::msg::AdrianMessage::UniquePtr msg) -> void {

            auto request =
                std::make_shared<onboarding_msgs::srv::EchoString::Request>();
            request->data = msg->name + ": " + std::to_string(msg->amount);

            client_->async_send_request(request);
        };
        subscription_ =
            create_subscription<onboarding_msgs::msg::AdrianMessage>(
                "adrian_topic", 10, topic_callback
            );
        client_ =
            create_client<onboarding_msgs::srv::EchoString>("echo_string");
    }
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AdrianSubscriber>());
    rclcpp::shutdown();
    return 0;
}
