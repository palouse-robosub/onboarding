#include "rclcpp/rclcpp.hpp"
#include "onboarding_msgs/msg/adrian_message.hpp"

class AdrianSubscriber : public rclcpp::Node {
    private:
        rclcpp::Subscription<onboarding_msgs::msg::AdrianMessage>::SharedPtr subscription_;
    public:
        AdrianSubscriber() 
        : Node("AdrianSubscriber")
        {
            auto topic_callback = [this](onboarding_msgs::msg::AdrianMessage::UniquePtr msg) -> void
            {
                RCLCPP_INFO(get_logger(), "I heard: %s with num %u", msg->name.c_str(), msg->amount);
            };
            subscription_ = create_subscription<onboarding_msgs::msg::AdrianMessage>("topic", 10, topic_callback);
        }
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AdrianSubscriber>());
    rclcpp::shutdown();
    return 0;
}
