#include <memory>

#include "onboarding_msgs/msg/ben_message.hpp"
#include "onboarding_msgs/srv/echo_string.hpp"
#include "rclcpp/rclcpp.hpp"

class BenSubscriber : public rclcpp::Node {
  public:
    rclcpp::Subscription<onboarding_msgs::msg::BenMessage>::SharedPtr
        subscription_;

    BenSubscriber() : Node("ben_subscriber") {
        // creating a service client within the subscriber node which we call
        // "echo_string"
        client = this->create_client<onboarding_msgs::srv::EchoString>(
            "echo_string"
        );

        auto topic_callback =
            [this](onboarding_msgs::msg::BenMessage::UniquePtr msg) -> void {
            // Next, create a request
            auto message =
                std::make_shared<onboarding_msgs::srv::EchoString::Request>();
            message->data =
                "Ben's uint32 is counting up: " + std::to_string(msg->data);

            // Next, send the request
            auto result = client->async_send_request(message);

            // Finally, await the result
            // rclcpp::spin_until_future_complete(this->shared_from_this(),
            // result);
        };
        subscription_ =
            this->create_subscription<onboarding_msgs::msg::BenMessage>(
                "ben_topic", 10, topic_callback
            );
    }

  private:
    rclcpp::Client<onboarding_msgs::srv::EchoString>::SharedPtr client;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BenSubscriber>());
    rclcpp::shutdown();
    return 0;
}
