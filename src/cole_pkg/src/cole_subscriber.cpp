#include <memory>
#include <sstream>

#include "onboarding_msgs/srv/echo_string.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/nav_sat_fix.hpp"

class ColeSubscriber : public rclcpp::Node {
  public:
    ColeSubscriber() : Node("cole_subscriber") {
        client_ = this->create_client<onboarding_msgs::srv::EchoString>(
            "echo_string"
        );

        auto topic_callback =
            [this](sensor_msgs::msg::NavSatFix::UniquePtr msg) -> void {
            std::ostringstream out;
            out.precision(3);
            out << "Cole is (likely) currently at: (";
            out << std::fixed << msg->latitude << ", ";
            out << std::fixed << msg->longitude << ")";

            auto request =
                std::make_shared<onboarding_msgs::srv::EchoString::Request>();
            request->data = std::move(out).str();
            client_->async_send_request(request);
        };
        subscription_ = this->create_subscription<sensor_msgs::msg::NavSatFix>(
            "cole_topic", 10, topic_callback
        );
    }

  private:
    rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr subscription_;
    rclcpp::Client<onboarding_msgs::srv::EchoString>::SharedPtr  client_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ColeSubscriber>());
    rclcpp::shutdown();
    return 0;
}
