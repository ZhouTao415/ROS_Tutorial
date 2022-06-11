#include "ros/ros.h"
#include "plumbing_head_src/hello.h"

int main(int argc, char  *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "hello_head_src");


    hello_ns::MyHello myHello;
    myHello.run();
    //目的：我虽然包含了 hello.h 但是我没办法链接到hello.cpp的
    return 0;
}
 