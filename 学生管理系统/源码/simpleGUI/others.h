#pragma once
#include "includes.h"
#include"global.h"
#include"showtable.h"

int cnumberisexist(char *s);
int idisexist(char *s);
int nameisexist(char *s);
void searchstudent(char *s);
void coursedelete(course *s);
void studentdelete(student *s);
void replaceblank(char *s);
void dereplaceblank(char *s);
course* courseisexist(char *name);
void showsearchresult(student **s);
void showxuanke(student **s, char *number);
course* searchcourse(char *s);
void readytosearch();