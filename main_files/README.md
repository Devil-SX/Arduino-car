- **红外线遥控**通过红外线遥控器控制小车前、后、左、右、停运动
- **超声波测试**使用超声波模块读取距离，并打印在串口
- **超声波跟踪**开启跟踪模式后，前方有物体靠近，靠太近后退
- **舵机测试_Iservo**旋转舵机功能测试
- **人工智障自动瞎走_IServo**未完成，表现十分智障【BUG】
- **MATLAB联动雷达_IServo**Arduino做下位机，MATLAB做上位机，超声波扫描距离并在MATLAB上显示【放弃维护】
- **MATLAB联动雷达_Servo**使用官方"Servo.h"库的版本

# 人工智障自动瞎走
红外线遥控器按"0“切换自动挡
1. 舵机旋转超声波模块扫描180°距离，并获取距离最远的角度，执行第二步
2. 如果该角度不在前方，旋转车身使其在前方，并返回第一步；如果在，执行第三步
3. 如果最远距离够远，前进；如果不够远，后退，返回第一步

# MATLAB联动雷达
MATLAB作为上位机，Arduino作为下位机，通过串口通信
## 工作循环
1. MATLAB向串口传输指定角度，同时等待Arduino回信
2. Arduino收到指定角度，舵机旋转至该角度，超声波模块测距，向串口传输距离，等待MATLAB回信
3. MATLAB收到距离，绘图显示，并改变角度返回第一步
## 其它
- 启动程序顺序是，先启动Arduino，再启动MATLAB程序
- 从工作循环上看，无论是Arduino还是MATLAB向对方发送信息，都能触发该循环从而初始化
- MATLAB在启动时会向Arduino发送一次角度以初始化，但该信息似乎Arduino并没有反应，因此初始化其实是通过下面实现的（待修改）
- Arduino会计算距离上一次向MATLAB发送距离的时间，若超出指定时间，则会重新发送一次
