#pragma once
#include"includes.h"
#include"global.h"
#include"pageselector.h"
#include"others.h"

void showaddcoloum(double x, double y, int choose);
void showcoursebox(int i, course *p);
void showcourses(course *p, int choose);
void showstudentbox(int i, student *p, char *score);
void showstudents(student *p, int choose);
void DrawBox(double x, double y, double width, double height);
void idsort(student *Head, int reversed);
void namesort(student *Head, int reversed);