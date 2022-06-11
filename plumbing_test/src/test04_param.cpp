#include "ros/ros.h"

/*
   需求： 修改参数服务器中 turtlesim 背景色相关的参数

   1.初始化ROS 节点
   2. 不一定需要创建句柄节点（和后续API 有关） 参数设置上有两套API c++ rset。。 Node。。
   3. 修改参数 
*/

int main(int argc, char  *argv[])
{
    //   1.初始化ROS 节点
    ros::init(argc,argv,"change_bgColor");
    //2. 不一定需要创建句柄节点（和后续API 有关） 参数设置上有两套API c++ rset。。 Node。。
    ros::NodeHandle nh("turtlesim"); // turtlesim 命名空间，构造函数 
    //or 
    //ros::NodeHandle nh;
    // nh.setParam("/turtlesim/background_r",255);
    // nh.setParam("/turtlesim/background_g",65);
    // nh.setParam("/turtlesim/background_b",255);
    // 3. 修改参数
    //如果调用 ros::param 不需要创建节点句柄
    //  ros::param::set("/turtlesim/background_r",0);
    //  ros::param::set("/turtlesim/background_g",0);
    //  ros::param::set("/turtlesim/background_b",0);
    nh.setParam("background_r",255);
    nh.setParam("background_g",255);
    nh.setParam("background_b",255);
    return 0;
}
