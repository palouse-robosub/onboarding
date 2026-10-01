// includes
#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class GavinPublisher : public rclcpp::Node {
  public:
    GavinPublisher()
      // constructor
      : Node("gavin_publisher"), count_(0) {
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        auto timer_callback = [this]() -> void {
            auto message = std_msgs::msg::String();
            if(count_++%2){
              message.data = "Gavin thinks this is True";
            } else {
              message.data = "Gavin thinks this is False";
            }
            //message.data =
                //"Gavin thinks this is " + this->(boolean)count_++%2;
                //"Gavin thinks this is " + std::to_string((boolean)this->count_++%2);
            // message.data = "Gavin thinks this is " +
            // std::to_string(this->count_++);
            RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
            this->publisher_->publish(message);
        };
        timer_ = this->create_wall_timer(2000ms, timer_callback);
    }

  private:
    rclcpp::TimerBase::SharedPtr                        timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t                                              count_;
};

int main(int argc, char* argv[]) {
    // setup and spin
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GavinPublisher>());
    rclcpp::shutdown();
    return 0;
}
