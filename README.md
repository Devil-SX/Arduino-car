# Arduino智能小车

## 硬件平台

- 智宇科技 ZY08ARDUINO 智能小车

## 包含模块驱动

主目录下放着一些编写的模块驱动代码

- **IMove**控制小车移动模块
- **IBeep**蜂鸣器模块
- **IServo**舵机模块【暂时放弃维护，改用Arduino官方的"Servo.h"库】
- **IUltrasound**超声波模块
- **IRremote**红外遥控模块by智宇科技

## 示例程序

"main_files"里放着一些写好的主文件，复制替换car.ino使用即可
"MATLAB"放着MATLAB作为上位机与小车联动的MATLAB文件