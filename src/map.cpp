#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Pose.h>
#include <iostream>
#include <turtlesim/SetPen.h>
#include <turtlesim/TeleportAbsolute.h>
#include <stdlib.h>
#include <std_srvs/Empty.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <unistd.h>



using namespace std;



class CallbackSub
{
    public:
    float lengthn;
    float widthn;
    void lisenterlength(const std_msgs::Float32::ConstPtr& length){
        //float lengthn;
        lengthn = length -> data;
        //cout << lengthn;
        
        
    }
    void lisenterwidth(const std_msgs::Float32::ConstPtr& width){
         //float widthn;
        widthn = width -> data;
        cout <<  widthn;
    }
};



/*void ros (){
    while (newC < 0.5) {
   
       
    }
       
    }*/



int main(int argc, char **argv)
{
    //Here we define our map
    ros::init(argc, argv, "one");
    CallbackSub newCallback;
    //ros ();
    float box_size = ros::param::param("~box_size", 9);
    
    ros::NodeHandle n;
    ros::service::waitForService("/turtle1/teleport_absolute", -1);
    ros::ServiceClient teleport_client = n.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    ros::ServiceClient pen_client = n.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
    ros::Subscriber subl = n.subscribe("leng", 1000, &CallbackSub::lisenterlength, &newCallback);
    ros::Subscriber subw = n.subscribe("wid", 1000, &CallbackSub::lisenterwidth, &newCallback);
    ros::Rate loop_rate(10);
    turtlesim::SetPen pen_srv;

    pen_srv.request.off = true;
    pen_client.call(pen_srv);

    turtlesim::TeleportAbsolute srv;
    
    /*do {
    }
    while ( 0 > widt );*/
     ros::spinOnce();
    // Wait 10 second
    usleep(15000000);

    cout <<"Længden: " << newCallback.lisenterlength.lenghtn << endl;
    cout <<"Bredden: " << newCallback.lisenterlength.widthn << endl;

    srv.request.x = newCallback.lisenterlength.lengthn-box_size/2;
    srv.request.y = newCallback.lisenterlength.lengthn-box_size/2;
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

    ros::spinOnce();

    return 0;
}


