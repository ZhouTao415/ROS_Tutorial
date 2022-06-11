#! /usr/bin/env python
## 制定解释器
"""
    Python 版 HelloWorld

"""
#1.导包
import rospy
#2 编写主入口
if __name__ == "__main__":
    #初始化ros节点
    rospy.init_node("Hello_p")
    #输出日志
    rospy.loginfo("Hello World by python!!!!")
