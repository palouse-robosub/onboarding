#include <chrono>
#include <memory>
#include <cmath>
#include <string>
#include <regex>
#include <iostream>
#include <curl/curl.h>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/fluid_pressure.hpp"

using namespace std::chrono_literals;

class AtmosphericPressurePublisher : public rclcpp::Node {
  public:

    //callback function for http get request
    static size_t WriteCallback(void *contents,size_t size,size_t nmemb,std::string *response){
        size_t totalSize =size *nmemb;
        response->append((char*) contents,totalSize);
        return totalSize;
    }

    // makes the HTTP get Request and returns a plaintext string of the METAR from aviationweather.gov
    std::string MakeRequest() {
        CURL *curl;
        CURLcode res;
        std::string responseString;
        curl= curl_easy_init();
        if(curl){
            curl_easy_setopt(curl,CURLOPT_URL,"https://aviationweather.gov/api/data/metar?ids=KPUW&format=raw&taf=false&hours=0");
            curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteCallback);
            curl_easy_setopt(curl,CURLOPT_WRITEDATA,&responseString);
            res =curl_easy_perform(curl);
            if(res!=CURLE_OK){
                std::cerr<<"Curl error: "<<curl_easy_strerror(res) <<std::endl;
            }
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();

        return responseString;
    }
    
    // gets the current hour with chrono
    int GetCurrentHour() {
        std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        return std::localtime(&t)->tm_hour;
    }

    double GetAtmosphericPressure() {

        int currentHour = GetCurrentHour();

        if (!hour || hour != currentHour) {     // METAR is updated once per hour so we check if we've already gotten it this hour

            std::string METAR = MakeRequest();
            
            // regex to get the atmospheric pressure part of METAR
            std::regex pattern(R"( A(\d{4}))");
            std::smatch matches;

            if (std::regex_search(METAR, matches, pattern)) {
                std::string my_string_var = matches[1].str();
                aPressure = std::stoi(matches[1].str());
            }

            hour = currentHour;
        }

        return (double)aPressure * 33.863889;   // return value in Pascals
    }

    AtmosphericPressurePublisher() : Node("pressure_publisher") {
        publisher_ = this->create_publisher<sensor_msgs::msg::FluidPressure>("topic", 10);

        auto timer_callback =
            [this]() -> void {
                auto message = sensor_msgs::msg::FluidPressure();
                message.fluid_pressure = GetAtmosphericPressure();
                message.variance = 0.0; // no variance known 
                RCLCPP_INFO(this->get_logger(), "Pressure: %f", message.fluid_pressure);
                this->publisher_->publish(message);
            };
        timer_ = this->create_wall_timer(2000ms, timer_callback);

    }

  private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::FluidPressure>::SharedPtr publisher_;
    int hour; 
    double aPressure = 0;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AtmosphericPressurePublisher>());
    rclcpp::shutdown();
    return 0;
}
