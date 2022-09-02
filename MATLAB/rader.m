%半双工雷达

clear;

%黑底绿线，彰显极客风
fig  = figure('Color','black');
polarscatter(0,0);
set(gca,'color','black');


%全局变量
global angle;%角度制
angle = 0;
global angles;
angles = [];
global isadd;
isadd = 1;%增加为1，减少为-1
global data;
data = [];

%串口定义
port = "COM9";
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
global angles;
global isadd;
global data;
disp("Get Recall");
string = readline(s);
distance = str2double(string);
disp(distance);

%记录数据
if ~isnan(distance)
    data = [data distance];
else
    data = [data 0];
end
angles = [angles angle];

%绘制雷达图
polarscatter(angles*pi/180, data,10,"filled",'MarkerFaceColor',"green");
set(gca,'color','black');
hold on;
polarplot([angle angle]*pi/180,[0 max(data)],'Color','green');
hold off;

%发送新指令
angle = angle + isadd;
isadd = isadd-2*(angle==180)+2*(angle==0);
writeline(s,int2str(angle));%发送指令
disp(angle);

%掉头停顿一下
if((angle==179&&isadd==-1)||(angle==1&&isadd==1))
    disp('start waiting');
    angles = [];
    data = [];
    pause(2);
    disp('end waiting');
end

end