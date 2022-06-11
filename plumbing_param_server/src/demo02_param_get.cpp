#include "ros/ros.h"


/* 
   参数查询，也有两套API

   实现：
    ros::NodeHandle --------------------------------------
        param(键,默认值) 
            存在，返回对应结果，否则返回默认值

        getParam(键,存储结果的变量)
            存在,返回 true,且将值赋值给参数2
            若果键不存在，那么返回值为 false，且不为参数2赋值

        getParamCached键,存储结果的变量)--提高变量获取效率 Cached 缓存
            存在,返回 true,且将值赋值给参数2
            若果键不存在，那么返回值为 false，且不为参数2赋值

        getParamNames(std::vector<std::string>)
            获取所有的键,并存储在参数 vector 中 

        hasParam(键)
            是否包含某个键，存在返回 true，否则返回 false

        searchParam(参数1，参数2)
            搜索键，参数1是被搜索的键，参数2存储搜索结果的变量

   

    ros::param -------------------------------------------
          
*/


int main(int argc, char  *argv[])
{
    //设置编码
    setlocale(LC_ALL,"");
    //初始化ROS节点
    ros::init(argc, argv,"get_param_c");
    //创建节点句柄
    ros::NodeHandle nh;

    //ros::NodeHandle --------------------------------------
    //1.param
        //param(键,默认值) 根据key来获取值
        //存在，返回对应结果，否则返回默认值
        // 用一个变量接受一下,查询key为radius的值，没有返回0. 5
        double radius = nh.param("radius", 0.5);
        ROS_INFO("radius = %.2f", radius);
    //2.getParam(键,存储结果的变量),返回值是bool
        //存在,返回 true,且将值赋值给参数2
        //若果键不存在，那么返回值为 false，且不为参数2赋值
        // double radius2 = 0.0;
        // bool result  = nh.getParam("radius", radius2);
        // if (result)
        // {
        //     ROS_INFO("获取的半径: %.2f", radius2);
        // } else{
        //     ROS_INFO("被查询的变量不存在");
        // }
    //3.getParamCached键,存储结果的变量)--提高变量获取效率 Cached 缓存
        //存在,返回 true,且将值赋值给参数2
        //若果键不存在，那么返回值为 false，且不为参数2赋值
        //我会看一下你之前师傅获取过，如果获取过，在缓存中直接拿，没有，远程调取
        //getParamCached 他的实现 与getParam 类似，只是底层性能上有提升，一般测试下，性能提升看不算出来。
        double radius2 = 0.0;
        bool result  = nh.getParamCached("radius", radius2);
        if (result)
        {
            ROS_INFO("获取的半径: %.2f", radius2);
        } else{
            ROS_INFO("被查询的变量不存在");
        }
    //4.getParamNames(std::vector<std::string>)
        //获取所有的键,并存储在参数 vector 中 
        //创建一个vector去保存这些names 使用的范型是string类型，叫做names
        std::vector<std::string> names;
        //开始调用
        nh.getParamNames(names);
        //遍历names，进而获取每个key name的名称
        //元素为name ，被遍历的是names
        for (auto &&name : names)
        {
            ROS_INFO("遍历的元素:%s",name.c_str()); //转化成c风格的字符串
        }

    //5.hasParam(键)
        //是否包含某个键，存在返回 true，否则返回 false
        bool flag1 = nh.hasParam("radius");
        bool flag2 = nh.hasParam("radiusxxxx");
        ROS_INFO("radius 存在么？ %d", flag1);
        ROS_INFO("radiusxxxx 存在么？ %d", flag2);
    //6. searchParam(参数1，参数2)
        //搜索键，参数1是被搜索的键，参数2存储搜索结果的变量
        //定义一个变量，得接收查询到的key name ，类型 string
        std::string key;
        nh.searchParam("radius", key);
        ROS_INFO("搜索结果:%s",key.c_str()); //radius存在，把其值封装进我们的key
        std::string key_x;
        nh.searchParam("radiusxxxy", key_x);//不存在
        ROS_INFO("搜索结果:%s",key_x.c_str());

    //ros::param -------------------------------------------
    double radius_param = ros::param::param("radius", 100.5);
    ROS_INFO("radius_param = %.2f", radius_param);
    double radius_param_fault = ros::param::param("radiusxcxc", 100.5);
    ROS_INFO("radius_paramxcxc = %.2f", radius_param_fault);

    std::vector<std::string> names_param;
    ros::param::getParamNames(names_param);
    for (auto &&name : names_param)
    {
        ROS_INFO("key: %s", name.c_str());
    }
    return 0;
}

