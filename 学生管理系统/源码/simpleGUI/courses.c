#include "courses.h"

void coursesmenu(int selection)
{
	if (tmp && isworking)
	{
		if (selection == 1)
			isworking = 21;
		if (selection == 2)
		{
			search[0] = '\0';
			isworking = 22;
		}
		if (selection == 3)
		{
			search[0] = '\0';
			isworking = 23;
		}
		if (selection == 4)
			isworking = 20;
	}
}
void showcourseinterface()
{
	showcourses(cnow, 1);
	drawpageselector(2);
}
void showcourseaddinterface()
{
	showcourseinfo();
	strcpy(status, "adding course");
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("取消")*0.9, winheight / 10, TextStringWidth("取消")*1.8, 1.0 / 3, "取消"))
	{
		isworking = tmp = 20;
		sprintf(status, "%d records at all", allcourses);
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("确认")*2.7, winheight / 10, TextStringWidth("确认")*1.8, 1.0 / 3, "确认"))
	{
		int a = cnumberisexist(addcoursenumber);
		if (strcmp(addcoursenumber, "") == 0 || strcmp(addcoursename, "") == 0)
			strcpy(status, "The course number and name cannot be empty！！！");
		else if (a == 1)
			strcpy(status, "The course already exists！！！");
		else
		{
			course *p = createcoursenode();
			strcpy(p->number, addcoursenumber);
			strcpy(p->coursename, addcoursename);
			p->next = chead->next;
			chead->next = p;
			isworking = tmp = 20;
			allcourses++;
			if (allcourses % 10 == 0) allcpages = allcourses / 10;
			else allcpages = allcourses / 10 + 1;
			if (nowcpage == 0) nowcpage = 1;
			sprintf(status, "%d records at all", allcourses);
		}
	}
}
void showcoursedeleteinterface()
{
	strcpy(status, "Please enter the course's number or name");
	SetPenColor("Black");
	drawLabel(winwidth / 2 - 6 * GetFontHeight() - TextStringWidth("删除学生"), winheight / 2 + GetFontHeight() * 0.7, "删除课程");
	textbox(GenUIID(0), winwidth / 2 - 5 * GetFontHeight(), winheight / 2, 2.5, 1.0 / 3, search, sizeof(search));
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("取消")*0.9, winheight / 7, TextStringWidth("取消")*1.8, 1.0 / 3, "取消"))
	{
		isworking = tmp = 20;
		sprintf(status, "%s", "Delete cancelled");
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("删除")*2.7, winheight / 7, TextStringWidth("删除")*1.8, 1.0 / 3, "删除"))
	{
		course *p = searchcourse(search);
		if (p)
		{
			coursedelete(p);
			allcourses--;
			changepageselector(2);                    //修改翻页器
			strcpy(status, "Deleted successfully");
			isworking = tmp = 20;
		}
		else strcpy(status, "No records found");
	}
}
void showcoursesearchinterface()
{
	strcpy(status, "Please enter the course's number or name");
	SetPenColor("Black");
	drawLabel(winwidth / 2 - 6 * GetFontHeight() - TextStringWidth("搜索学生"), winheight / 2 + GetFontHeight() * 0.7, "搜索课程");
	textbox(GenUIID(0), winwidth / 2 - 5 * GetFontHeight(), winheight / 2, 2.5, 1.0 / 3, search, sizeof(search));
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("取消")*0.9, winheight / 7, TextStringWidth("取消")*1.8, 1.0 / 3, "取消"))
	{
		isworking = tmp = 20;
		sprintf(status, "%s", "Search cancelled");
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("搜索")*2.7, winheight / 7, TextStringWidth("搜索")*1.8, 1.0 / 3, "搜索"))
	{
		isworking = 24;
		nowselectedcourse = searchcourse(search);
	}
}
void showcoursesearchresultinterface()
{
	showcoursebox(0, NULL);
	if (nowselectedcourse)	showcoursebox(1, nowselectedcourse);
	else strcpy(status, "No courses found");
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("返回")*0.9, winheight / 7, TextStringWidth("返回")*1.8, 1.0 / 3, "返回"))
		isworking = 23;
}
void showcoursereviseinterface()
{
	showcourseinfo();
	strcpy(status, "revising course");
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("取消")*0.9, winheight / 10, TextStringWidth("取消")*1.8, 1.0 / 3, "取消"))
	{
		isworking = tmp = 20;
		sprintf(status, "%d records at all", allcourses);
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("确认")*2.7, winheight / 10, TextStringWidth("确认")*1.8, 1.0 / 3, "确认"))
	{
		if (strcmp(addcoursenumber, "") == 0 || strcmp(addcoursename, "") == 0)
			strcpy(status, "The course number and name cannot be empty！！！");
		else
		{
			student *t = Lhead->next;
			while (t)
			{
				course *q = t->c->next;
				while (q)
				{
					if (strcmp(q->number, nowselectedcourse->number) == 0)
					{
						strcpy(q->number, addcoursenumber);
						strcpy(q->coursename, addcoursename);
						break;
					}
					q = q->next;
				}
				t = t->next;
			}
			strcpy(nowselectedcourse->number, addcoursenumber);
			strcpy(nowselectedcourse->coursename, addcoursename);
			isworking = tmp = 20;
			sprintf(status, "%d records at all", allcourses);
		}
	}
}
void showcourselist()
{
	SetPenColor("Black");
	drawLabel(winwidth / 2 - TextStringWidth(nowselectedcourse->coursename) / 2, winheight - 4 * GetFontHeight(), nowselectedcourse->coursename);
	showxuanke(snow, nowselectedcourse->number);
	drawpageselector(3);
	if (button(GenUIID(0), winwidth * 3 / 4 - TextStringWidth("返回")*0.9, winheight / 8, TextStringWidth("返回")*1.8, 1.0 / 3, "返回"))
	{
		isworking = 20;
		fromcourse = 0;
	}
}
void showcoursestatistics()
{
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("返回")*0.9, winheight / 7, TextStringWidth("返回")*1.8, 1.0 / 3, "返回"))
		isworking = tmp = 20;
	SetPenColor("Black");
	int a[9] = { 0 };
	int all = 0;
	student *q = nowselectedcourse->s->next;
	while (q)
	{
		if (q->score < 60) a[0]++;
		else if (q->score < 65) a[1]++;
		else if (q->score < 70) a[2]++;
		else if (q->score < 75) a[3]++;
		else if (q->score < 80) a[4]++;
		else if (q->score < 85) a[5]++;
		else if (q->score < 90) a[6]++;
		else if (q->score < 95) a[7]++;
		else if (q->score <= 100) a[8]++;
		all++;
		q = q->next;
	}
	double fH = GetFontHeight();
	double h = fH * 2;
	double x = winwidth * 2 / 5;
	double y = winheight - 16 * fH;
	int i = 0;
	char abc[9][10] = { "<60分:","60-64分:","65-69分:" ,"70-74分:" ,"75-79分:" ,"80-84分:" ,"85-89分:" ,"90-94分:" ,"95-100分:" };
	char tmp[10];
	drawLabel(x - fH / 2 - TextStringWidth("编号:"), y + 2 * h, "编号:");
	drawLabel(x, y + 2 * h, nowselectedcourse->number);
	drawLabel(x + 0.75 * 2 - fH / 2 - TextStringWidth("编号:"), y + 2 * h, "课程:");
	drawLabel(x + 0.75 * 2, y + 2 * h, nowselectedcourse->coursename);
	while (i < 9)
	{
		drawLabel(x - fH / 2 - TextStringWidth(abc[i]), y - i * h, abc[i]);
		itoa(a[i], tmp, 10);
		drawLabel(x, y - i * h, tmp);
		sprintf(tmp, "%.2f%%", all != 0 ? 100.0*a[i] / all : 0);
		drawLabel(x + 0.75 * 2 - fH / 2 - TextStringWidth("分数:"), y - i * h, "比例:");
		drawLabel(x + 0.75 * 2, y - i * h, tmp);
		i++;
	}
}
void showcoursedeletinginterface()
{
	strcpy(status, "Do you want to delete it?");
	if (button(GenUIID(0), winwidth - 2.5, 0, 2.5 / 2, 1.0 / 3, "Yes"))
	{
		isdeleting = 0;
		coursedelete(nowselectedcourse);
		allcourses--;
		changepageselector(2);
		strcpy(status, "Deleted successfully");
	}
	if (button(GenUIID(0), winwidth - 0.5*2.5, 0, 2.5 / 2, 1.0 / 3, "No"))
	{
		isdeleting = 0;
		sprintf(status, "Detete cancelled");
	}
}
void showcourseinfo()
{
	double fH = GetFontHeight();
	double h = fH * 2; // 控件高度
	double w = winwidth / 4; // 控件宽度
	double x = winwidth / 5;
	double y = winheight - 4 * fH - h;
	SetPenColor("Black");
	drawLabel(x + 0.75*w - fH / 2 - TextStringWidth("编号"), y - 5 * h + fH * 0.7, "编号");
	textbox(GenUIID(0), x + 0.75*w, y - 5 * h, w, h, addcoursenumber, sizeof(addcoursenumber));
	if (button(GenUIID(0), x + 1.75*w, y - 5 * h, w / 6, h, "复制"))
		strcpy(clipboard, addcoursenumber);
	if (button(GenUIID(0), x + 1.75*w+ w / 6, y - 5 * h, w / 6, h, "粘贴"))
		if (strcmp(clipboard, "") != 0)
			strcpy(addcoursenumber, clipboard);

	drawLabel(x + 0.75*w - fH / 2 - TextStringWidth("名称"), y - 7 * h + fH * 0.7, "名称");
	textbox(GenUIID(0), x + 0.75*w, y - 7 * h, w, h, addcoursename, sizeof(addcoursename));
	if (button(GenUIID(0), x + 1.75*w, y - 7 * h, w / 6, h, "复制"))
		strcpy(clipboard, addcoursename);
	if (button(GenUIID(0), x + 1.75*w + w / 6, y - 7 * h, w / 6, h, "粘贴"))
		if (strcmp(clipboard, "") != 0)
			strcpy(addcoursename, clipboard);
}