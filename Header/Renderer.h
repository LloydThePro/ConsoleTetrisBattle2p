#ifndef RENDERER_SYS_H
#define RENDERER_SYS_H

#if defined(UNICODE) || defined(_UNICODE)
#undef UNICODE
#undef _UNICODE 
#endif

#include <Windows.h>
#include <string>
#if defined(_MSC_VER)
#define wcscpy wcscpy_s
#define strcpy strcpy_s
#define strset _strset_s
#endif 

#define WR_High 0x001
#define WR_Med 0x002
#define WR_Low 0x003

//textmode:define normal fontsize
#define WR_TextMode_Small 0x004
#define WR_TextMode_Med 0x005

#include "UtilStructs.h"
#include "FrameCounter.h"
#include "Animation.h"

class TextDisplay
{
private:
	HANDLE hdle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, nullptr);
public:
	char * scrbuffer = nullptr;
	COORD scrsz;
	bool IsRunning = true;
	FrameCounter fps;
	char Title[50] = "TextDisplay";
private:
	void Cleaner();
public:
	void InitTextDisplay(const int& Res, const COORD& scrbuffsz);
	~TextDisplay();
	void MainLoop();
public:
	void Animate(const AnimSys& Anims, byte);
	virtual void UpdateFrame() = 0;
	//overload
	void ClearScreen();
	void ClearScreen(const COORD& topLeft, const COORD& botRight);
	void FillScreen(const char& ch);
	void FillScreen(const char& ch, const COORD& topLeft, const COORD& botRight);
	void DrawScreen(const COORD& topLeft, const COORD& botRight);
	void DrawScreen();
	//DDA line drawing algorith
	void CreateLines_DDA(const LPoints &lpoints, const char &cChar);
	void DisplayText(const char*chtxt, const COORD& pos);
	//overload
	void DisplayText(const std::string chtxt, const COORD& pos);
	void DrawAsciiArt(const AsciiArt& art, const COORD& pos);
	//overload
	void DrawAsciiArt(AsciiArt& art);
};

#endif // !RENDERER_SYS_H

