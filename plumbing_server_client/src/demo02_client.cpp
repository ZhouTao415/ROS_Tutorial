#include "ros/ros.h"
#include "plumbing_server_client/AddInts.h"

/* ctrl shift + A
  客户端实现：提交两个整数，并处理响应结果
      1. 包含头文件
      2. 初始化ros节点
      3. 创建节点句柄
      4. 创建一个客户端对象
      5. 提交请求并处理响应
      6. spin(),如果是while 写spinonce() 
*/

    /* 
    实现参数的动态提交
    1. 格式 ： rosrun xxxx（package name） xxxx（node name） 12 34 
    2. 节点执行时，需要获取命令中的参数，并组织进 request，
    怎么获取参数 用argc argv 实现
    argc代表传入参数总量，第一个是指程序名，第二个是12，第三那个是34，所以argc是 3
     
     */

/* 
   问题 1：P71 
       如果先启动客户端，那么会请求异常
   需求
      如果先启动客户端，不要直接抛出异，而是挂起，等服务器启动后，在正常请求
   解决
      在ROS中内置了相关函数，这些函数可以让客户端启动后挂起，等待服务器启动
     函数1
       //客户端调用的
       client.waitForExistence();
     函数2
       //得传参数，被等待的服务的话题
       ros::service::waitForService("addInts");
 */


int main(int argc, char  *argv[])
{

     setlocale(LC_ALL,"");

    // 优化实现，获取命令中的参数
    if(argc != 3){
        ROS_INFO(" 提交的参数个数不对。");
        return 1;
    }
    //解析argv的元素2 和3

     // 2. 初始化ros节点
     ros::init(argc,argv,"daBao");
     // 3. 创建节点句柄
     ros::NodeHandle nh;
     // 4. 创建一个客户端对象,模板，话题名称
     ros::ServiceClient client = nh.serviceClient<plumbing_server_client::AddInts>("addInts");
     // 5. 提交请求并处理响应创建addInts object ::ai
     plumbing_server_client::AddInts ai;
     //5-1处理请求
       //解析argv的元素2 和3
     //ai.request.num1 = 100;
     //ai.request.num2 = 200; 
       //现在是字符串类型，转化为整型用atoi
     ai.request.num1 = atoi(argv[1]);
     ai.request.num2 = atoi(argv[2]);   
     //5-2处理响应,客户端访问服务器,call 穿service 对象 ai 进去就行，之后提交
     
     //问题 1解决 调用的时机是在创建完成客户端对象之后，发送请求之前：
     //判断服务器状态的函数
     //函数1
       //客户端调用的
       //client.waitForExistence();
     //函数2
       //得传参数，被等待的服务的话题
       ros::service::waitForService("addInts");


     bool flag = client.call(ai);

     if (flag)
     {
         ROS_INFO("Response sucess");
         //获取结果,封装在ai.response.sum里面
         ROS_INFO("Response result = %d", ai.response.sum);
     } else{
         ROS_INFO("handle fail ...");
     }
     //6. spin(),如果是while 写spinonce() 
    return 0;
}
