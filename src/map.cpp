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
    //Lenght of the box
    float lengthn;
    //width of the box
    float widthn;
    //Indicators for when one of the functions have been running. 
    bool run1, run2 = false;    
    void lisenterlength(const std_msgs::Float32::ConstPtr& length){
       
        lengthn = length->data;
        //cout << lengthn;
        run1 = true;
    }
    void lisenterwidth(const std_msgs::Float32::ConstPtr& width){
        
        widthn = width->data;
        //cout <<  widthn11;
        run2 = true;
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
    //The blue areas size is actually 11X11
    float box_size = ros::param::param("~box_size", 11);
    ros::NodeHandle n;
    ros::service::waitForService("/turtle1/teleport_absolute", -1);
    ros::ServiceClient teleport_client = n.serviceClient<turtlesim::TeleportAbsolute>("/turtle1/teleport_absolute");
    ros::ServiceClient pen_client = n.serviceClient<turtlesim::SetPen>("/turtle1/set_pen");
    ros::Subscriber subl = n.subscribe("leng", 1000, &CallbackSub::lisenterlength, &newCallback);
    ros::Subscriber subw = n.subscribe("wid", 1000, &CallbackSub::lisenterwidth, &newCallback);
    ros::Rate loop_rate(10);
    turtlesim::SetPen pen_srv;
    //Boolean for stopping the box generator loop.
    bool stoploop = false;
    pen_srv.request.off = true;
    pen_client.call(pen_srv);

    turtlesim::TeleportAbsolute srv;
    
//Box generator loop.
    //Here we want to continously wait for when we have received values from the map.cpp.
    //The the box will be generated once.
    while ( ros::ok())
    {  
        //When new values for the box size have been received 
        //and its the first time the lopp runs.
        if (newCallback.run1 && newCallback.run2 && !stoploop)
        {
        //ros::spinOnce();
        // Wait 10 second
        //usleep(15000000);

            cout <<"Længden: " << newCallback.lengthn << endl;
            cout <<"Bredden: " << newCallback.widthn << endl;

            srv.request.x = (box_size-newCallback.lengthn)/2;
            srv.request.y = (box_size-newCallback.widthn)/2;
            teleport_client.call(srv);

            pen_srv.request.off = false;
            pen_srv.request.width = 8;
            pen_srv.request.r = 228;
            pen_srv.request.g = 228;
            pen_client.call(pen_srv);

            srv.request.x = (box_size-newCallback.lengthn)/2;
            srv.request.y = (box_size+newCallback.widthn)/2;
            teleport_client.call(srv);

            srv.request.x = (box_size+newCallback.lengthn)/2;
            srv.request.y = (box_size+newCallback.widthn)/2;
            teleport_client.call(srv);

            srv.request.x = (box_size+newCallback.lengthn)/2;
            srv.request.y = (box_size-newCallback.widthn)/2;
            teleport_client.call(srv);

            srv.request.x = (box_size-newCallback.lengthn)/2;
            srv.request.y = (box_size-newCallback.widthn)/2;
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
            //Setting stop loop to true as we only want create the box once: 
            stoploop = true;
            //Setting the functions run indicators to false as we have now used the value they received.
            newCallback.run1 = false;
            newCallback.run2 = false;
        }
    ros::spinOnce();
    loop_rate.sleep();
    }
    return 0;
}


