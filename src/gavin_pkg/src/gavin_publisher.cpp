// includes
#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

using namespace std::chrono_literals;

class GavinPublisher : public rclcpp::Node {
  public:
    GavinPublisher()
      // constructor
      : Node("gavin_publisher"), count_(0) {
        publisher_ =
            this->create_publisher<std_msgs::msg::Bool>("gavin_topic", 10);
        auto timer_callback = [this]() -> void {
            auto message = std_msgs::msg::Bool();
            message.data = (bool)(count_++ % 2);

            this->publisher_->publish(message);
        };
        timer_ = this->create_wall_timer(2000ms, timer_callback);
    }

  private:
    rclcpp::TimerBase::SharedPtr                      timer_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher_;
    size_t                                            count_;
};

int main(int argc, char* argv[]) {
    // setup and spin
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GavinPublisher>());
    rclcpp::shutdown();
    return 0;
}
