#pragma once
#include "includes.h"
typedef struct Course {
	char number[30];
	char coursename[30];
	int score;
	struct Course* next;
	struct Student *s;      //该课程所有学生
}course;
typedef struct Student {
	char id[12];
	char name[16];
	char major[30];
	char phonenumber[12];
	int score;
	course *c;              //学生所选的课程 
	struct Student *next;
}student;

extern double winwidth, winheight;   // 窗口尺寸
extern char status[80];      //状态栏内容 
extern char filename[80] ;  //文件名 
extern char clipboard[30];        //剪贴板

extern char addid[30];
extern char addname[30];
extern char addmajor[30];
extern char addphonenumber[30];
extern char addcourses[12][30];
extern char addscores[12][10];

extern char addcoursenumber[30];
extern char addcoursename[30];

extern char search[80];

extern int fromdetail;
extern int fromclosing ;
extern int fromsearch ;
extern int fromcourse ;
extern int isworking ;       //是否在工作中
extern int tmp;   //记录isworking之前状态 

extern int isopening ;       //正在尝试打开
extern int issaving ;
extern int isclosing ;
extern int isquitting ;
extern int isdeleting ;   //学生正在被删除？
extern int ishelping ;
extern int isabouting ;

extern int isreaded ;     //是否已生成链表 
extern int islocal ;      //是否从本地打开 

extern student *nowselectedstudent;    //记录当前选中的学生
extern course *nowselectedcourse;

extern int allpages;
extern int nowpage;
extern int allrecords ;

extern int allcourses ;
extern int allcpages ;
extern int nowcpage ;

extern int allsearchresults ;
extern int allspages ;
extern int nowspage ;
extern student** snow;

extern student* now ;               //记录当前页面的第一条
extern course *cnow ;

extern int idreversed ;     //学号排序是否反向
extern int namereversed ;	//姓名排序是否反向

extern student* searchresult[10000];

extern student List;     //学生链表 
extern student *Lhead;    //学生链表头部 （带头结点）

extern course cList;    //课程链表
extern course *chead ;

extern FILE *fp ;