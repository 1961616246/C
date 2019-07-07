#include"students.h"

void studentsmenu(int selection)
{
	if (isworking && tmp)
	{
		if (selection == 1)
		{
			isworking = 11;
			addid[0] = addname[0] = addmajor[0] = addphonenumber[0] = '\0';
			int i = 0;
			for (i = 0; i < 12; i++)
				addcourses[i][0] = addscores[i][0] = '\0';
		}
		if (selection == 2)
		{
			search[0] = '\0';
			isworking = 15;
		}
		if (selection == 3)
		{
			search[0] = '\0';
			isworking = 12;
		}
		if (selection == 4)
			isworking = tmp = 1;
	}
}
void showstudentinterface()
{
	showstudents(now, 1);
	drawpageselector(1);
}
void showstudentaddinterface()
{
	showcoloums();
	strcpy(status, "Adding student");
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("取消")*0.9, winheight / 10, TextStringWidth("取消")*1.8, 0.3333333333333333, "取消"))
	{
		isworking = tmp = 1;
		sprintf(status, "%d records at all", allrecords);
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("确认")*2.7, winheight / 10, TextStringWidth("确认")*1.8, 0.33333333333333333, "确认"))
	{
		int a = idisexist(addid);
		int b = nameisexist(addname);
		if (strcmp(addid, "") == 0 || strcmp(addname, "") == 0)
			strcpy(status, "The student number and name cannot be empty！！！");
		else if (a == 1 || b == 1)
			strcpy(status, "The student already exists！！！");
		else
		{
			if (addtolinkedlist() == 0)
				strcpy(status, "The courses does not exist!!!");
			else
			{
				isworking = tmp = 1;
				sprintf(status, "%d records at all", allrecords);
			}
		}
	}
}
void showstudentsearchinterface()
{
	strcpy(status, "Please enter the student's id, name, major or phonenumber");
	SetPenColor("Black");
	drawLabel(winwidth / 2 - 6 * GetFontHeight() - TextStringWidth("搜索学生"), winheight / 2 + GetFontHeight() * 0.7, "搜索学生");
	textbox(GenUIID(0), winwidth / 2 - 5 * GetFontHeight(), winheight / 2, 2, 0.3333333333333333333333, search, sizeof(search));
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("取消")*0.9, winheight / 7, TextStringWidth("取消")*1.8, 0.3333333333333333333, "取消"))
	{
		isworking = tmp = 1;
		sprintf(status, "%s", "Search cancelled");
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("搜索")*2.7, winheight / 7, TextStringWidth("搜索")*1.8, 0.333333333333333333333, "搜索"))
	{
		isworking = 13;
		searchstudent(search);
	}
}
void showstudentsearchresultinterface()
{
	int i = 0;
	showsearchresult(snow);
	drawpageselector(3);              //画翻页器
	if (searchresult[0] == NULL) strcpy(status, "No records found");
	else sprintf(status, "Find %d records", allsearchresults);
	if (button(GenUIID(0), winwidth * 3 / 4 - TextStringWidth("返回")*0.9, winheight / 8, TextStringWidth("返回")*1.8, 0.333333333333333333, "返回"))
	{
		isworking = 12;
		fromsearch = 0;
	}
}
void showstudentreviseinterface()
{
	showcoloums();
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("取消")*0.9, winheight / 10, TextStringWidth("取消")*1.8, 0.3333333333333333333, "取消"))
	{
		if (fromdetail == 1)
			isworking = 19;
		else if (fromsearch == 1)
			isworking = 13;
		else if (fromcourse == 1)
			isworking = 28;
		else isworking = tmp = 1;
		sprintf(status, "%d records at all", allrecords);
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("确认")*2.7, winheight / 10, TextStringWidth("确认")*1.8, 0.33333333333333333333, "确认"))
	{
		int flag = 1;
		int i = 0;
		course *p = nowselectedstudent->c;
		for (i = 0; i < 12; i++)
		{
			if (strcmp(addcourses[i], "") != 0)
			{
				if (courseisexist(addcourses[i]) == NULL)
					flag = 0;
			}
		}
		if (flag == 1)
		{
			for (i = 0; i < 12; i++)
			{
				if (strcmp(addcourses[i], "") != 0)
				{
					course *c = courseisexist(addcourses[i]);
					student *t;
					t = c->s->next;
					while (t&&strcmp(t->id, nowselectedstudent->id))
						t = t->next;
					if (t == NULL)
					{
						student *tmp = createstudentnode();
						tmp->next = c->s->next;
						c->s->next = tmp;
						t = tmp;
					}
					strcpy(t->id, addid);
					strcpy(t->name, addname);
					strcpy(t->major, addmajor);
					strcpy(t->phonenumber, addphonenumber);
					t->score = atoi(addscores[i]);
					if (p->next)
					{
						p->next->score = atoi(addscores[i]);
						strcpy(p->next->coursename, addcourses[i]);
					}
					else
					{
						course *q = createcoursenode();
						q->next = NULL;
						strcpy(q->number, c->number);
						strcpy(q->coursename, addcourses[i]);
						p->next = q;
						q->score = atoi(addscores[i]);
					}
					p = p->next;
				}
			}
			strcpy(nowselectedstudent->id, addid);
			strcpy(nowselectedstudent->name, addname);
			strcpy(nowselectedstudent->major, addmajor);
			strcpy(nowselectedstudent->phonenumber, addphonenumber);
			if (fromdetail == 1)
				isworking = 19;
			else if (fromsearch == 1)
				isworking = 13;
			else if (fromcourse == 1)
				isworking = 28;
			else isworking = tmp=1;
			sprintf(status, "%d records at all", allrecords);
		}
		else	strcpy(status, "The course does not exist!!!");
	}
}
void showstudentdeleteinterface()
{
	strcpy(status, "Please enter the student's id");
	SetPenColor("Black");
	drawLabel(winwidth / 2 - 6 * GetFontHeight() - TextStringWidth("删除学生"), winheight / 2 + GetFontHeight() * 0.7, "删除学生");
	textbox(GenUIID(0), winwidth / 2 - 5 * GetFontHeight(), winheight / 2, 2, 0.3333333333333333333333, search, sizeof(search));
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("取消")*0.9, winheight / 7, TextStringWidth("取消")*1.8, 0.333333333333333333, "取消"))
	{
		isworking = tmp = 1;
		sprintf(status, "%s", "Delete cancelled");
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("删除")*2.7, winheight / 7, TextStringWidth("删除")*1.8, 0.3333333333333333333, "删除"))
	{
		searchstudent(search);
		if (searchresult[0])
		{
			studentdelete(searchresult[0]);
			allrecords--;
			changepageselector(1);                           //修改翻页器
			strcpy(status, "Deleted successfully");
			isworking = tmp = 1;
		}
		else strcpy(status, "No records found");
	}
}
void showstudentdeletinginterface()
{
	strcpy(status, "Do you want to delete it?");
	if (button(GenUIID(0), winwidth - 2, 0, 1, 0.33333333333333333, "Yes"))
	{
		if (fromcourse == 1)
		{
			int i;
			for (i = 0; i < 10000; i++)
				if (searchresult[i] == nowselectedstudent)
					break;
			int j;
			for (j = i; j < 9999; j++)
				searchresult[j] = searchresult[j + 1];
		}
		isdeleting = 0;
		studentdelete(nowselectedstudent);
		allrecords--;
		changepageselector(1);
		strcpy(status, "Deleted successfully");
	}
	if (button(GenUIID(0), winwidth - 1, 0, 1, 0.33333333333333333, "No"))
	{
		isdeleting = 0;
		sprintf(status, "Detete cancelled");
	}
}
void showcoloums()
{
	double fH = GetFontHeight();
	double h = fH * 2; // 控件高度
	double w = winwidth / 4; // 控件宽度
	double x = winwidth / 5;
	double y = winheight - 4 * fH - h;
	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("学号"), y - 1.2*h + fH * 0.7, "学号");
	textbox(GenUIID(0), x, y - 1.2*h, w*2/3, h, addid, sizeof(addid));
	if (button(GenUIID(0), x+w*2/3, y - 1.2*h, w/6, h, "复制"))
		strcpy(clipboard, addid);
	if (button(GenUIID(0), x + w * 5 / 6, y - 1.2*h, w / 6, h, "粘贴"))
		if(strcmp(clipboard,"")!=0)
			strcpy(addid,clipboard);

	drawLabel(x + 1.5*w - fH / 2 - TextStringWidth("姓名"), y - 1.2*h + fH * 0.7, "姓名");
	textbox(GenUIID(0), x + 1.5*w, y - 1.2*h, w*2/3, h, addname, sizeof(addname));
	if (button(GenUIID(0), x +1.5*w+ w * 2 / 3, y - 1.2*h, w / 6, h, "复制"))
		strcpy(clipboard, addname);
	if (button(GenUIID(0), x +1.5*w+w * 5 / 6, y - 1.2*h, w / 6, h, "粘贴"))
		if (strcmp(clipboard, "") != 0)
			strcpy(addname, clipboard);

	drawLabel(x - fH / 2 - TextStringWidth("专业"), y - 3.6*h + fH * 0.7, "专业");
	textbox(GenUIID(0), x, y - 3.6*h, w, h, addmajor, sizeof(addmajor));
	if (button(GenUIID(0), x  + w * 2 / 3, y - 3.6*h, w / 6, h, "复制"))
		strcpy(clipboard, addmajor);
	if (button(GenUIID(0), x  + w * 5 / 6, y - 3.6*h, w / 6, h, "粘贴"))
		if (strcmp(clipboard, "") != 0)
			strcpy(addmajor, clipboard);

	drawLabel(x + 1.5*w - fH / 2 - TextStringWidth("手机号码"), y - 3.6*h + fH * 0.7, "手机号码");
	textbox(GenUIID(0), x + 1.5*w, y - 3.6*h, w, h, addphonenumber, sizeof(addphonenumber));
	if (button(GenUIID(0), x + 1.5*w + w * 2 / 3, y - 3.6*h, w / 6, h, "复制"))
		strcpy(clipboard, addphonenumber);
	if (button(GenUIID(0), x + 1.5*w + w * 5 / 6, y - 3.6*h, w / 6, h, "粘贴"))
		if (strcmp(clipboard, "") != 0)
			strcpy(addphonenumber, clipboard);

	int i = 0;
	char abc[10] = { "" };
	for (i = 0; i < 6; i++)
	{
		sprintf(abc, "课程%d:", i + 1);
		drawLabel(x - fH / 2 - TextStringWidth(abc), y - 5.4*h - 1.2*i*h + fH * 0.7, abc);
		textbox(GenUIID(i), x, y - 5.4*h - 1.2*i*h, w * 2 / 3, h, addcourses[i], sizeof(addcourses[i]));
		drawLabel(x + 0.88*w - fH / 2 - TextStringWidth("分数:"), y - 5.4*h - 1.2*i*h + fH * 0.7, "分数:");
		textbox(GenUIID(i), x + 0.88*w, y - 5.4*h - 1.2*i*h, w / 5, h, addscores[i], sizeof(addscores[i]));
	}
	for (i = 0; i < 6; i++)
	{
		sprintf(abc, "课程%d:", i + 7);
		drawLabel(x + 1.5*w - fH / 2 - TextStringWidth(abc), y - 5.4*h - 1.2*i*h + fH * 0.7, abc);
		textbox(GenUIID(i), x + 1.5*w, y - 5.4*h - 1.2*i*h, w * 2 / 3, h, addcourses[i + 6], sizeof(addcourses[i + 6]));
		drawLabel(x + 0.88*w + 1.5*w - fH / 2 - TextStringWidth("分数:"), y - 5.4*h - 1.2*i*h + fH * 0.7, "分数:");
		textbox(GenUIID(i), x + 0.88*w + 1.5*w, y - 5.4*h - 1.2*i*h, w / 5, h, addscores[i + 6], sizeof(addscores[i + 6]));
	}
}
void showdetails(student *p)
{
	double fH = GetFontHeight();
	double h = fH * 2; // 控件高度
	double w = winwidth / 4; // 控件宽度
	double x = winwidth / 5;
	double y = winheight - 8 * fH;
	strcpy(status, "Showing details");
	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("学号:"), y, "学号:");
	drawLabel(x, y, p->id);
	drawLabel(x + 1.5*w - fH / 2 - TextStringWidth("姓名:"), y, "姓名:");
	drawLabel(x + 1.5*w, y, p->name);
	drawLabel(x - fH / 2 - TextStringWidth("专业:"), y - 1.5*h, "专业:");
	drawLabel(x, y - 1.5*h, p->major);
	drawLabel(x + 1.5*w - fH / 2 - TextStringWidth("手机号码:"), y - 1.5*h, "手机号码:");
	drawLabel(x + 1.5*w, y - 1.5*h, p->phonenumber);
	int i = 0;
	char abc[10] = { "" };
	course *q = p->c->next;
	while (q)
	{
		sprintf(abc, "课程%d:", i + 1);
		drawLabel(x - fH / 2 - TextStringWidth(abc), y - 3 * h - 1.5*i*h, abc);
		drawLabel(x, y - 3 * h - 1.5*i*h, q->coursename);
		itoa(q->score, abc, 10);
		drawLabel(x + 0.75*w - fH / 2 - TextStringWidth("分数:"), y - 3 * h - 1.5*i*h, "分数:");
		drawLabel(x + 0.75*w, y - 3 * h - 1.5*i*h, abc);
		q = q->next;
		i++;
		if (i >= 6) break;
	}
	i = 0;
	while (q)
	{
		sprintf(abc, "课程%d:", i + 7);
		drawLabel(x + 1.5*w - fH / 2 - TextStringWidth(abc), y - 3 * h - 1.5*i*h, abc);
		drawLabel(x + 1.5*w, y - 3 * h - 1.5*i*h, q->coursename);
		itoa(q->score, abc, 10);
		drawLabel(x + 2.25*w - fH / 2 - TextStringWidth("分数:"), y - 3 * h - 1.5*i*h, "分数:");
		drawLabel(x + 2.25*w, y - 3 * h - 1.5*i*h, abc);
		q = q->next;
		i++;
		if (i >= 6) break;
	}
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("取消")*0.9, winheight / 10, TextStringWidth("取消")*1.8, h, "取消"))
	{
		sprintf(status, "%d records at all", allrecords);
		if (fromsearch == 1) isworking = 13;
		else if (fromcourse == 1) isworking = 28;
		else isworking = tmp = 1;
		fromdetail = 0;
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("修改")*2.7, winheight / 10, TextStringWidth("修改")*1.8, h, "修改"))
	{
		fromdetail = 1;
		nowselectedstudent = p;
		readytosearch();
	}
}
