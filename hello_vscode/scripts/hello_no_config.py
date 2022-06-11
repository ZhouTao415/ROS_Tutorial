# python 的解释器
#! /usr/bin/env python 3
#现象：当不配置 CMakeList.txt 执行pytho年文件抛出异常：
# /usr/bin/env python ‘python’: No such file or directory
#原因—：当前 noetic使用Python3
#解决
     #1。直接声明解释器为python3(不建议)
     #2. 通过软链接将python 链接到python3上(建议) ：
     # sudo ln -s /usr/bin/python3 /usr/bin/python
     


#导包
import rospy
#入口
if __name__ == "__main":
    #初始化ros节点
    rospy.init_node("hello_p2")
    #输出日志
    rospy.loginfo("hello vsocode! 这是python！ no config")