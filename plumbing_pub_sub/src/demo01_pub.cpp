#include "ros/ros.h"
#include "std_msgs/String.h"
#include<sstream>
/*
    发布方实现：
         1.包含头文件
           ROS 中文本类型 --- "std_msgs/String.h"

*/
int main(int argc, char *argv[])
{
    //解决乱码问题
    setlocale(LC_ALL, "");
   
    /*  3.1
       作用： ROS初始化函数 ros::init

       参数：
            1. argc   ----封装实参个数（n + 1 多的一个是文件自身）
            2. argv   ---封装参数的数组（字符串数组，把参数文件封装） rosrun 功能包 节点 参数传入（hello 123 。。。）
            3. name   ---为节点命名（唯一性）
            4. option ---节点启动选项
               返回值： void 空没有返回值
       
       使用：
           1. argc 与 argv 的使用
              如果按照ROS中特定格式传入实参，那么ROS可以加入使用，比如用来设置全局参数，给节点重命名...
            rosrun plumbing_pub_sub demo01_pub _length:=2
           2. option 的使用
              节点名称需要保证唯一，会导致一个问题： 同一个节点不能重复启动。
              结果：ROS 中当有重名的节点启动时，之前的的节点被关闭。
              需求：特定场景下，需要一个节点多次启动且能正常运行，怎么办？
              解决：设置启动项：ros::init_options::AnonymousName
                   当创建ROS节点时，会在用户自定义的节点名称后缀随机数，从而比避免重名问题。
     
    */

    // 2.初始化 ROS 节点（我要把相亲对象二狗子创建出来）
    ros::init(argc, argv,"erGouZi",ros::init_options::AnonymousName); //加一个随机数
    
    // 3.创建节点句柄
    ros::NodeHandle nh;
    // 4.创建发布者对象；

    /*  
      作用：创建发布者对象
      模板：被发布的消息的类型

      参数：
          1. 话题名称
          2. 队列长度
          3. latch（可选） 如果设置为ture， 会保存发布方的作后一条消息，并且
             新的定也u对象连接到发布方时，发布方将会将这条消息发送给订阅者

        使用：
           latch 设置为ture的作用？
           已静态地图发布为列，方案1 :  可以使用固定的发布频率发送地图数据，但是效率低，
           方案2： 可以将地图发布对象 latch 设置为图， 并且发布方只发送一次数据，每当订阅者连接时，
           将地图数据发送给订阅者（只发送一次），这样提高了数据的发送的效率。

    */
    //050: 解耦和 体现，即使总不同的语言，也可以进行数据交换，话题要一致

    ros::Publisher pub = nh.advertise<std_msgs::String>("house", 10,true);
    // 5.编写发布逻辑并发布数据
    //要求以10HZ的频率发布数据，并且文本后添加编号
    //先创建被发布的消息
    std_msgs::String msg;  
    //发布频率
    ros::Rate rate(1); //10 HZ  
    //设置编号
    int count = 0;
    //编写循环，循环中发布数据
    //休眠三秒钟
    ros::Duration(3).sleep();
    while (ros::ok()) //如果ros节点还活着就继续
    {
        
        //如果计数器 >=50 那么关闭节点
        if(count >= 5) {
            ros::shutdown();
        }
        count ++;//每循环一次++一次
        //msg.data = "hello";
        //实现字符串拼接数字， 创建stringstream 对象 << 拼接
        std::stringstream ss;
        ss << "hello ---> " << count;
        //我们还要把拼接出的数据取出来赋值给msg.data,将里面的数据提取为字符串，然后publish
        msg.data = ss.str();
        // if (count <= 10){
        //     pub.publish(msg);
        //     //添加日志,ss.str.这是一个字符串，string类型，%s对应c_str部分
        //     ROS_INFO("发布的数据是:%s", ss.str().c_str());
        // }
       



        pub.publish(msg);   
        //添加日志,ss.str.这是一个字符串，string类型，%s对应c_str部分
        ROS_INFO("发布的数据是:%s", ss.str().c_str());
        rate.sleep();//相当于水0.1s
        //官方建议，处理回调函数，一次
        ros::spinOnce();
        ROS_INFO("一轮回调执行完毕...");
    }
    //teminnal
    //publish 发布 rosrun plumbing_pub_sub demo01_pub
    //sublish 订阅 rostopic echo house （house 话题名称）


    return 0;  
}