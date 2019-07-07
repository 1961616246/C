#include "global.h"

double winwidth, winheight;   // 窗口尺寸
char status[80];      //状态栏内容 
char filename[80] = "";  //文件名 
char clipboard[30];        //剪贴板

char addid[30];
char addname[30];
char addmajor[30];
char addphonenumber[30];
char addcourses[12][30];
char addscores[12][10];

char addcoursenumber[30];
char addcoursename[30];

char search[80];

int fromdetail = 0;
int fromclosing = 0;
int fromsearch = 0;
int fromcourse = 0;
int isworking = 0;       //是否在工作中
int tmp;   //记录isworking之前状态 

int isopening = 0;       //正在尝试打开
int issaving = 0;
int isclosing = 0;
int isquitting = 0;
int isdeleting = 0;   //学生正在被删除？
int ishelping = 0;
int isabouting = 0;

int isreaded = 0;     //是否已生成链表 
int islocal = 0;      //是否从本地打开 

student *nowselectedstudent;    //记录当前选中的学生
course *nowselectedcourse;

int allpages;
int nowpage;
int allrecords = 0;

int allcourses = 0;
int allcpages = 0;
int nowcpage = 0;

int allsearchresults = 0;
int allspages = 0;
int nowspage = 0;
student** snow;

student* now = NULL;               //记录当前页面的第一条
course *cnow = NULL;

int idreversed = 0;     //学号排序是否反向
int namereversed = 0;	//姓名排序是否反向

student* searchresult[10000];

student List;     //学生链表 
student *Lhead = &List;    //学生链表头部 （带头结点）

course cList;    //课程链表
course *chead = &cList;

FILE *fp = NULL;