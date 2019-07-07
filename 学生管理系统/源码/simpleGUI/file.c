#include"file.h"

void openfile()
{
	isopening = 0;
	fp = fopen(filename, "r+");
	if (fp == NULL)
		sprintf(status, "Failed to open %s. Please check the path and the file name", filename);
	else
	{
		readtolinkedlist(fp);        //生成链表
		isworking = tmp = 1;
		islocal = 1;
		sprintf(status, "Open %s successfully.%d records at all", filename, allrecords);
	}
}
void closefile()
{
	if (fp)		fclose(fp);
	isworking = 0;
	tmp = 1;
	destroystudentlist();
	destroycourselist();
	islocal = 0;
	cnow = chead;
	now = Lhead;
	allrecords = allcourses = 0;
	allcpages = allpages =  nowcpage=nowpage=0;
}
void savefile()
{
	if (tmp && isworking)
	{
		if (islocal == 1)
		{
			ishelping = isabouting = 0;
			rewind(fp);
			writetofile(fp);
			isworking = tmp = 1;
			sprintf(status, "Saved successfully");
		}
		else  issaving = 1;           //文件是新建的
	}
}
void createfile()
{
	if (isworking == 0)
	{
		islocal = 0;
		isworking = 1;
		strcpy(status, "Creating a new file");
		now = Lhead;
		cnow = chead;
		showaddcoloum(winwidth / 10, winheight - 8 * GetFontHeight(), 1);
		allrecords = 0;
	}
	else strcpy(status, "File has been opened!!!");
}
void guiling()
{
	isopening = issaving = isclosing = ishelping = isabouting = 0;
}
void filemenu(int selection)
{
	if (selection > 0) guiling();
	if (selection == 1)
		createfile();
	if (selection == 2 && isclosing == 0 && issaving == 0 && (tmp == 0 || isworking == 0))
		isopening = 1;
	if (selection == 3 && isopening == 0 && isclosing == 0 && isworking && tmp)
		savefile();
	if (selection == 4 && isopening == 0 && issaving == 0 && isworking && tmp)
		isclosing = 1;
	if (selection == 5)
		isquitting = 1;
}
void readtolinkedlist(FILE *fp)
{
	int number = 0;
	char tmp1[1000];
	char tmp2[1000];
	fgets(tmp1, 1000, fp);
	student *Ltail = Lhead;
	while (strcmp(tmp1, "#\n") != 0)
	{
		number++;
		Ltail->next = createstudentnode();   //生成新节点
		Ltail = Ltail->next;
		int cnt = 0;
		int i = 0;
		int j = 0;
		int len = strlen(tmp1);
		while (i < len&&j < len)
		{
			while ((tmp1[i] == ' ' || tmp1[i] == '\n') && i < len)
				i++;
			j = i;
			if (tmp1[i] == '\0' || tmp1[j] == '\0') break;
			while (tmp1[j] != ' '&&tmp1[j] != '\0'&&tmp1[j] != '\n')
				j++;
			strcpy(tmp2, tmp1 + i);
			strcpy(tmp2 + j - i, "\0");
			dereplaceblank(tmp2);
			if (cnt == 0) strcpy(Ltail->id, tmp2);
			else if (cnt == 1) strcpy(Ltail->name, tmp2);
			else if (cnt == 2)	strcpy(Ltail->major, tmp2);
			else if (cnt == 3) strcpy(Ltail->phonenumber, tmp2);
			j++;
			i = j;
			cnt++;
		}
		fgets(tmp1, 1000, fp);
		i = j = cnt = 0;
		len = strlen(tmp1);
		if (strcmp(tmp1, "\n") != 0)
		{
			char tnumber[30];
			char tcoursename[30];
			int tscore;
			while (i < len&&j < len)
			{
				while ((tmp1[i] == ' ' || tmp1[i] == '\n') && i < len)
					i++;
				j = i;
				if (tmp1[i] == '\0' || tmp1[j] == '\0') break;
				while (tmp1[j] != ' '&&tmp1[j] != '\0'&&tmp1[j] != '\n')
					j++;
				strcpy(tmp2, tmp1 + i);
				strcpy(tmp2 + j - i, "\0");
				dereplaceblank(tmp2);
				if (cnt == 0) strcpy(tnumber, tmp2);
				else if (cnt == 1) strcpy(tcoursename, tmp2);
				else if (cnt == 2)
				{
					tscore = atoi(tmp2);
					Addtocourse(Ltail->c, tnumber, tcoursename, tscore);
					Addtocourselist(Ltail, tnumber, tcoursename, tscore);
				}
				j++;
				i = j;
				cnt++;
				if (cnt >= 3) cnt = cnt - 3;
			}
		}
		fgets(tmp1, 1000, fp);
	}
	now = Lhead;
	cnow = chead;
	allrecords = number;
	if (allrecords % 10 == 0)
		allpages = allrecords / 10;
	else allpages = allrecords / 10 + 1;
	if (allcourses % 10 == 0)
		allcpages = allcourses / 10;
	else allcpages = allcourses / 10 + 1;
	nowpage = nowcpage = 1;
}
void writetofile(FILE *fp)
{
	student *p = Lhead->next;
	while (p)
	{
		replaceblank(p->id);
		replaceblank(p->name);
		fprintf(fp, "%s %s", p->id, p->name);
		if (p->major)
		{
			replaceblank(p->major);
			fprintf(fp, " %s", p->major);
		}
		if (p->phonenumber)
		{
			replaceblank(p->phonenumber);
			fprintf(fp, " %s", p->phonenumber);
		}
		fprintf(fp, "\n");
		course *q = p->c->next;
		while (q)
		{
			replaceblank(q->number);
			replaceblank(q->coursename);
			fprintf(fp, " %s %s %d", q->number, q->coursename, q->score);
			q = q->next;
		}
		fprintf(fp, "\n");
		p = p->next;
	}
	fprintf(fp, "#\n");
}
void drawopeninginterface()
{
	strcpy(status, "Please enter the path of the file");
	textbox(GenUIID(0), winwidth * 2 / 5, 0, winwidth * 3 / 5 - winwidth / 5, 1.0 / 3, filename, sizeof(filename));
	if (button(GenUIID(0), winwidth * 4 / 5, 0, 1, 1.0 / 3, "Enter"))
		openfile();                                              //打开文件
	if (button(GenUIID(0), winwidth * 9 / 10, 0, 1, 1.0 / 3, "Cancel"))
	{
		isopening = 0;
		sprintf(status, "");
	}
}
void drawclosinginterface()
{
	if (tmp&&isworking)
	{
		ishelping = isabouting = 0;
		sprintf(status, "Do you want to save it?");
		if (button(GenUIID(0), winwidth - 3, 0, 1, 0.33333333333333333, "Save"))
		{
			if (islocal == 0)
			{
				issaving = 1;
				isclosing = 0;
				fromclosing = 1;
			}
			else
			{
				isclosing = 0;
				rewind(fp);
				writetofile(fp);
				closefile();                           //关闭文件
				sprintf(status, "Saved successfully");
			}
		}
		if (button(GenUIID(0), winwidth - 2, 0, 1, 0.333333333333333333333, "Not Save"))
		{
			closefile();                              //关闭文件
			isclosing = 0;
			sprintf(status, "");
		}
		if (button(GenUIID(0), winwidth - 1, 0, 1, 0.33333333333333333333333, "Cancel"))
		{
			isworking = 1;
			isclosing = 0;
			sprintf(status, "");
		}
	}
	else isclosing = 0;
}
void drawsavinginterface()
{
	strcpy(status, "Please enter the path and the name of the file");
	textbox(GenUIID(0), winwidth * 2 / 5, 0, winwidth * 3 / 5 - winwidth / 5, 1.0 / 3, filename, sizeof(filename));
	ishelping = isabouting = 0;
	if (button(GenUIID(0), winwidth - 2, 0, 1, 0.3333333333333333333333, "Save"))
	{
		fp = fopen(filename, "w+");
		if (fp == NULL)
			sprintf(status, "Failed to save %s. Please check the file name and your permission to save it!", filename);
		else
		{
			rewind(fp);
			writetofile(fp);
			isworking = tmp = 1;
			islocal = 1;
			sprintf(status, "Save %s successfully", filename);
			issaving = 0;
			if (fromclosing == 1)
			{
				fromclosing = 0;
				closefile();                              //关闭文件
			}
		}
	}
	if (button(GenUIID(0), winwidth - 1, 0, 1, 0.3333333333333333333333, "Cancel"))
	{
		issaving = 0;
		sprintf(status, "");
		fromclosing = 0;
	}
}
void drawquittinginterface()
{
	if (tmp && isworking)
	{
		ishelping = isabouting = 0;
		sprintf(status, "Do you want to quit without save?");
		if (button(GenUIID(0), winwidth - 3, 0, 1, 0.33333333333333333333333333, "Save"))
		{
			rewind(fp);
			writetofile(fp);
			exit(-1);
		}
		if (button(GenUIID(0), winwidth - 2, 0, 1, 0.3333333333333333333333333, "Not Save"))
			exit(-1);
		if (button(GenUIID(0), winwidth - 1, 0, 1, 0.33333333333333333333333, "Cancel"))
		{
			isworking = 1;
			isquitting = 0;
			sprintf(status, "");
		}
	}
	else exit(-1);
}
