#include"add.h"

void Addtocourselist(student *s, char *s1, char *s2, int score)
{
	course *t = chead->next;
	while (t)
	{
		if (strcmp(t->number, s1) == 0)
			break;
		t = t->next;
	}
	course *p;
	if (t == NULL)
	{
		p = createcoursenode();
		p->next = chead->next;
		chead->next = p;
		strcpy(p->number, s1);
		strcpy(p->coursename, s2);
		allcourses++;
	}
	else	p = t;
	student *q = createstudentnode();
	q->next = p->s->next;
	p->s->next = q;
	q->score = score;
	strcpy(q->id, s->id);
	strcpy(q->name, s->name);
	strcpy(q->major, s->major);
	strcpy(q->phonenumber, s->phonenumber);
}
int addtolinkedlist()
{
	int flag = 1;
	int i = 0;
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
		student *p = createstudentnode();
		for (i = 0; i < 12; i++)
		{
			if (strcmp(addcourses[i], "") != 0)
			{
				course *c = courseisexist(addcourses[i]);
				student *t = createstudentnode();
				t->next = c->s->next;
				c->s->next = t;
				strcpy(t->id, addid);
				strcpy(t->name, addname);
				strcpy(t->major, addmajor);
				strcpy(t->phonenumber, addphonenumber);
				t->score = atoi(addscores[i]);
				Addtocourse(p->c, c->number, c->coursename, atoi(addscores[i]));
			}
		}
		strcpy(p->id, addid);
		strcpy(p->name, addname);
		strcpy(p->major, addmajor);
		strcpy(p->phonenumber, addphonenumber);
		p->next = Lhead->next;
		Lhead->next = p;
		allrecords++;
		if (allrecords % 10 == 0) allpages = allrecords / 10;
		else allpages = allrecords / 10 + 1;
		if (nowpage == 0) nowpage = 1;
		isworking = tmp = 1;
		sprintf(status, "%d records at all", allrecords);
		return 1;
	}
	else
	{
		strcpy(status, "The course does not exist!!!");
		return 0;
	}
}
void Addtocourse(course *head, char *s1, char *s2, int n)
{
	course *q = createcoursenode();
	q->next = head->next;
	strcpy(q->number, s1);
	strcpy(q->coursename, s2);
	q->score = n;
	head->next = q;
}