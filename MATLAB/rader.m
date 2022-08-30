%半双工雷达

clear;

%黑底绿线，彰显极客风
fig  = figure('Color','black');
polarscatter(0,0);
set(gca,'color','black');


%全局变量
global angle;%角度制
angle = 0;
global isadd;
isadd = 1;%增加为1，减少为-1

%串口定义
port = "COM4";
baudrate = 9600;
device = serialport(port,baudrate);
device.Terminator

%定义回调函数
configureCallback(device,"terminator",@read_arduino);

%发送指令激活单片机
writeline(device,int2str(angle));
angle = angle + isadd;


%定义回调函数
function read_arduino(s,~)
global angle;
global isadd;
disp("Get Recall");
string = readline(s);
data = str2double(string);
disp(data);
%如果是有效数字，显示它
if ~isnan(data)
    hold on;
    polarscatter(angle*pi/180, data,"filled",'MarkerFaceColor',"green");
end
angle = angle + isadd;
isadd = isadd-2*(angle==180)+2*(angle==0);
writeline(s,int2str(angle));%发送指令
disp(angle);

%掉头停顿一下
if((angle==179&&isadd==-1)||(angle==1&&isadd==1))
    disp('start waiting');
    pause(10);
    disp('end waiting');
end

end