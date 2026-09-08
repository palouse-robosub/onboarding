#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "onboarding_msgs/msg/ben_message.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses a fancy C++11 lambda
* function to shorten the callback syntax, at the expense of making the
* code somewhat more difficult to understand at first glance. */

class BenPublisher : public rclcpp::Node
{
public:
size_t count_;
  BenPublisher()
  : Node("ben_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<onboarding_msgs::msg::BenMessage>("ben_topic", 10);
    auto timer_callback =
      [this]() -> void {
        auto message = onboarding_msgs::msg::BenMessage();
        message.data = count_++;
        this->publisher_->publish(message);
      };
    // publishes every 0.5hz (equivalent to 2000ms)
    timer_ = this->create_wall_timer(2000ms, timer_callback);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<onboarding_msgs::msg::BenMessage>::SharedPtr publisher_;
  
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BenPublisher>());
  rclcpp::shutdown();
  return 0;
}