#pragma once
#include"global.h"
#include"includes.h"
#include"display.h"

void CharEventProcess(char ch);
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);