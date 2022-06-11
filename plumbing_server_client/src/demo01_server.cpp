#include "ros/ros.h"
#include "plumbing_server_client/AddInts.h"
/* ctrl shift + A
  服务端实现：解析客户端提交的数据，并运算再产生响应
      1. 包含头文件
      2. 初始化ros节点
      3. 创建节点句柄
      4. 创建一个服务对象
      5. 处理请求并产生响应
      6. spin(),如果是while 写spinonce() 
*/


//有请求对象，响应对象，传递给回调函数
//类型是当前功能包下面的。request 类型， &是引用
bool doNums(plumbing_server_client::AddInts::Request  &request,
            plumbing_server_client::AddInts::Response &response){
    //请求和响应以参数的形式传入近来，可以处理请求，就是把两个数字解析出来，求和设置进response
    //1. 处理请求,analyse the number 
    int num1 = request.num1;
    int num2 = request.num2;
    ROS_INFO("the data of recive: num1 = %d, num2 = %d", num1,num2);
    //2. 组织响应
    int sum = num1 + num2;
    response.sum = sum;
    ROS_INFO("the sum of result: sum = %d", sum);
    return true;// 处理请求成功
}


int main(int argc, char  *argv[])
{
    setlocale(LC_ALL,"");
    
 //       2. 初始化ros节点
 ros::init(argc,argv,"heiShui"); //节点名称续造保持唯一
 //       3. 创建节点句柄
 ros::NodeHandle nh;
 //       4. 创建一个服务对象 # doNums 回调函数，返回bool类型 addInt is topic name
 ros::ServiceServer server = nh.advertiseService("addInts",doNums);
 
 ROS_INFO("服务器端启动");
 //       5. 处理请求并产生响应
 //       6. spin(),如果是while 写spinonce()
 ros::spin();
    return 0;
}
