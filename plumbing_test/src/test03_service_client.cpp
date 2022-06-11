#include "ros/ros.h"
#include "turtlesim/Spawn.h"
/*  
   需求：是向服务端发送请求，生成一只小乌龟
        1.服务话题 /spawn
        2.服务消息类型 turtlesim/Spawn
        3.运行前先启动 turtlesim_node 节点
    
    1 包含头文件
    2 初始化ros节点
    3 创建节点句柄
    4 创建客户端对象
    5 组织数据并发送 客户端可控不需要回调函数
    6 处理响应
*/

int main(int argc, char  *argv[])
{
    setlocale(LC_ALL,"");
    // 2 初始化ros节点
    ros::init(argc,argv,"service_call");
    // 3 创建节点句柄
    ros::NodeHandle nh;
    // 4 创建客户端对象
    ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
    // 5 组织数据并发送 客户端可控不需要回调函数 创建spawn对象
        //判断服务状态
    ros::service::waitForService("/spawn");
    //5-1 请求组织数据
    turtlesim::Spawn spawn;
    spawn.request.x = 4.0;
    spawn.request.y = 1.0;
    spawn.request.theta = 1.57;
    spawn.request.name = "turtle_1224";
    //5-2 发送请求

    //client.waitForExistence();
    //如果启动就访问我们的服务器用下面的方式,产生响应，函数返回值是bool
    //client.call(spawn);//意思是我要把spawn对象发送到服务器，spawn.request 就包含上面的数据了
    //flag 是 接收响应状态，响应结果也会被设置进spwn对象， bool 为ture ，正常响应，否则有问题
    bool flag = client.call(spawn);
    
    // 6 处理响应
    if (flag)
    {
        ROS_INFO("新的乌龟生成,名字:%s", spawn.response.name.c_str());
    } 
    else{
        ROS_INFO("乌龟生成失败!!!");
    }

    return 0;
}

// int main(int argc, char *argv[])
// {
//     setlocale(LC_ALL,"");
//     // 2.初始化 ros 节点
//     ros::init(argc,argv,"set_turtle");
//     // 3.创建 ros 句柄
//     ros::NodeHandle nh;
//     // 4.创建 service 客户端
//     ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
//     // 5.等待服务启动
//     // client.waitForExistence();
//     ros::service::waitForService("/spawn");
//     // 6.发送请求
//     turtlesim::Spawn spawn;
//     spawn.request.x = 1.0;
//     spawn.request.y = 1.0;
//     spawn.request.theta = 1.57;
//     spawn.request.name = "my_turtle";
//     bool flag = client.call(spawn);
//     // 7.处理响应结果
//     if (flag)
//     {
//         ROS_INFO("新的乌龟生成,名字:%s",spawn.response.name.c_str());
//     } else {
//         ROS_INFO("乌龟生成失败!!!");
//     }


//     return 0;
// }
