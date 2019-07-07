#include"display.h"

void display()
{
	DisplayClear();      // 清屏
	drawMenu();
	drawstatus();    //状态栏
	if (isopening == 1) drawopeninginterface();
	else if (issaving == 1) drawsavinginterface();
	else if (isclosing == 1) drawclosinginterface();
	else if (isquitting == 1) drawquittinginterface();
	else if (isdeleting == 1) showstudentdeletinginterface();
	else if (isdeleting == 2) showcoursedeletinginterface();

	if (ishelping == 1) drawhelpinginterface();
	else if (isabouting == 1) drawaboutinginterface();

	if (isworking == 1)		showstudentinterface();
	else if (isworking == 11)		showstudentaddinterface();
	else if (isworking == 12)		showstudentsearchinterface();
	else if (isworking == 13)		showstudentsearchresultinterface();
	else if (isworking == 14)		showstudentreviseinterface();
	else if (isworking == 15)		showstudentdeleteinterface();
	else if (isworking == 19)		showdetails(nowselectedstudent);
	else if (isworking == 20)		showcourseinterface();
	else if (isworking == 21)		showcourseaddinterface();
	else if (isworking == 22)		showcoursedeleteinterface();
	else if (isworking == 23)		showcoursesearchinterface();
	else if (isworking == 24)		showcoursesearchresultinterface();
	else if (isworking == 25)		showcoursereviseinterface();
	else if (isworking == 28)		showcourselist();
	else if (isworking == 29)		showcoursestatistics();
}
void drawMenu()
{
	static char * menuListFile[] = { "File",
		"New   | Ctrl-N",
		"Open  | Ctrl-O",
		"Save  | Ctrl-S",
		"Close | Ctrl-W",
		"Exit  | Ctrl-E" };
	static char * menuListStudents[] = { "Students",
		"Add    | Ctrl-I",
		"Delete | Ctrl-D",
		"Search | Ctrl-F",
		"Show students" };
	static char * menuListCourses[] = { "Courses",
		"Add  ",
		"Delete",
		"Search",
		"Show courses" };
	static char * menuListHelp[] = { "Help",
		"Get help | Ctrl-H",
		"About us" };

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH * 1.5; // 控件高度
	double w = TextStringWidth(menuListStudents[0])*1.8; // 控件宽度
	double wlist = TextStringWidth(menuListHelp[1])*1.2; //下拉菜单宽度 
	int   selection;

	//画 图标工具栏
	drawtoolbar();
	// File 菜单
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	filemenu(selection);
	// Students 菜单
	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListStudents, sizeof(menuListStudents) / sizeof(menuListStudents[0]));
	studentsmenu(selection);
	// Courses 菜单
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListCourses, sizeof(menuListCourses) / sizeof(menuListCourses[0]));
	coursesmenu(selection);
	// Help 菜单
	selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	helpmenu(selection);
}
void drawstatus()
{
	SetPenColor("Black");
	drawLabel(0, winheight / 200, status);
}
void drawtoolbar()
{
	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH * 1.5; // 控件高度
	double w = 1.06875; // 控件宽度
	if (button(GenUIID(0), x + 4.5 * w, y - h, w / 2, h, "New"))
		createfile();
	if (button(GenUIID(0), x + 5 * w, y - h, w / 2, h, "Open") && isclosing == 0 && issaving == 0 && isworking != 1 && isworking != 3 && isworking / 10 != 1)
		isopening = 1;
	if (button(GenUIID(0), x + 5.5 * w, y - h, w / 2, h, "Save") && isopening == 0 && isclosing == 0 && isworking)
		savefile();
	if (button(GenUIID(0), x + 6 * w, y - h, w / 2, h, "Close") && isopening == 0 && issaving == 0 && isworking)
		isclosing = 1;
	if (button(GenUIID(0), x + 6.5 * w, y - h, w / 2, h, "Quit"))
		isquitting = 1;
}