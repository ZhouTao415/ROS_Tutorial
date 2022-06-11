#include "ros/ros.h"
#include "plumbing_pub_sub/Person.h"
/*
    订阅方:订阅的信息
          1.包含头文件
              # #include "plumbing_pub_sub/Person.h"
          2.初始化ROS节点
          3.创建节点句柄
          4.创建订阅者对象
          5.处理订阅的数据
          6。调用spin（）函数
*/
//b包订阅到的数据传进来，参数声明这里面（const 包名：：Person::对应常量指针的引用）
void doPerson(const plumbing_pub_sub::Person::ConstPtr  & person){
    ROS_INFO("订阅人的信息:  %s, %d, %.2f", person->name.c_str(), person->age, person->height);

}
int main(int argc, char  *argv[])
{
        //订阅方:订阅的信息
        setlocale(LC_ALL,"");
        ROS_INFO("订阅方实现");
        //2.初始化ROS节点
        ros::init(argc, argv,"jiaZhang");
        //3.创建节点句柄
        ros::NodeHandle nh;
        //4.创建订阅者对象,话题名称，队列长度，回调函数(《处理订阅到的数据)
        ros::Subscriber sub = nh.subscribe("liaotian", 10, doPerson);
        //5.处理订阅的数据
        //6.调用spin（）函数
        ros::spin();
    return 0;
}
