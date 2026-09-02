#include "onboarding_msgs/srv/echo_string.hpp"
#include "rclcpp/rclcpp.hpp"

class EchoService : public rclcpp::Node {
  public:
    EchoService() :
      Node("echo_service") {
        echo_service_ = this->create_service<onboarding_msgs::srv::EchoString>(
            "echo_string", std::bind(
                                &EchoService::echo_callback, this,
                                std::placeholders::_1, std::placeholders::_2
                            )
        );
    }

  private:
    rclcpp::Service<onboarding_msgs::srv::EchoString>::SharedPtr echo_service_;

    void echo_callback(
        const std::shared_ptr<onboarding_msgs::srv::EchoString::Request> request,
        std::shared_ptr<onboarding_msgs::srv::EchoString::Response> response
    ) {
      RCLCPP_INFO(
        get_logger(),
        "Echo request recieved: %s",
        request->data.c_str()
      );
    }
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);

    auto publisher_node = std::make_shared<EchoService>();

    rclcpp::spin(publisher_node);

    rclcpp::shutdown();

    return 0;
}