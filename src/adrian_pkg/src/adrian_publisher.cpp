#include <chrono>
#include <memory>
#include <string>

#include "onboarding_msgs/msg/adrian_message.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class AdrianPublisher : public rclcpp::Node {
  private:
    rclcpp::Publisher<onboarding_msgs::msg::AdrianMessage>::SharedPtr
                                 publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    uint16_t                     count_ = 0;

  public:
    AdrianPublisher() : Node("AdrianPublisher") {
        publisher_ =
            this->create_publisher<onboarding_msgs::msg::AdrianMessage>(
                "adrian-topic", 10
            );
        auto timer_callback = [this]() -> void {
            auto message   = onboarding_msgs::msg::AdrianMessage();
            message.name   = "Hello... World...";
            message.amount = count_++;

            RCLCPP_INFO(get_logger(), "Publishing: '%s'", message.name.c_str());
            publisher_->publish(message);
        };
        timer_ = create_wall_timer(500ms, timer_callback);
    }
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AdrianPublisher>());
    rclcpp::shutdown();
    return 0;
}
