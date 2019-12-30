#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <turtlesim/SetPen.h>
#include <turtlesim/TeleportAbsolute.h>
#include "p1ex/AddTwoInts.h"

using namespace std;


bool add(p1ex::AddTwoInts::Request  &req,
         p1ex::AddTwoInts::Response &res)
{
    //The blue areas size is actually 11X11
    float box_size = ros::param::param("~box_size", 11);
    ros::NodeHandle n;
    ros::service::waitForService("/turtle1/teleport_absolute", -1);
    ros::ServiceClient teleport_client = n.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    ros::ServiceClient pen_client = n.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
    ros::Rate loop_rate(10);
    turtlesim::SetPen pen_srv;
    //Boolean for stopping the box generator loop.
    pen_srv.request.off = true;
    pen_client.call(pen_srv);

    turtlesim::TeleportAbsolute srv;
    
//Box generator loop.
    //Here we want to continously wait for when we have received values from the map.cpp.
    //The the box will be generated once

            cout <<"Længden: " << req.a << endl;
            cout <<"Bredden: " << req.b << endl;

            srv.request.x = (box_size-req.a)/2;
            srv.request.y = (box_size-req.b)/2;
            teleport_client.call(srv);

            pen_srv.request.off = false;
            pen_srv.request.width = 8;
            pen_srv.request.r = 228;
            pen_srv.request.g = 228;
            pen_client.call(pen_srv);

            srv.request.x = (box_size-req.a)/2;
            srv.request.y = (box_size+req.b)/2;
            teleport_client.call(srv);

            srv.request.x = (box_size+req.a)/2;
            srv.request.y = (box_size+req.b)/2;
            teleport_client.call(srv);

            srv.request.x = (box_size+req.a)/2;
            srv.request.y = (box_size-req.b)/2;
            teleport_client.call(srv);

            srv.request.x = (box_size-req.a)/2;
            srv.request.y = (box_size-req.b)/2;
            teleport_client.call(srv);

            pen_srv.request.off = true;
            pen_client.call(pen_srv);

            srv.request.x = 5.5;
            srv.request.y = 5.5;
            teleport_client.call(srv);
           
        
    return true;
}

int main(int argc, char **argv)
{
    //Here we define our map
    ros::init(argc, argv, "one");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("add_two_ints", add);
    ROS_INFO("Ready to create box");
    ros::spin();
    return 0;
}


