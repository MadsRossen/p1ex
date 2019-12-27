#include <boost/bind.hpp>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <std_srvs/Empty.h>
#include <iostream>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <std_msgs/String.h>
#include <sstream>     
#include <std_msgs/Float32.h>
using namespace std;



int main(int argc, char **argv)
{
  ros::init(argc, argv, "two");
  ros::NodeHandle nh;
  ros::Publisher len_pub = nh.advertise<std_msgs::Float32>("leng", 10);
  ros::Publisher wid_pub = nh.advertise<std_msgs::Float32>("wid", 10);
  ros::Rate loop_rate(0.5);
  //ros::Subscriber pose_sub = nh.subscribe("turtle1/pose", 1, poseCallback);
  //ros::Publisher twist_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
  //ros::ServiceClient reset = nh.serviceClient<std_srvs::Empty>("reset");
  //ros::Timer timer = nh.createTimer(ros::Duration(0.016), boost::bind(timerCallback, _1, twist_pub));
  float i;

  float k;
  
  cout << "What is the length ";
  cin >> i;
  cout << "What is the width ";
  cin >> k;
 while (ros::ok()){
  std_msgs::Float32 length;
  length.data = i;
  std_msgs::Float32 width;
  width.data = k;
  //std::stringstream ss;
  //ss << i << k;
  //msg.data = ss.str();
  //ROS_INFO("%s", msg.data.c_str());

  len_pub.publish(length);
  wid_pub.publish(width);
  ros::spinOnce();
  loop_rate.sleep();
  }

  return 0;
}
