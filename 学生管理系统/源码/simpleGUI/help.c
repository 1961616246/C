#include"help.h"

void showhelp()
{
	double x = winwidth / 5;
	double y = winheight * 6 / 7;
	double h = GetFontHeight() * 4;
	drawLabel(x, y, "1st step:Open a local file or create a new file");
	drawLabel(x, y = y - h, "2nd step:You can revise the students' and courses' information");
	drawLabel(x, y = y - h, "3rd step:You can search student with his/her id or name or you can search a specific course");
	drawLabel(x, y = y - h, "4th step:Don't forget to save your file!");
}
void showabout()
{
	double x = winwidth / 5;
	double y = winheight * 2 / 3;
	double h = GetFontHeight() * 4;
	drawLabel(x, y, "Author: Li Jiahao");
	drawLabel(x, y - h, "Email: 1961616246@qq.com");
}
void helpmenu(int selection)
{
	if (selection > 0) guiling();
	if (selection == 1)
	{
		tmp = (isworking == 2) ? tmp : isworking;
		ishelping = 1;
	}
	if (selection == 2)
	{
		tmp = (isworking == 2) ? tmp : isworking;
		isabouting = 1;
	}
}
void drawhelpinginterface()
{
	isworking = 2;
	showhelp();                    //展示内容
	strcpy(status, "Showing help");
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("我知道了"), winheight / 7, TextStringWidth("我知道了")*1.8, 0.33333333333333333, "我知道了"))
	{
		isworking = tmp;
		ishelping = 0;
	}
}
void drawaboutinginterface()
{
	isworking = 2;
	showabout();                  //展示内容
	strcpy(status, "Showing about us");
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("返回"), winheight / 7, TextStringWidth("返回")*1.8, 0.33333333333333333333, "返回"))
	{
		isworking = tmp;
		isabouting = 0;
	}
}