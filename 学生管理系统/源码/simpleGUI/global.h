#pragma once
#include "includes.h"
typedef struct Course {
	char number[30];
	char coursename[30];
	int score;
	struct Course* next;
	struct Student *s;      //�ÿγ�����ѧ��
}course;
typedef struct Student {
	char id[12];
	char name[16];
	char major[30];
	char phonenumber[12];
	int score;
	course *c;              //ѧ����ѡ�Ŀγ� 
	struct Student *next;
}student;

extern double winwidth, winheight;   // ���ڳߴ�
extern char status[80];      //״̬������ 
extern char filename[80] ;  //�ļ��� 
extern char clipboard[30];        //������

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
extern int isworking ;       //�Ƿ��ڹ�����
extern int tmp;   //��¼isworking֮ǰ״̬ 

extern int isopening ;       //���ڳ��Դ�
extern int issaving ;
extern int isclosing ;
extern int isquitting ;
extern int isdeleting ;   //ѧ�����ڱ�ɾ����
extern int ishelping ;
extern int isabouting ;

extern int isreaded ;     //�Ƿ����������� 
extern int islocal ;      //�Ƿ�ӱ��ش� 

extern student *nowselectedstudent;    //��¼��ǰѡ�е�ѧ��
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

extern student* now ;               //��¼��ǰҳ��ĵ�һ��
extern course *cnow ;

extern int idreversed ;     //ѧ�������Ƿ���
extern int namereversed ;	//���������Ƿ���

extern student* searchresult[10000];

extern student List;     //ѧ������ 
extern student *Lhead;    //ѧ������ͷ�� ����ͷ��㣩

extern course cList;    //�γ�����
extern course *chead ;

extern FILE *fp ;