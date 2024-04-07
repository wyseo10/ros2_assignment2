// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cstdio>
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include "geometry_msgs/msg/twist.hpp"

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher")
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtlesim1/turtle1/cmd_vel", 10);
    publisher_2 = this->create_publisher<geometry_msgs::msg::Twist>("/turtlesim2/turtle1/cmd_vel", 10);
    timer_ = this->create_wall_timer(
      100ms, std::bind(&MinimalPublisher::timer_callback, this));
  }
  
private:
  void timer_callback()
  {

//For turtle1, square

  if(flag == true)
  {
    cmd_vel.linear.x = 3;
    cmd_vel.angular.z = 0;
    flag = false;
  }
  else 
  {
    cmd_vel.linear.x = 0;
    cmd_vel.angular.z = 3.141592653589723238462643383 / 2;
    flag = true;
  }

    publisher_->publish(cmd_vel);
    //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_2;


  //-Init variables
  geometry_msgs::msg::Twist cmd_vel;
  geometry_msgs::msg::Twist cmd_vel_2;
  double x_velocity = 3;
  double y_velocity = 3;
  double ang_velocity = 1;
  bool flag = true;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
