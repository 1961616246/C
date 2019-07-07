#include"others.h"

int cnumberisexist(char *s)
{
	course *p = chead->next;
	int result = 0;
	while (p)
	{
		if (strcmp(p->number, s) == 0)
		{
			result = 1;
			break;
		}
		p = p->next;
	}
	return result;
}
int idisexist(char *s)
{
	int result = 0;
	student *p = Lhead->next;
	while (p)
	{
		if (strcmp(p->id, s) == 0)
		{
			result = 1;
			break;
		}
		p = p->next;
	}
	return result;
}
int nameisexist(char *s)
{
	int result = 0;
	student *p = Lhead->next;
	while (p)
	{
		if (strcmp(p->name, s) == 0)
		{
			result = 1;
			break;
		}
		p = p->next;
	}
	return result;
}
void searchstudent(char *s)
{
	int i;
	for (i = 0; i < 10000; i++) searchresult[i] = NULL;
	int k = 0;
	student *p = Lhead->next;
	while (p)
	{
		if (strcmp(p->id, s) == 0 || strcmp(p->name, s) == 0 || strcmp(p->phonenumber, s) == 0 || strcmp(p->major, s) == 0)
			searchresult[k++] = p;
		p = p->next;
	}
	allsearchresults = k;
	if (searchresult[0])
		nowspage = 1;
	else nowspage = 0;
	snow = searchresult;
	if (allsearchresults % 10 == 0) allspages = allsearchresults / 10;
	else allspages = allsearchresults / 10 + 1;
}
void coursedelete(course *s)
{
	course *p = chead;
	while (p->next != s)
		p = p->next;
	p->next = s->next;
	student *q = Lhead->next;
	while (q)
	{
		course *t = q->c;
		while (t->next&&strcmp(t->next->number, s->number) != 0)
			t = t->next;
		if (t->next)
		{
			course *tmp = t->next;
			t->next = t->next->next;
			free(tmp);
		}
		q = q->next;
	}
	free(s);
}
void studentdelete(student *s)
{
	student *p = Lhead;
	while (p->next != s)
		p = p->next;
	p->next = s->next;
	course *q = chead->next;
	while (q)
	{
		student *t = q->s;
		while (t->next&&strcmp(t->next->id, s->id) != 0)
			t = t->next;
		if (t->next)
		{
			student *tmp = t->next;
			t->next = t->next->next;
			free(tmp);
		}
		q = q->next;
	}
	free(s);
}
void replaceblank(char *s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ') s[i] = '$';
		i++;
	}
}
void dereplaceblank(char *s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$') s[i] = ' ';
		i++;
	}
}
course* courseisexist(char *name)
{
	course *p = chead->next;
	while (p)
	{
		if (strcmp(p->coursename, name) == 0)
			break;
		p = p->next;
	}
	return p;
}
void showsearchresult(student **s)
{
	int i = 0;
	showstudentbox(0, NULL, NULL);
	while (s[i])
	{
		showstudentbox(i + 1, s[i], NULL);
		i++;
		if (i > 9) break;
	}
}
void showxuanke(student **s, char *number)
{
	int i = 0;
	showstudentbox(0, NULL, "1");
	while (s[i])
	{
		course *p = s[i]->c->next;
		while (p)
		{
			if (strcmp(p->number, number) == 0)
				break;
			p = p->next;
		}
		char tmp[5];
		itoa(p->score, tmp, 10);
		showstudentbox(i + 1, s[i], tmp);
		i++;
		if (i > 9)break;
	}
}
course* searchcourse(char *s)
{
	course *p = chead->next;
	while (p)
	{
		if (strcmp(p->number, s) == 0 || strcmp(p->coursename, s) == 0)
			return p;
		p = p->next;
	}
	return p;
}
void readytosearch()
{
	student *p = nowselectedstudent;
	isworking = 14;
	strcpy(addid, p->id);
	strcpy(addname, p->name);
	strcpy(addmajor, p->major);
	strcpy(addphonenumber, p->phonenumber);
	course *q = p->c->next;
	int j = 0;
	while (q)
	{
		strcpy(addcourses[j], q->coursename);
		char tmp[20];
		itoa(q->score, tmp, 10);
		strcpy(addscores[j], tmp);
		q = q->next;
		j++;
		if (j >= 12) break;
	}
	for (; j < 12; j++)
	{
		strcpy(addcourses[j], "");
		strcpy(addscores[j], "");
	}
}