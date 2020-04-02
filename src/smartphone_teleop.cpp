#include <chrono>
#include <memory>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class Velocity_Publisher : public rclcpp::Node
{
public:
  std::vector<float> xyz = {0.0, 0.0, 0.0};
  int sock;
  int addr_len, bytes_read;
  char recv_data[1024];
  struct sockaddr_in server_addr, client_addr;
  bool initilized = false;

  Velocity_Publisher(): Node("velocity_publisher") {
    cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 1);

    timer_ = this->create_wall_timer(
      50ms, std::bind(&Velocity_Publisher::timer_callback, this));
  }

private:
  void UDP_iniitilize(){
    if ((Velocity_Publisher::sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        RCLCPP_INFO(this->get_logger(), "can't open socket!");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero),8);

    int binding = bind(sock,(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    
    if (binding == -1) {
        RCLCPP_INFO(this->get_logger(), "can't bind!");
    }

    addr_len = sizeof(struct sockaddr);
  }

  void parse_sensor_data() {
    char* token = strtok(recv_data, ",");
    xyz.at(0) = atof(token);
    token = strtok(NULL, ",");
    xyz.at(1) = atof(token);
    token = strtok(NULL, ",");
    xyz.at(2) = atof(token);
  }

  void timer_callback()
  {
    if (initilized == false) {
        UDP_iniitilize();
        initilized = true;
    }

    bytes_read = recvfrom(sock,
							recv_data,
							1024,
							0,
							(struct sockaddr *)&client_addr,
							(socklen_t *)&addr_len);

	if (bytes_read){
        recv_data[bytes_read] = '\0';
    } 

    parse_sensor_data();
    
    geometry_msgs::msg::Twist cmd_vel;

    cmd_vel.linear.x = 0.05*xyz[1];
    cmd_vel.linear.y = 0.0;
    cmd_vel.linear.z = 0.0;
    cmd_vel.angular.x = 0.0;
    cmd_vel.angular.y = 0.0;
    cmd_vel.angular.z = 0.05*xyz[2];

    cmd_vel_pub_->publish(cmd_vel);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Velocity_Publisher>());
  rclcpp::shutdown();
  return 0;
}