#include "global.h"

double winwidth, winheight;   // ���ڳߴ�
char status[80];      //״̬������ 
char filename[80] = "";  //�ļ��� 
char clipboard[30];        //������

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
int isworking = 0;       //�Ƿ��ڹ�����
int tmp;   //��¼isworking֮ǰ״̬ 

int isopening = 0;       //���ڳ��Դ�
int issaving = 0;
int isclosing = 0;
int isquitting = 0;
int isdeleting = 0;   //ѧ�����ڱ�ɾ����
int ishelping = 0;
int isabouting = 0;

int isreaded = 0;     //�Ƿ����������� 
int islocal = 0;      //�Ƿ�ӱ��ش� 

student *nowselectedstudent;    //��¼��ǰѡ�е�ѧ��
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

student* now = NULL;               //��¼��ǰҳ��ĵ�һ��
course *cnow = NULL;

int idreversed = 0;     //ѧ�������Ƿ���
int namereversed = 0;	//���������Ƿ���

student* searchresult[10000];

student List;     //ѧ������ 
student *Lhead = &List;    //ѧ������ͷ�� ����ͷ��㣩

course cList;    //�γ�����
course *chead = &cList;

FILE *fp = NULL;