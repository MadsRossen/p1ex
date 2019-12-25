#include <boost/bind.hpp>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <std_srvs/Empty.h>
#include <iostream>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <std_msgs/String.h>
     
using namespace std;
int length;
int width;


int main(int argc, char **argv)
{
  ros::init(argc, argv, "two");
  ros::NodeHandle nh;
  ros::Publisher len_pub = nh.advertise<std_msgs::String>("leng", 10);
  //ros::Subscriber pose_sub = nh.subscribe("turtle1/pose", 1, poseCallback);
  //ros::Publisher twist_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
  //ros::ServiceClient reset = nh.serviceClient<std_srvs::Empty>("reset");
  //ros::Timer timer = nh.createTimer(ros::Duration(0.016), boost::bind(timerCallback, _1, twist_pub));

  cout << "What is the length ";
  cin >> length ;
  cout << "What is the width ";
  cin >> width ;
 
  std_msgs::String msg;
  std::stringstream msglen;
  msglen << width,length << count;
  msg.data = msglen.str();
  len_pub.publish(msg);

  return 0;
}
