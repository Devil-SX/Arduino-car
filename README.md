# Arduino智能小车

## 硬件平台

- 智宇科技 ZY08ARDUINO 智能小车

## 包含模块驱动

主目录下放着一些编写的模块驱动代码

- **IMove**控制小车移动模块
- **IBeep**蜂鸣器模块
- **IServo**舵机模块
- **IUltrasound**超声波模块
- **IRremote**红外遥控模块by智宇科技

## 示例程序

"main_files"里放着一些写好的主文件，复制替换car.ino使用即可

- **红外线遥控**通过红外线遥控器控制小车前、后、左、右、停运动
- **超声波测试**使用超声波模块读取距离，并打印在串口
- **超声波跟踪**开启跟踪模式后，前方有物体靠近，靠太近后退
- **舵机测试**旋转舵机功能测试
- **人工智障自动瞎走**未完成，表现十分智障【BUG】
- **MATLAB联动雷达**Arduino做下位机，MATLAB做上位机，超声波扫描距离并在MATLAB上显示【BUG】

"MATLAB"放着MATLAB作为上位机与小车联动的MATLAB文件

- **show_image.m**半工，MATLAB上位机实现类似Arduino串口绘图器的功能（可搭配“超声波测试”测试程序）
- **rader.m**半双工，MATLAB上位机实现雷达扫描（关联“MATLAB联动雷达”）【BUG】