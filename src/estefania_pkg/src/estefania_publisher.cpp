#include <chrono>
#include <memory>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;

class EstefaniaPublisher : public rclcpp::Node {
  public:
    EstefaniaPublisher() :
      Node("estefania_publisher"), generator_(std::random_device{}()),
      distribution_(0.0f, 100.0f) {
        publisher_ = this->create_publisher<std_msgs::msg::Float32>(
            "estefania_topic", 10
        );

        timer_ = this->create_wall_timer(
            2s, std::bind(&EstefaniaPublisher::publish_message, this)
        );
    }

  private:
    void publish_message() {
        std_msgs::msg::Float32 message;
        message.data = distribution_(generator_);

        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr                         timer_;

    std::mt19937                          generator_;
    std::uniform_real_distribution<float> distribution_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<EstefaniaPublisher>());
    rclcpp::shutdown();

    return 0;
}
