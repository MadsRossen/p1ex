#include <ros/ros.h>

int main(int argc, char **argv)
{
    //Here we define our map
    ros::init(argc, argv, "one");
    ros::NodeHandle nh;
    std::cout<< "hello world" << std::endl;

    return 0;
}
