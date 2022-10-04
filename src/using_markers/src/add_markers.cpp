#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

using namespace std;

float robot_x, robot_y, robot_w;

void callback(const nav_msgs::Odometry &odom)
{
    robot_x = odom.pose.pose.position.x;
    robot_y = odom.pose.pose.position.y; 
    robot_w = odom.pose.pose.orientation.w; 
} 


int main( int argc, char** argv )
{
    ros::init( argc, argv, "tmp");
    ros::NodeHandle n;
    ros::Rate r(1);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    ros::Subscriber sub = n.subscribe("odom",3,callback);
    bool picked = false;
    float dist_1, dist_2;
    //float ang_1, ang_2;


    uint32_t shape = visualization_msgs::Marker::CUBE;

    while( ros::ok() )
    {
        visualization_msgs::Marker marker;
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time::now();

        marker.ns = "basic_shapes";
        marker.id = 0;

        marker.type = shape;

        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;

        marker.scale.x = 0.2;
        marker.scale.y = 0.2;
        marker.scale.z = 0.2;

        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0f;

        marker.lifetime = ros::Duration();

        while( marker_pub.getNumSubscribers() < 1 )
        {
            if (!ros::ok())
            {
                return 0;
            }
            ROS_WARN_ONCE("Please create a subscriber to the marker");
        }


        if(picked==false)
        {
           marker.pose.position.x = 1.5;
           marker.pose.position.y = 6.0;
           marker.action = visualization_msgs::Marker::ADD;
           marker_pub.publish(marker);
           //ros::Duration(5).sleep();
           ROS_INFO("Object ready to pick up");
        }


        while(true)
        {
          dist_1 = sqrt( pow(robot_x - marker.pose.position.x, 2) + pow(robot_y - marker.pose.position.y, 2) );

          //ang_1 = abs(robot_w - marker.pose.orientation.w);

          //if(dist_1<= 0.3 && ang_1 < M_PI/180)
          if(dist_1<= 0.3)
          {
            marker.action = visualization_msgs::Marker::DELETE;
            marker_pub.publish( marker );
            ROS_INFO("Object has been picked up");
            picked = true;
            //ros::Duration(5.0).sleep();
            
            break;
           }
         }


        while(picked==true)
        {
          dist_2 = sqrt( pow(robot_x - marker.pose.position.x, 2) + pow(robot_y - marker.pose.position.y, 2) );

          //ang_2 = abs(robot_w - marker.pose.orientation.w);

          //if(dist_2<= 0.3 && ang_2 < M_PI/180)
          if(dist_2<= 0.3)
          {
             marker.pose.position.x = 3.0;
             marker.pose.position.y = -1.0;
             marker.action = visualization_msgs::Marker::ADD;
             marker_pub.publish(marker);
             //ros::Duration(5).sleep();
             ROS_INFO("Object has been droped");

              break;
           }
         }
        
       

        ros::spinOnce();
        r.sleep();
        
    }


    return 0;
}
