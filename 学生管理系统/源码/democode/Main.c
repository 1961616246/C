#include "global.h"
#include"includes.h"
#include"eventprocess.h"

void Main() 
{
	// 初始化窗口和图形系统
	SetWindowTitle("学生管理系统");
	tmp = 1;
    InitGraphics();
	// 获得窗口尺寸
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
	// 注册时间响应函数
	registerCharEvent(CharEventProcess); // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
}