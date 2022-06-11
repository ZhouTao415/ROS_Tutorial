#include "ros/ros.h"


/* 
    需要实现参数的新增与修改
    需求：首先设置机器人的共享参数，类型，半径（0.15m）
         再修改半径（0.2m）
    实现：
        ros::NodeHandle
            setParam("key",value) //function
        ros::param
            set("key",value)
    修改，只需继续调用 setParam or seet function ,保证 key 已存在，那么值会覆盖。 

*/
int main(int argc, char  *argv[])
{
    //首先初始化ROS节点
    ros::init(argc,argv,"set_param_c");
    //创建ROS节点句柄
    ros::NodeHandle nh;
    //参数增-------------------------------------
    //方案1: nh,先生成机器人的类型type 和机器人的半径值
    nh.setParam("type", "xiaoHUang");
    nh.setParam("radius",0.15);
    //方案2： ros::param key name can't same
    ros::param::set("type_param","xiaoBai");
    ros::param::set("radius_param", 0.15);
    //参数改-------------------------------------
    //方案1: nh key 重复就会覆盖之前
    nh.setParam("radius",0.2);
    //方案2： ros::para
    ros::param::set("radius_param", 0.25);
    return 0;
}
