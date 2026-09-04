#include <memory>

#include "onboarding_msgs/msg/oliver_double.hpp"
#include "onboarding_msgs/srv/echo_string.hpp"
#include "rclcpp/rclcpp.hpp"

class OliverSubscriber : public rclcpp::Node {
  public:
    OliverSubscriber() : Node("oliver_subscriber") {
        std::shared_ptr<rclcpp::Node> node =
            rclcpp::Node::make_shared("oliver_onboarding_echo_client");
        rclcpp::Client<onboarding_msgs::srv::EchoString>::SharedPtr client =
            node->create_client<onboarding_msgs::srv::EchoString>(
                "echo_string"
            );
        auto topic_callback =
            [this, client](
                onboarding_msgs::msg::OliverDouble::UniquePtr msg
            ) -> void {
            auto echo_string =
                std::make_shared<onboarding_msgs::srv::EchoString::Request>();
            std::stringstream output{};
            output << "Oliver's doubles are diverging: "
                   << msg->my_glorious_double << " "
                   << msg->my_second_glorious_double;
            echo_string->data = output.str();
            client->async_send_request(echo_string);
        };
        subscription_ =
            this->create_subscription<onboarding_msgs::msg::OliverDouble>(
                "oliver_topic", 10, topic_callback
            );
    }

  private:
    rclcpp::Subscription<onboarding_msgs::msg::OliverDouble>::SharedPtr
        subscription_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OliverSubscriber>());
    rclcpp::shutdown();
    return 0;
}
