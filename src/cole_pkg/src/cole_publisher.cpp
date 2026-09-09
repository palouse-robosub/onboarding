#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/nav_sat_fix.hpp"
#include "sensor_msgs/msg/nav_sat_status.hpp"

using namespace std::chrono_literals;

class ColePublisher : public rclcpp::Node {
  public:
    ColePublisher() : Node("cole_publisher") {
        publisher_ = this->create_publisher<sensor_msgs::msg::NavSatFix>(
            "cole_topic", 10
        );
        auto timer_callback = [this]() -> void {
            auto message = sensor_msgs::msg::NavSatFix();

            message.header.stamp    = this->get_clock()->now();
            message.header.frame_id = "gps_dummy_frame";

            message.status.status =
                sensor_msgs::msg::NavSatStatus::STATUS_SBAS_FIX;
            message.status.service =
                sensor_msgs::msg::NavSatStatus::SERVICE_GPS;

            // Pullman, WA (Dana 3)
            message.latitude  = 46.7301761;      // degrees
            message.longitude = -117.1694623;    // degrees
            message.altitude  = 766;             // meters

            message.position_covariance = {
                1, 0, 0, 0, 1, 0, 0, 0, 1
            };    // diagonal

            message.position_covariance_type =
                sensor_msgs::msg::NavSatFix::COVARIANCE_TYPE_UNKNOWN;

            this->publisher_->publish(message);
        };
        timer_ = this->create_wall_timer(2000ms, timer_callback);
    }

  private:
    rclcpp::TimerBase::SharedPtr                              timer_;
    rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr publisher_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ColePublisher>());
    rclcpp::shutdown();
    return 0;
}
