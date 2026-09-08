#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "onboarding_msgs/msg/ben_message.hpp"
#include "onboarding_msgs/srv/echo_string.hpp"

class BenSubscriber : public rclcpp::Node
{
public:
  rclcpp::Subscription<onboarding_msgs::msg::BenMessage>::SharedPtr subscription_;
  BenSubscriber()
  : Node("ben_subscriber")
  {
    auto topic_callback =
      [this](onboarding_msgs::msg::BenMessage::UniquePtr msg) -> void {
        // making a node to create a client in?
        std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("ben_echo_string_client");

        // creating a service client within the node that was just created, which we call "echo_string"
        rclcpp::Client<onboarding_msgs::srv::EchoString>::SharedPtr client =
            node->create_client<onboarding_msgs::srv::EchoString>("echo_string");
        
        // Next, create a request
        auto message = std::make_shared<onboarding_msgs::srv::EchoString::Request>();
        message->data = "(Ben) What is in message: " + std::to_string(msg->data);

        // Next, send the request
        auto result = client->async_send_request(message);

        // Finally, await the result
        rclcpp::spin_until_future_complete(node, result);
      };
    subscription_ =
      this->create_subscription<onboarding_msgs::msg::BenMessage>("ben_topic", 10, topic_callback);
  }

private:
  
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BenSubscriber>());
  rclcpp::shutdown();
  return 0;
}