#include "ros/ros.h"
#include "std_msgs/String.h"

//订阅的消息是std_msgs/String.h"下的消息
//const std_msgs::String::ConstPtr 指的是
//我现在拿到的是传入消息的是std_msgs::String类型，传入的参数是常量参数的引用ConstPtr
void doMsg(const std_msgs::String::ConstPtr & msg){
    //通过msg获取并操作订阅到的数据 msg 是一个指针类型.通过箭头的方式调用过来，我们需要c_str字符串
    ROS_INFO("翠花订阅的数据:%s",msg->data.c_str());
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    //发布方实现：
        //1.包含头文件
        //ROS 中文本类型 --- "std_msgs/String.h"
    // 2.初始化 ROS 节点我要把相亲对象翠花创建出来，不能重名，保证节点的唯一性
    ros::init(argc, argv,"cuihua");
    // 3.创建节点句柄，
    ros::NodeHandle nh;
    // 4.创建订阅者对象； 下面的10,缓存数据的长度，并且依赖于句柄 doMsg 回调函数，上面定义下void
    //050: 解耦和 体现，即使总不同的语言，也可以进行数据交换，话题要一致
    ros::Subscriber sub = nh.subscribe("house", 10,doMsg);
    // 5.编写发布逻辑并发布数据
    //spin 回头,到这步就得用回调函数doMsg，频繁执行
    ros::spin();
    ROS_INFO("spin后的语句");

    return 0;
}