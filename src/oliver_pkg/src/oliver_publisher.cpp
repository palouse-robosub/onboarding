#include <chrono>
#include <memory>
#include <string>

#include "onboarding_msgs/msg/oliver_double.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses a fancy C++11 lambda
 * function to shorten the callback syntax, at the expense of making the
 * code somewhat more difficult to understand at first glance. */

class OliverPublisher : public rclcpp::Node {
  public:
    OliverPublisher() : Node("oliver_publisher"), count_(0) {
        publisher_ = this->create_publisher<onboarding_msgs::msg::OliverDouble>(
            "oliver_topic", 10
        );
        auto timer_callback = [this]() -> void {
            auto message = onboarding_msgs::msg::OliverDouble();

            message.my_glorious_double        = std::pow(2, count_);
            message.my_second_glorious_double = std::pow(2, -count_);
            count_++;

            this->publisher_->publish(message);
        };
        timer_ = this->create_wall_timer(2000ms, timer_callback);
    }

  private:
    rclcpp::TimerBase::SharedPtr                                     timer_;
    rclcpp::Publisher<onboarding_msgs::msg::OliverDouble>::SharedPtr publisher_;
    double                                                           count_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OliverPublisher>());
    rclcpp::shutdown();
    return 0;
}
