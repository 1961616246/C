#include"pageselector.h"

void drawpageselector(int choose)
{
	double fH = GetFontHeight();
	double h = (winheight - 8 * fH) / 14;
	double w1 = winwidth / 5;
	double w2 = w1 / 3;
	if (choose == 1)
	{
		if (button(GenUIID(0), winwidth / 2 - 0.5*w1, 4 * fH, w2, h, "<"))         //前翻
		{
			if (nowpage > 1)
			{
				nowpage--;
				student *p = Lhead;
				while (p->next->next->next->next->next->next->next->next->next->next != now)
					p = p->next;
				now = p;
			}
		}
		char page[10];
		sprintf(page, "%d/%d", nowpage, allpages);
		drawLabel(winwidth / 2 - 0.6*w1 + 1.5*w2, 4 * fH + h / 2, page);
		if (button(GenUIID(0), winwidth / 2 - 0.5*w1 + 2 * w2, 4 * fH, w2, h, ">"))     //后翻
		{
			if (nowpage < allpages)
			{
				nowpage++;
				now = now->next->next->next->next->next->next->next->next->next->next;
			}
		}
	}
	else if (choose == 2)
	{
		if (button(GenUIID(0), winwidth / 2 - 0.5*w1, 4 * fH, w2, h, "<"))         //前翻
		{
			if (nowcpage > 1)
			{
				nowcpage--;
				course *p = chead;
				while (p->next->next->next->next->next->next->next->next->next->next != cnow)
					p = p->next;
				cnow = p;
			}
		}
		char page[10];
		sprintf(page, "%d/%d", nowcpage, allcpages);
		drawLabel(winwidth / 2 - 0.6*w1 + 1.5*w2, 4 * fH + h / 2, page);
		if (button(GenUIID(0), winwidth / 2 - 0.5*w1 + 2 * w2, 4 * fH, w2, h, ">"))     //后翻
		{
			if (nowcpage < allcpages)
			{
				nowcpage++;
				cnow = cnow->next->next->next->next->next->next->next->next->next->next;
			}
		}
	}
	else if (choose == 3)
	{
		if (button(GenUIID(0), winwidth / 2 - 0.5*w1, 4 * fH, w2, h, "<"))         //前翻
		{
			if (nowspage > 1)
			{
				nowspage--;
				snow = snow - 10;
			}
		}
		char page[10];
		sprintf(page, "%d/%d", nowspage, allspages);
		drawLabel(winwidth / 2 - 0.6*w1 + 1.5*w2, 4 * fH + h / 2, page);
		if (button(GenUIID(0), winwidth / 2 - 0.5*w1 + 2 * w2, 4 * fH, w2, h, ">"))     //后翻
		{
			if (nowspage < allspages)
			{
				nowspage++;
				snow = snow + 10;
			}
		}
	}
}
void changepageselector(int choose)
{
	if (choose == 1)
	{
		if (allrecords % 10 == 0) allpages = allrecords / 10;
		else allpages = allrecords / 10 + 1;
		if (nowpage > allpages)
		{
			nowpage--;
			student *p = Lhead;
			while (p->next->next->next->next->next->next->next->next->next->next != now)
				p = p->next;
			now = p;
		}
	}
	else if (choose == 2)
	{
		if (allcourses % 10 == 0) allcpages = allcourses / 10;  //翻页器做修改
		else allcpages = allcourses / 10 + 1;
		if (nowcpage > allcpages&&allcpages)
		{
			nowcpage--;
			course *p = chead;
			while (p->next->next->next->next->next->next->next->next->next->next != cnow)
				p = p->next;
			cnow = p;
		}
		else if (allcpages == 0)
		{
			nowcpage = 0;
			cnow = chead;
		}
	}
}