#pragma once
#include"showtable.h"

void showaddcoloum(double x, double y, int choose)
{

	SetPenColor("Black");
	double fH = GetFontHeight();
	double h = (winheight - 8 * fH) / 14;
	if (choose == 1)
	{
		double w = TextStringWidth("3180104460")*1.5;
		DrawBox(x, y, w, h);
		x = x + w;
		w = TextStringWidth("Li Jiahao")*1.8;
		DrawBox(x, y, w, h);
		x = x + w;
		w = TextStringWidth("机械电子工程") * 2.5;
		DrawBox(x, y, w, h);
		x = x + w;
		w = TextStringWidth("13588390245")*1.2;
		DrawBox(x, y, w, h);
		x = x + w;
		w = winwidth * 9 / 10 - x;
		DrawBox(x, y, w, h);
		if (button(GenUIID(0), x, y, w, h, "增加"))
		{
			isworking = 11;
			strcpy(addid, "");
			strcpy(addname, "");
			strcpy(addmajor, "");
			strcpy(addphonenumber, "");
			int i;
			for (i = 0; i < 12; i++)
			{
				strcpy(addcourses[i], "");
				strcpy(addscores[i], "");
			}
		}
	}
	else if (choose == 2)
	{
		double w = TextStringWidth("00000000")*1.5;
		DrawBox(x, y, w, h);
		x = x + w;
		w = TextStringWidth("111111111111111")*1.8;
		DrawBox(x, y, w, h);
		x = x + w;
		w = winwidth * 9 / 10 - x;
		DrawBox(x, y, w, h);
		if (button(GenUIID(0), x, y, w, h, "增加"))
		{
			isworking = 21;
			strcpy(addcoursename, "");
			strcpy(addcoursenumber, "");
		}
	}
}
void showcoursebox(int i, course *p)
{
	double x = winwidth / 10;
	double y = winheight - 8 * GetFontHeight();
	double z = (winheight - 8 * GetFontHeight()) / 14;
	double fH = GetFontHeight();
	double h = (winheight - 8 * fH) / 14;
	double w = TextStringWidth("00000000")*1.5;
	SetPenColor("Black");
	DrawBox(x, y - z * i, w, h);
	if (p)	drawLabel(x + w * 0.2, y - z * i + h / 2, p->number);
	else	drawLabel(x + w * 0.3, y - z * i + h / 2, "编号");
	x = x + w;
	w = TextStringWidth("111111111111111")*1.8;
	SetPenColor("Black");
	DrawBox(x, y - z * i, w, h);
	if (p)	drawLabel(x + w * 0.3, y - z * i + h / 2, p->coursename);
	else	drawLabel(x + w * 0.3, y - z * i + h / 2, "名称");
	x = x + w;
	w = winwidth * 9 / 10 - x;
	SetPenColor("Black");
	DrawBox(x, y - z * i, w, h);
	if (p)
	{
		if (button(GenUIID(i), x, y - z * i, w / 4, h, "修改"))
		{
			nowselectedcourse = p;
			strcpy(addcoursenumber, p->number);
			strcpy(addcoursename, p->coursename);
			isworking = 25;
		}
		if (button(GenUIID(i), x + w / 4, y - z * i, w / 4, h, "删除"))
		{
			nowselectedcourse = p;
			isdeleting = 2;
		}
		if (button(GenUIID(i), x + w / 2, y - z * i, w / 4, h, "选课名单"))
		{
			int i = 0, k = 0;
			for (i = 0; i < 10000; i++) searchresult[i] = NULL;
			student *t = p->s->next;
			while (t)
			{
				student *q = Lhead->next;
				while (q)
				{
					if (strcmp(q->id, t->id) == 0)
						break;
					q = q->next;
				}
				searchresult[k++] = q;
				t = t->next;
			}
			allsearchresults = k;
			nowspage = 1;
			snow = searchresult;
			if (allsearchresults % 10 == 0) allspages = allsearchresults / 10;
			else allspages = allsearchresults / 10 + 1;
			nowselectedcourse = p;
			isworking = 28;
			fromcourse = 1;
			drawpageselector(3);
		}
		if (button(GenUIID(i), x + w * 3 / 4, y - z * i, w / 4, h, "成绩统计"))
		{
			nowselectedcourse = p;
			isworking = 29;
		}
	}
	else drawLabel(x + w * 0.4, y - z * i + h / 2, "管理");
}
void showcourses(course *p, int choose)
{
	double x = winwidth / 10;
	double y = winheight - 8 * GetFontHeight();
	int i = 0;
	showcoursebox(0, NULL);
	y = y - (winheight - 8 * GetFontHeight()) / 14;
	p = p->next;
	while (p)
	{
		showcoursebox(i + 1, p);
		y = y - (winheight - 8 * GetFontHeight()) / 14;
		i++;
		if (i > 9) break;
		p = p->next;
	}
	if (choose == 1)	showaddcoloum(x, y, 2);
	sprintf(status, "%d records at all", allcourses);
}
void showstudentbox(int i, student *p, char *score)
{
	double x = winwidth / 10;
	double y = winheight - 8 * GetFontHeight();
	double z = (winheight - 8 * GetFontHeight()) / 14;
	double fH = GetFontHeight();
	double h = (winheight - 8 * fH) / 14;
	double w = TextStringWidth("3180104460")*1.5;
	SetPenColor("Black");
	DrawBox(x, y - z * i, w, h);
	if (p)	drawLabel(x + w * 0.2, y - z * i + h / 2, p->id);
	else
	{
		drawLabel(x + w * 0.3, y - z * i + h / 2, "学号");
		if (isworking == 1)
		{
			if (button(GenUIID(0), x + 0.7*w, y - z * i + h / 4, w / 5, h / 2, idreversed == 0 ? "↑" : "↓"))
			{
				now = Lhead;
				nowpage = 1;
				idsort(Lhead, idreversed);
				idreversed = 1 - idreversed;
			}
		}
	}
	x = x + w;
	w = TextStringWidth("Li Jiahao")*1.8;
	SetPenColor("Black");
	DrawBox(x, y - z * i, w, h);
	if (p)	drawLabel(x + w * 0.2, y - z * i + h / 2, p->name);
	else
	{
		drawLabel(x + w * 0.3, y - z * i + h / 2, "姓名");
		if (isworking == 1)
		{
			if (button(GenUIID(0), x + 0.7*w, y - z * i + h / 4, w / 5, h / 2, namereversed == 0 ? "↑" : "↓"))
			{
				now = Lhead;
				nowpage = 1;
				namesort(Lhead, namereversed);
				namereversed = 1 - namereversed;
			}
		}
	}
	x = x + w;
	w = TextStringWidth("机械电子工程") * 2.5;
	SetPenColor("Black");
	DrawBox(x, y - z * i, w, h);
	if (p)	drawLabel(x + w * 0.2, y - z * i + h / 2, p->major);
	else    drawLabel(x + w * 0.4, y - z * i + h / 2, "专业");
	x = x + w;
	w = TextStringWidth("13588390245")*1.2;
	SetPenColor("Black");
	DrawBox(x, y - z * i, w, h);
	if (score == NULL)
	{
		if (p) drawLabel(x + w * 0.1, y - z * i + h / 2, p->phonenumber);
		else drawLabel(x + w * 0.2, y - z * i + h / 2, "手机号码");
	}
	else
	{
		if (i == 0) drawLabel(x + w * 0.2, y + h / 2, "成绩");
		else drawLabel(x + 0.15*w, y - z * i + h / 2, score);
	}
	x = x + w;
	w = winwidth * 9 / 10 - x;
	SetPenColor("Black");
	DrawBox(x, y - z * i, w, h);
	if (p)
	{
		if (button(GenUIID(i), x, y - z * i, w / 3, h, "修改"))
		{
			if (isworking == 13) fromsearch = 1;
			nowselectedstudent = p;
			readytosearch();
		}
		if (button(GenUIID(i), x + w / 3, y - z * i, w / 3, h, "删除"))
		{
			nowselectedstudent = p;
			if (isworking == 13) fromsearch = 1;
			isdeleting = 1;
		}
		if (button(GenUIID(i), x + w * 2 / 3, y - z * i, w / 3, h, "详细信息"))
		{
			if (isworking == 13) fromsearch = 1;
			nowselectedstudent = p;
			isworking = 19;
		}
	}
	else drawLabel(x + w * 0.4, y - z * i + h / 2, "管理");
}
void showstudents(student *p, int choose)
{
	double x = winwidth / 10;
	double y = winheight - 8 * GetFontHeight();
	int i = 0;
	showstudentbox(0, NULL, NULL);
	y = y - (winheight - 8 * GetFontHeight()) / 14;
	p = p->next;
	while (p)
	{
		showstudentbox(i + 1, p, NULL);
		y = y - (winheight - 8 * GetFontHeight()) / 14;
		i++;
		if (i > 9) break;
		p = p->next;
	}
	if (choose == 1)	showaddcoloum(x, y, 1);
}
void DrawBox(double x, double y, double width, double height)
{
	MovePen(x, y);
	DrawLine(0, height);
	DrawLine(width, 0);
	DrawLine(0, -height);
	DrawLine(-width, 0);
}
void idsort(student *Head, int reversed)
{
	if (Head->next == NULL || Head->next->next == NULL)return;
	student *p = Head->next->next, *pstart = Head, *pend = Head->next;
	while (p != NULL)
	{
		student *tmp = pstart->next, *pre = pstart;
		if (reversed == 0)
		{
			while (tmp != p && strcmp(p->id, tmp->id) >= 0)
			{
				tmp = tmp->next; pre = pre->next;
			}
		}
		else if (reversed == 1)
		{
			while (tmp != p && strcmp(p->id, tmp->id) <= 0)
			{
				tmp = tmp->next; pre = pre->next;
			}
		}
		if (tmp == p)pend = p;
		else
		{
			pend->next = p->next;
			p->next = tmp;
			pre->next = p;
		}
		p = pend->next;
	}
}
void namesort(student *Head, int reversed)
{
	if (Head->next == NULL || Head->next->next == NULL)return;
	student *p = Head->next->next, *pstart = Head, *pend = Head->next;
	while (p != NULL)
	{
		student *tmp = pstart->next, *pre = pstart;
		if (reversed == 0)
		{
			while (tmp != p && strcmp(p->name, tmp->name) >= 0)
			{
				tmp = tmp->next; pre = pre->next;
			}
		}
		else if (reversed == 1)
		{
			while (tmp != p && strcmp(p->name, tmp->name) <= 0)
			{
				tmp = tmp->next; pre = pre->next;
			}
		}
		if (tmp == p)pend = p;
		else
		{
			pend->next = p->next;
			p->next = tmp;
			pre->next = p;
		}
		p = pend->next;
	}
}