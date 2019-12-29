#include <boost/bind.hpp>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <std_srvs/Empty.h>
#include <iostream>
#include <turtlesim/TeleportAbsolute.h>
//#include <turtlesim/SetPen.h>
#include <sstream>     
#include <std_msgs/Float32.h>
#include "p1ex/AddTwoInts.h"
using namespace std;



int main(int argc, char **argv)
{
  ros::init(argc, argv, "two");
  ros::NodeHandle nh;
  float box_size = ros::param::param("~box_size", 11);
  ros::service::waitForService("/turtle1/teleport_absolute", -1);
  ros::ServiceClient client = nh.serviceClient<p1ex::AddTwoInts>("add_two_ints");
  ros::ServiceClient teleport_client = nh.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
  p1ex::AddTwoInts srv;
  turtlesim::TeleportAbsolute srv1;
  ros::Rate loop_rate(5);
  bool runLoop = true;
  float i, k;
  int turn = 2;
  float jj, ii, Y_MIN, Y_MAX, X_MAX, X_MIN;

  
  cout << "What is the length " << endl;
  cin >> ii;
  cout << "What is the width " << endl;
  cin >> jj;
  srv.request.a = ii;
  srv.request.b = jj;
  Y_MIN = (box_size-jj)/2;
  Y_MAX = (box_size+jj)/2;
  X_MAX = (box_size+ii)/2;
  X_MIN = (box_size-ii)/2;
  ii = X_MIN;
  jj = Y_MAX;
  
  if (client.call(srv))
  {
    ROS_INFO("Sum: %ld", (long int)srv.response.sum);

    while (runLoop)
    {
      srv1.request.x = ii;
      srv1.request.y = jj;
      teleport_client.call(srv1);
      loop_rate.sleep();  
            if (jj <= Y_MIN)
            {
              if (ii >= X_MAX)
              {
                runLoop = false;
                cout << "If1.1"<< endl;
              }
              else
              {
                ii = X_MAX;
              //ROS_INFO("If1.2");
                cout << "If1.2"<< endl;
              } 
            }
            else 
            {
              if (ii >= X_MAX)
              {
                if (turn == 1)
                {
                  ii = X_MAX;
                  jj = jj - 0.5;
                  turn = 2;
                //ROS_INFO("If2.1");
                  cout << "If2.1"<< endl;
                }
                else
                {
                  ii = X_MIN;
                  turn = 1;
                //ROS_INFO("If2.2");
                  cout << "If2.2"<< endl;
                }
              }
              else
              {
                if (turn == 1)
                {
                  ii = X_MIN;
                  jj = jj - 0.5;
                  turn = 2;
                  //ROS_INFO("If3.1");
                  cout << "If3.1"<< endl;
                }
                else
                {
                  ii = X_MAX;
                  turn = 1;
                  //ROS_INFO("If3.2");
                  cout << "If3.2"<< endl;
                }
              }
            }
    }
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }
 // }

  return 0;
}
