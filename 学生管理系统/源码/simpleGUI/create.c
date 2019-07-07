#include"create.h"
student* createstudentnode()                    //创建学生节点
{
	student *p = (student*)malloc(sizeof(student));
	p->next = NULL;
	strcpy(p->id, "");
	strcpy(p->name, "");
	strcpy(p->major, "");
	strcpy(p->phonenumber, "");
	p->score = 0;
	course *q = (course*)malloc(sizeof(course));
	q->next = NULL;
	p->c = q;
	return p;
}
course* createcoursenode()
{
	course *p = (course*)malloc(sizeof(course));
	p->next = NULL;
	strcpy(p->number, "");
	strcpy(p->coursename, "");
	p->score = 0;
	student *q = (student*)malloc(sizeof(student));
	q->next = NULL;
	p->s = q;
	return p;
}