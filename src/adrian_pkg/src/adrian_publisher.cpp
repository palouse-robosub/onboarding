#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "onboarding_msgs/msg/example.hpp"

using namespace std::chrono_literals;

class AdrianPublisher : public rclcpp::Node
{
    private:
        rclcpp::Publisher<onboarding_msgs::msg::Example>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        uint16_t count_ = 0;

    public:
        AdrianPublisher() 
        : Node("AdrianPublisher")
        {
            publisher_ = this->create_publisher<onboarding_msgs::msg::Example>("topic", 10);
            auto timer_callback = [this]() -> void 
            {
                auto message = onboarding_msgs::msg::Example();
                message.example_string = "Hello..." + std::to_string(count_);
                message.example_u16 = count_++;
                message.example_u8 = 8u;

                RCLCPP_INFO(get_logger(), "Publishing: '%s'", message.example_string.c_str());
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
