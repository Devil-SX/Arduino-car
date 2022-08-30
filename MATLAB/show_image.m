%和串口半工通讯
%MATLAB作为上位机，接收并显示来自串口的数据
%还没设置退出接口

clear;

%黑底绿线，彰显极客风
fig  = figure('Color','black');
set(gca,'color','black');

global iter;
global last_data;
last_data = 0;
iter = 1;

%串口定义
port = "COM4";
baudrate = 9600;
device = serialport(port,baudrate);

%定义回调函数
configureCallback(device,"terminator",@serial_callback);

%定义回调函数
function serial_callback(s,~)
global iter;
global last_data;
string = readline(s);
data = str2double(string);
disp(data);
%如果是有效数字，显示它
if ~isnan(data)
    hold on;
    linewidth = 0.2 + 2/(1+exp(-10*abs(data-last_data)));%变化越剧烈线越粗
    plot([iter,iter+1],[last_data,data],"Color","green","LineWidth",linewidth);
    iter = iter + 1;
    last_data = data;
end
end