#include <functional>
#include <memory>
#include <string>

#include "onboarding_msgs/srv/echo_string.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

class EstefaniaSubscriber : public rclcpp::Node {
  public:
    EstefaniaSubscriber() : Node("estefania_subscriber") {
        subscription_ = this->create_subscription<std_msgs::msg::Float32>(
            "estefania_topic", 10,
            std::bind(
                &EstefaniaSubscriber::topic_callback, this,
                std::placeholders::_1
            )
        );

        client_ = this->create_client<onboarding_msgs::srv::EchoString>(
            "echo_string"
        );
    }

  private:
    void topic_callback(const std_msgs::msg::Float32::SharedPtr message) {
        std::string summary =
            "Estefania received the value: " + std::to_string(message->data);

        if (!client_->wait_for_service(std::chrono::seconds(1))) {
            RCLCPP_WARN(this->get_logger(), "Echo service is not available.");
            return;
        }

        auto request =
            std::make_shared<onboarding_msgs::srv::EchoString::Request>();

        request->data = summary;

        client_->async_send_request(request);
    }

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_;

    rclcpp::Client<onboarding_msgs::srv::EchoString>::SharedPtr client_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<EstefaniaSubscriber>());

    rclcpp::shutdown();

    return 0;
}
