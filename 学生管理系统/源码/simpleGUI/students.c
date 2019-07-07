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
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("ȡ��")*0.9, winheight / 10, TextStringWidth("ȡ��")*1.8, 0.3333333333333333, "ȡ��"))
	{
		isworking = tmp = 1;
		sprintf(status, "%d records at all", allrecords);
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("ȷ��")*2.7, winheight / 10, TextStringWidth("ȷ��")*1.8, 0.33333333333333333, "ȷ��"))
	{
		int a = idisexist(addid);
		int b = nameisexist(addname);
		if (strcmp(addid, "") == 0 || strcmp(addname, "") == 0)
			strcpy(status, "The student number and name cannot be empty������");
		else if (a == 1 || b == 1)
			strcpy(status, "The student already exists������");
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
	drawLabel(winwidth / 2 - 6 * GetFontHeight() - TextStringWidth("����ѧ��"), winheight / 2 + GetFontHeight() * 0.7, "����ѧ��");
	textbox(GenUIID(0), winwidth / 2 - 5 * GetFontHeight(), winheight / 2, 2, 0.3333333333333333333333, search, sizeof(search));
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("ȡ��")*0.9, winheight / 7, TextStringWidth("ȡ��")*1.8, 0.3333333333333333333, "ȡ��"))
	{
		isworking = tmp = 1;
		sprintf(status, "%s", "Search cancelled");
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("����")*2.7, winheight / 7, TextStringWidth("����")*1.8, 0.333333333333333333333, "����"))
	{
		isworking = 13;
		searchstudent(search);
	}
}
void showstudentsearchresultinterface()
{
	int i = 0;
	showsearchresult(snow);
	drawpageselector(3);              //����ҳ��
	if (searchresult[0] == NULL) strcpy(status, "No records found");
	else sprintf(status, "Find %d records", allsearchresults);
	if (button(GenUIID(0), winwidth * 3 / 4 - TextStringWidth("����")*0.9, winheight / 8, TextStringWidth("����")*1.8, 0.333333333333333333, "����"))
	{
		isworking = 12;
		fromsearch = 0;
	}
}
void showstudentreviseinterface()
{
	showcoloums();
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("ȡ��")*0.9, winheight / 10, TextStringWidth("ȡ��")*1.8, 0.3333333333333333333, "ȡ��"))
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
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("ȷ��")*2.7, winheight / 10, TextStringWidth("ȷ��")*1.8, 0.33333333333333333333, "ȷ��"))
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
	drawLabel(winwidth / 2 - 6 * GetFontHeight() - TextStringWidth("ɾ��ѧ��"), winheight / 2 + GetFontHeight() * 0.7, "ɾ��ѧ��");
	textbox(GenUIID(0), winwidth / 2 - 5 * GetFontHeight(), winheight / 2, 2, 0.3333333333333333333333, search, sizeof(search));
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("ȡ��")*0.9, winheight / 7, TextStringWidth("ȡ��")*1.8, 0.333333333333333333, "ȡ��"))
	{
		isworking = tmp = 1;
		sprintf(status, "%s", "Delete cancelled");
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("ɾ��")*2.7, winheight / 7, TextStringWidth("ɾ��")*1.8, 0.3333333333333333333, "ɾ��"))
	{
		searchstudent(search);
		if (searchresult[0])
		{
			studentdelete(searchresult[0]);
			allrecords--;
			changepageselector(1);                           //�޸ķ�ҳ��
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
	double h = fH * 2; // �ؼ��߶�
	double w = winwidth / 4; // �ؼ����
	double x = winwidth / 5;
	double y = winheight - 4 * fH - h;
	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("ѧ��"), y - 1.2*h + fH * 0.7, "ѧ��");
	textbox(GenUIID(0), x, y - 1.2*h, w*2/3, h, addid, sizeof(addid));
	if (button(GenUIID(0), x+w*2/3, y - 1.2*h, w/6, h, "����"))
		strcpy(clipboard, addid);
	if (button(GenUIID(0), x + w * 5 / 6, y - 1.2*h, w / 6, h, "ճ��"))
		if(strcmp(clipboard,"")!=0)
			strcpy(addid,clipboard);

	drawLabel(x + 1.5*w - fH / 2 - TextStringWidth("����"), y - 1.2*h + fH * 0.7, "����");
	textbox(GenUIID(0), x + 1.5*w, y - 1.2*h, w*2/3, h, addname, sizeof(addname));
	if (button(GenUIID(0), x +1.5*w+ w * 2 / 3, y - 1.2*h, w / 6, h, "����"))
		strcpy(clipboard, addname);
	if (button(GenUIID(0), x +1.5*w+w * 5 / 6, y - 1.2*h, w / 6, h, "ճ��"))
		if (strcmp(clipboard, "") != 0)
			strcpy(addname, clipboard);

	drawLabel(x - fH / 2 - TextStringWidth("רҵ"), y - 3.6*h + fH * 0.7, "רҵ");
	textbox(GenUIID(0), x, y - 3.6*h, w, h, addmajor, sizeof(addmajor));
	if (button(GenUIID(0), x  + w * 2 / 3, y - 3.6*h, w / 6, h, "����"))
		strcpy(clipboard, addmajor);
	if (button(GenUIID(0), x  + w * 5 / 6, y - 3.6*h, w / 6, h, "ճ��"))
		if (strcmp(clipboard, "") != 0)
			strcpy(addmajor, clipboard);

	drawLabel(x + 1.5*w - fH / 2 - TextStringWidth("�ֻ�����"), y - 3.6*h + fH * 0.7, "�ֻ�����");
	textbox(GenUIID(0), x + 1.5*w, y - 3.6*h, w, h, addphonenumber, sizeof(addphonenumber));
	if (button(GenUIID(0), x + 1.5*w + w * 2 / 3, y - 3.6*h, w / 6, h, "����"))
		strcpy(clipboard, addphonenumber);
	if (button(GenUIID(0), x + 1.5*w + w * 5 / 6, y - 3.6*h, w / 6, h, "ճ��"))
		if (strcmp(clipboard, "") != 0)
			strcpy(addphonenumber, clipboard);

	int i = 0;
	char abc[10] = { "" };
	for (i = 0; i < 6; i++)
	{
		sprintf(abc, "�γ�%d:", i + 1);
		drawLabel(x - fH / 2 - TextStringWidth(abc), y - 5.4*h - 1.2*i*h + fH * 0.7, abc);
		textbox(GenUIID(i), x, y - 5.4*h - 1.2*i*h, w * 2 / 3, h, addcourses[i], sizeof(addcourses[i]));
		drawLabel(x + 0.88*w - fH / 2 - TextStringWidth("����:"), y - 5.4*h - 1.2*i*h + fH * 0.7, "����:");
		textbox(GenUIID(i), x + 0.88*w, y - 5.4*h - 1.2*i*h, w / 5, h, addscores[i], sizeof(addscores[i]));
	}
	for (i = 0; i < 6; i++)
	{
		sprintf(abc, "�γ�%d:", i + 7);
		drawLabel(x + 1.5*w - fH / 2 - TextStringWidth(abc), y - 5.4*h - 1.2*i*h + fH * 0.7, abc);
		textbox(GenUIID(i), x + 1.5*w, y - 5.4*h - 1.2*i*h, w * 2 / 3, h, addcourses[i + 6], sizeof(addcourses[i + 6]));
		drawLabel(x + 0.88*w + 1.5*w - fH / 2 - TextStringWidth("����:"), y - 5.4*h - 1.2*i*h + fH * 0.7, "����:");
		textbox(GenUIID(i), x + 0.88*w + 1.5*w, y - 5.4*h - 1.2*i*h, w / 5, h, addscores[i + 6], sizeof(addscores[i + 6]));
	}
}
void showdetails(student *p)
{
	double fH = GetFontHeight();
	double h = fH * 2; // �ؼ��߶�
	double w = winwidth / 4; // �ؼ����
	double x = winwidth / 5;
	double y = winheight - 8 * fH;
	strcpy(status, "Showing details");
	SetPenColor("Black");
	drawLabel(x - fH / 2 - TextStringWidth("ѧ��:"), y, "ѧ��:");
	drawLabel(x, y, p->id);
	drawLabel(x + 1.5*w - fH / 2 - TextStringWidth("����:"), y, "����:");
	drawLabel(x + 1.5*w, y, p->name);
	drawLabel(x - fH / 2 - TextStringWidth("רҵ:"), y - 1.5*h, "רҵ:");
	drawLabel(x, y - 1.5*h, p->major);
	drawLabel(x + 1.5*w - fH / 2 - TextStringWidth("�ֻ�����:"), y - 1.5*h, "�ֻ�����:");
	drawLabel(x + 1.5*w, y - 1.5*h, p->phonenumber);
	int i = 0;
	char abc[10] = { "" };
	course *q = p->c->next;
	while (q)
	{
		sprintf(abc, "�γ�%d:", i + 1);
		drawLabel(x - fH / 2 - TextStringWidth(abc), y - 3 * h - 1.5*i*h, abc);
		drawLabel(x, y - 3 * h - 1.5*i*h, q->coursename);
		itoa(q->score, abc, 10);
		drawLabel(x + 0.75*w - fH / 2 - TextStringWidth("����:"), y - 3 * h - 1.5*i*h, "����:");
		drawLabel(x + 0.75*w, y - 3 * h - 1.5*i*h, abc);
		q = q->next;
		i++;
		if (i >= 6) break;
	}
	i = 0;
	while (q)
	{
		sprintf(abc, "�γ�%d:", i + 7);
		drawLabel(x + 1.5*w - fH / 2 - TextStringWidth(abc), y - 3 * h - 1.5*i*h, abc);
		drawLabel(x + 1.5*w, y - 3 * h - 1.5*i*h, q->coursename);
		itoa(q->score, abc, 10);
		drawLabel(x + 2.25*w - fH / 2 - TextStringWidth("����:"), y - 3 * h - 1.5*i*h, "����:");
		drawLabel(x + 2.25*w, y - 3 * h - 1.5*i*h, abc);
		q = q->next;
		i++;
		if (i >= 6) break;
	}
	if (button(GenUIID(0), winwidth / 2 + TextStringWidth("ȡ��")*0.9, winheight / 10, TextStringWidth("ȡ��")*1.8, h, "ȡ��"))
	{
		sprintf(status, "%d records at all", allrecords);
		if (fromsearch == 1) isworking = 13;
		else if (fromcourse == 1) isworking = 28;
		else isworking = tmp = 1;
		fromdetail = 0;
	}
	if (button(GenUIID(0), winwidth / 2 - TextStringWidth("�޸�")*2.7, winheight / 10, TextStringWidth("�޸�")*1.8, h, "�޸�"))
	{
		fromdetail = 1;
		nowselectedstudent = p;
		readytosearch();
	}
}
