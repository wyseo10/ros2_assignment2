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

#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <turtlesim/msg/pose.hpp>

using std::placeholders::_1;

  double real_x = 0;
  double real_y = 0;

  double err_x = 0;
  double err_y = 0;
  double err_theta = 0;


class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<turtlesim::msg::Pose>(
      "/turtle1/pose", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const turtlesim::msg::Pose &msg) const
  {
    real_x = msg.x - 5.544445;
    real_y = msg.y - 5.544445;

    RCLCPP_INFO(this->get_logger(), "x position: '%lf'", real_x);
    RCLCPP_INFO(this->get_logger(), "y position: '%lf'", real_y);

    

  }
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
