#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <turtlesim/SetPen.h>
#include <turtlesim/TeleportAbsolute.h>
#include "p1ex/AddTwoInts.h"
using namespace std;

//Function for getting and validating input.
int validateInput (float f_Input, bool confirm_Input, string dimension )
{
  while (!confirm_Input)
  {
    //Get input from user.
    cout << "Define the "<< dimension <<":"<<" (Must be between 1 and 11) " << endl;
    cin >> f_Input;
    //Checks if the input data does not match the varibale
    if(cin.fail())
      {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "You have entered wrong "<< dimension <<" input." << endl;
      }
    //if the input data matches, check if it above 11 or below 1
    else if(!cin.fail() && f_Input > 11 || f_Input < 1)
    {
      cout << "The " << dimension << " is not between 1 and 11" << endl;
    }
    //If the input is valid we can end the function
    else if (!cin.fail() && f_Input < 11 && f_Input > 1)
    {
      confirm_Input = true;
    }
  }
  //returning the valid input from the user.
  return f_Input;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "navigation");
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
  bool jjGood = false;
  bool iiGood = false;
  float jj, ii, Y_MIN, Y_MAX, X_MAX, X_MIN;

  //Running the validation function to receive valid input from user. 
  ii = validateInput(ii, iiGood, "lenght");
  jj = validateInput(jj, jjGood, "width");

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
                cout << "Result 6"<< endl;
              }
              else
              {
                ii = X_MAX;
                cout << "Result 5"<< endl;
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
                  cout << "Result 2"<< endl;
                }
                else
                {
                  ii = X_MIN;
                  turn = 1;
                  cout << "Result 3"<< endl;
                }
              }
              else
              {
                if (turn == 1)
                {
                  ii = X_MIN;
                  jj = jj - 0.5;
                  turn = 2;
                  cout << "Result 4"<< endl;
                }
                else
                {
                  ii = X_MAX;
                  turn = 1;
                  cout << "Result 1"<< endl;
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
