#ifndef MENU_SYS_H
#define MENU_SYS_H
#include "UtilStructs.h"


/*
     ---------
	  >MENU<
	->SELECT1
	  SELECT2
     ---------
*/

class MenuCursor
{
private:
	
	
public:
	vec2s CursorSize = { 0,0 };
	char * Cursor = nullptr;
	vec2s CursorPos = { 0,0 };
	
private:

public:
	MenuCursor(const char * cCursor, vec2s, vec2s);
	MenuCursor();
	~MenuCursor();
};


class MenuSystem
{
private:
	MenuCursor Cursor = MenuCursor("->", { 0,0 }, {2,1});
	std::string Copy;
public:
	AsciiData MenuGUI;
	MenuSystem(const char *, vec2s sz, vec2s loc, vec2s CursorS);
	
	void UpdateMenu();
	byte MenuInputs(byte, byte, vec2s, vec2s);
private:

public:

};


#endif // !MENU_SYS_H
