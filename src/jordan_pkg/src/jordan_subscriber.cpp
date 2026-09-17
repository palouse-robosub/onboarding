// includes
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/color_rgba.hpp"

class JordanSubscriber : public rclcpp::Node {
  public:
    JordanSubscriber() : Node("jordan_subscriber") {
        // constructor
        subscription_ = this->create_subscription<std_msgs::msg::ColorRGBA>(
            "led_color_topic", 10,
            std::bind(
                &JordanSubscriber::topic_callback, this, std::placeholders::_1
            )
        );
    }

  private:
    // runs automatically when new message arrives on topic
    void topic_callback(const std_msgs::msg::ColorRGBA::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "Heard Red Value: '%f'", msg->r);
    }

    rclcpp::Subscription<std_msgs::msg::ColorRGBA>::SharedPtr subscription_;
};

int main(int argc, char* argv[]) {
    // setup and spin
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JordanSubscriber>());
    rclcpp::shutdown();
    return 0;
}
