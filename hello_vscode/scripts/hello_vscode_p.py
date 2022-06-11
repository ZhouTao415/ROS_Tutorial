# python 的解释器
#! /usr/bin/env python

#导包
import rospy
#入口
if __name__ == "__main":
    #初始化ros节点
    rospy.init_node("hello_p")
    #输出日志
    rospy.loginfo("hello vsocode! 这是python！")