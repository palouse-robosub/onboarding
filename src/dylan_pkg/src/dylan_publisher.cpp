#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses a fancy C++11 lambda
 * function to shorten the callback syntax, at the expense of making the
 * code somewhat more difficult to understand at first glance. */

class DylanPublisher : public rclcpp::Node {
  public:
    DylanPublisher() : Node("dylan_publisher"), count_(0) {
        publisher_ =
            this->create_publisher<std_msgs::msg::Float32>("dylan_topic", 10);
        auto timer_callback = [this]() -> void {
            auto message = std_msgs::msg::Float32();
            message.data = static_cast<float>(this->count_++);
            this->publisher_->publish(message);
        };
        timer_ = this->create_wall_timer(2000ms, timer_callback);
    }

  private:
    rclcpp::TimerBase::SharedPtr                         timer_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
    size_t                                               count_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DylanPublisher>());
    rclcpp::shutdown();
    return 0;
}
