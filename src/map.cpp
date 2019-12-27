#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <iostream>
#include <turtlesim/SetPen.h>
#include <turtlesim/TeleportAbsolute.h>
#include <stdlib.h>
#include <std_srvs/Empty.h>
#include <std_msgs/String.h>

using namespace std;

void lis(const std_msgs::String::ConstPtr& msg){
    char hej = msg->data[1];
    //ROS_INFO(hej);
    
}


int main(int argc, char **argv)
{
    //Here we define our map
    ros::init(argc, argv, "one");
    
    float box_size = ros::param::param("~box_size", 9);

    ros::NodeHandle n;
    ros::service::waitForService("/turtle1/teleport_absolute", -1);
    ros::ServiceClient teleport_client = n.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    ros::ServiceClient pen_client = n.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
    ros::Subscriber sub = n.subscribe("leng", 10, lis);

    turtlesim::SetPen pen_srv;

    pen_srv.request.off = true;
    pen_client.call(pen_srv);

    turtlesim::TeleportAbsolute srv;

    float wp = 5.5;
    int lp = 2;


    srv.request.x = wp-box_size/2;
    srv.request.y = 5.5-box_size/2;
    teleport_client.call(srv);

    pen_srv.request.off = false;
    pen_srv.request.width = 8;
    pen_srv.request.r = 228;
    pen_srv.request.g = 228;
    pen_client.call(pen_srv);

    srv.request.x = 5.5-box_size/2;
    srv.request.y = 5.5+box_size/2;
    teleport_client.call(srv);

    srv.request.x = 5.5+box_size/2;
    srv.request.y = 5.5+box_size/2;
    teleport_client.call(srv);

    srv.request.x = 5.5+box_size/2;
    srv.request.y = 5.5-box_size/2;
    teleport_client.call(srv);

    srv.request.x = 5.5-box_size/2;
    srv.request.y = 5.5-box_size/2;
    teleport_client.call(srv);

    pen_srv.request.off = true;
    pen_client.call(pen_srv);

    srv.request.x = 5.5;
    srv.request.y = 5.5;
    teleport_client.call(srv);

    pen_srv.request.off = false;
    pen_srv.request.width = 8;
    pen_srv.request.r = 10;
    pen_srv.request.g = 228;
    pen_srv.request.b = 228;
    pen_client.call(pen_srv);

    ros::spin();

    return 0;
}
