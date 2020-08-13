#include "MenuSystem.h"

MenuCursor::MenuCursor(const char * cursor, vec2s Pos, vec2s Sz)
{
	MenuCursor::Cursor = new char[(Sz.X * Sz.Y) + 1];
	memcpy_s(Cursor, sizeof(char) * Sz.X * Sz.Y + 1, cursor, strlen(cursor));
	this->CursorPos = Pos;
	this->CursorSize = Sz;
}
MenuCursor::MenuCursor()
{

	this->CursorPos = { 0,0 };
	this->CursorSize = { 0,0 };
}
MenuCursor::~MenuCursor()
{
	if (MenuCursor::Cursor != nullptr) delete[] Cursor;
}
MenuSystem::MenuSystem(const char * filename, vec2s sz, vec2s loc, vec2s CursorS)
{
	MenuSystem::MenuGUI.Pos = { loc.X, loc.Y };
	MenuSystem::MenuGUI.sz = { sz.X, sz.Y };
	Cursor.CursorPos = CursorS;
	
	if (LoadDataFromFile(MenuSystem::MenuGUI, filename))
		Copy = MenuGUI.graphics;


	MenuSystem::UpdateMenu();
}
byte MenuSystem::MenuInputs(byte inputmode, byte orientation, vec2s vSE,vec2s hSE)
{
	switch (inputmode)
	{
	//+++++++++++++++++++++++++++++++++++++++++++
	case WASD:
		//--------------------
		switch (orientation)
		{
		case VERTICAL:
			
			if ((GetAsyncKeyState(87) & 0x1) && MenuSystem::Cursor.CursorPos.Y > vSE.X)
			{
				MenuSystem::Cursor.CursorPos.Y--;
				MenuSystem::UpdateMenu();

			}
			else if ((GetAsyncKeyState(83) & 0x1) && MenuSystem::Cursor.CursorPos.Y < vSE.Y)
			{
				MenuSystem::Cursor.CursorPos.Y++;
				MenuSystem::UpdateMenu();
			}

			else if (GetAsyncKeyState(VK_SPACE) & 0x1)
				return MenuSystem::Cursor.CursorPos.Y;
			break;

		case HORIZONTAL:
			if ((GetAsyncKeyState(68) & 0x1) && MenuSystem::Cursor.CursorPos.X < hSE.Y)
			{
				MenuSystem::Cursor.CursorPos.X++;
				MenuSystem::UpdateMenu();
			}
				
			else if ((GetAsyncKeyState(65) & 0x1) && MenuSystem::Cursor.CursorPos.X > hSE.X)
			{
				MenuSystem::Cursor.CursorPos.X--;
				MenuSystem::UpdateMenu();
			}
				
			break;
		}
		//--------------------
		break;
	//+++++++++++++++++++++++++++++++++++++++++++
	case UDLR:
		//--------------------

		/*
			NOTE TO SELF:
				Arrow keys still not implemented and not being used
		*/
		switch (orientation)
		{
		case VERTICAL:

			break;

		case HORIZONTAL:

			break;
		}
		//----------------
		break;
	//++++++++++++++++++++++++++++++++++++++++

	}

	return 254;
}
void MenuSystem::UpdateMenu()
{
	MenuSystem::MenuGUI.graphics = Copy;

	for(int y = 0; y < Cursor.CursorSize.Y; y++)
		for (int x = 0; x < Cursor.CursorSize.X; x++)
		{
			MenuGUI.graphics[(x + Cursor.CursorPos.X) + ((y + Cursor.CursorPos.Y) * MenuGUI.sz.X)] = Cursor.Cursor[x + y * Cursor.CursorSize.X];
		}

}