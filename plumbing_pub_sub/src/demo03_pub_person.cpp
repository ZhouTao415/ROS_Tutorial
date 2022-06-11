#include "ros/ros.h"
#include "plumbing_pub_sub/Person.h"

/*
    发布方:发布人的信息
          1.包含头文件
              # #include "plumbing_pub_sub/Person.h"
          2.初始化ROS节点
          3.创建节点句柄
          4.创建发布者对象
          5.编写发布逻辑，发布数据
*/
int main(int argc, char  *argv[])
{    // nh.setParam("/turtlesim/background_r",255);
    // nh.setParam("/turtlesim/background_g",65);
    // nh.setParam("/turtlesim/background_b",255);
        setlocale(LC_ALL,"");
        ROS_INFO("这是消息的发布方");

        // 2.初始化ROS节点
        ros:: init(argc,argv,"banzhuren");
        // 3.创建节点句柄
        ros::NodeHandle nh;
        //4.创建发布者对象 10 队列长度
        ros::Publisher pub = nh.advertise<plumbing_pub_sub::Person>("liaotian",10);
        //5.编写发布逻辑，发布数据
        //5.1 创建被发布的数据，创建一个person对象出来
        plumbing_pub_sub::Person person;
        //perosn 有一系列数据属性
        //为了让数据可识性
        person.name = "张三";
        person.age = 1;
        person.height = 1.73;
        //5.2设置发布频率
        ros::Rate rate(1);

        //5.3循环发布数据
        while (ros::ok())
        {
            //为了让数据可识性
            //修改数据
            person.age += 1;

            //核心: 数据发布,调用Pub对象
            pub.publish(person);

            ROS_INFO("发布的消息: %s, %d, %.2f", person.name.c_str(), person.age, person.height);

            //为了让发布频率，得调用下面函数
            rate.sleep();

            //suggestion
            ros::spinOnce();

        }
    
    return 0;
}
