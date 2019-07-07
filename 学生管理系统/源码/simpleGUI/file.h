#pragma once
#include "includes.h"
#include"global.h"
#include"destroy.h"
#include"showtable.h"
#include"add.h"
#include"others.h"
#include"create.h"

void filemenu(int selection);
void guiling();
void createfile();
void savefile();
void openfile();
void closefile();
void readtolinkedlist(FILE *fp);
void writetofile(FILE *fp);
void drawopeninginterface();
void drawclosinginterface();
void drawsavinginterface();
void drawquittinginterface(); 