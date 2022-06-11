#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
/* 
    需求：发布速度消息
         话题：/turtle1/cmd_vel
         消息：geometry_msgs/Twist 

    1.包含头文件
    2.初始化ROS节点
    3，创建句柄节点
    4.创建发布对象
    5发布逻辑
    6.spinOnce();   
*/

int main(int argc, char  *argv[])
{

    // 2.初始化ROS节点
    ros::init(argc,argv,"my_control");
    // 3，创建句柄节点
    ros::NodeHandle nh;
    // 4.创建发布对象
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    // 5发布逻辑
    ros::Rate rate(10);
    //组织发布的消息
    geometry_msgs::Twist twist;
    twist.linear.x = 1.0; //double
    twist.linear.y = 0; //double
    twist.linear.z = 0; //double

    twist.angular.x = 0;
    twist.angular.y = 0;
    twist.angular.z = 0.5;

    while (ros::ok)
    {
        pub.publish(twist);
        //休眠
        rate.sleep();
        // 6.spinOnce();  
        ros::spinOnce();

    }
    
      // 6.spinOnce();  
    
    return 0;
}
