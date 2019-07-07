#include"destroy.h"
void destroycourselist()
{
	course *p = chead->next;
	if (p == NULL) return;
	course *q;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	chead->next = NULL;
}
void destroystudentlist()
{
	student *p = Lhead->next;
	if (p == NULL) return;
	student *q;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	Lhead->next = NULL;
}