#include "global.h"
#include"includes.h"
#include"eventprocess.h"

void Main() 
{
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("ѧ������ϵͳ");
	tmp = 1;
    InitGraphics();
	// ��ô��ڳߴ�
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
	// ע��ʱ����Ӧ����
	registerCharEvent(CharEventProcess); // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
}