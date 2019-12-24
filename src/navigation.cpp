#include <ros/ros.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "two");
  ros::NodeHandle nh;
  std::cout<< "hello world" << std::endl;

 return 0;
}
