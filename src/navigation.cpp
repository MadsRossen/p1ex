#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <turtlesim/SetPen.h>
#include <turtlesim/TeleportAbsolute.h>
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
  ros::ServiceClient pen_client = nh.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
  p1ex::AddTwoInts srv;
  turtlesim::TeleportAbsolute srv1;
  turtlesim::SetPen pen_srv;
  ros::Rate loop_rate(5);
  bool runLoop = true;
  //float i, k;
  int turn = 2;
  float jj, ii, Y_MIN, Y_MAX, X_MAX, X_MIN;

  cout << "What is the length. Must be between 1 and 11 " << endl;
  cin >> ii;
while  ( ii > 11 || ii < 1 ){
    cout << "The length is not between 1 and 11" << endl;
    cout << "Enter new length" << endl;
    cin >> ii;
    }

  cout << "What is the width. Must be between 1 and 11 " << endl;
  cin >> jj;

while  ( jj > 11 || jj < 1){
    cout << "The width is not between 1 and 11" << endl;
    cout << "Enter new width" << endl;
    cin >> jj;
    }
 
  srv.request.a = ii;
  srv.request.b = jj;
  Y_MIN = (box_size-jj)/2 +0.5;
  Y_MAX = (box_size+jj)/2 -0.3;
  X_MAX = (box_size+ii)/2 -0.3;
  X_MIN = (box_size-ii)/2 +0.3;
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
      pen_srv.request.off = false;
      pen_srv.request.width = 8;
      pen_srv.request.r = 10;
      pen_srv.request.g = 228;
      pen_srv.request.b = 228;
      pen_client.call(pen_srv);
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
