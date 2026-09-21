// includes
#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/color_rgba.hpp"

using namespace std::chrono_literals;

class JordanPublisher : public rclcpp::Node {
  public:
    JordanPublisher() : Node("jordan_publisher"), count_(0) {
        // Refactored bc clang-format line limit (I think)
        // publisher_ = this->create_publisher<std_msgs::msg::ColorRGBA>(
        //     "led_color_topic", 10
        // );
        using ColorMsg = std_msgs::msg::ColorRGBA;
        publisher_ = this->create_publisher<ColorMsg>("led_color_topic", 10);

        auto timer_callback = [this]() -> void {
            auto message = std_msgs::msg::ColorRGBA();

            // Cycles through red values based on count_
            message.r = static_cast<float>(this->count_ % 10) / 10.0;
            message.g = 0.0f;
            message.b = 0.0f;
            message.a = 1.0f;    // Keep alpha at 1.0
            RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.r);
            this->publisher_->publish(message);
            this->count_++;
        };
        timer_ = this->create_wall_timer(500ms, timer_callback);
    }

  private:
    rclcpp::TimerBase::SharedPtr                           timer_;
    rclcpp::Publisher<std_msgs::msg::ColorRGBA>::SharedPtr publisher_;
    size_t                                                 count_;
};

int main(int argc, char* argv[]) {
    // setup and spin
    rclcpp::init(argc, argv);

    auto publisher_node = std::make_shared<JordanPublisher>();
    rclcpp::spin(publisher_node);

    rclcpp::shutdown();
    return 0;
}
