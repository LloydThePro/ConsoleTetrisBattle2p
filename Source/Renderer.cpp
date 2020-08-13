#include "Renderer.h"



Points operator-(const Points &p1, const Points &p2)
{
	Points result;
	result.X = p1.X - p2.X;
	result.Y = p1.Y - p2.Y;
	return result;
}

void TextDisplay::Cleaner()
{

	delete[] scrbuffer;
	scrbuffer = nullptr;
}

bool LoadDataFromFile(AsciiArt& art, const char * filename)
{
	std::string temp;

	std::ifstream file(filename);
	std::stringstream streamer;
	if (file.is_open())
	{
		while (std::getline(file, temp))
		{
			streamer << temp  /*<< '\n'*/;
		}
		art.graphics = streamer.str();
	}
	else
		return false;


	return true;
}
//Overload
bool LoadDataFromFile(AsciiArt& art, const std::string& filename)
{
	std::string temp;
	std::ifstream file(filename);
	std::stringstream streamer;
	if (file.is_open())
	{
		while (std::getline(file, temp))
		{
			streamer << temp /*<< '\n'*/;
		}
		art.graphics = streamer.str();
	}
	else
		return false;


	return true;
}
void TextDisplay::InitTextDisplay(const int& Res, const COORD& scrbuffsz)
{
	COORD fontSz;

	switch (Res)
	{
	case WR_High:
		fontSz = { 4,6 };
		break;
	case WR_Med:
		fontSz = { 8,8 };
		break;
	case WR_Low:
		fontSz = { 5,12 };
		break;
	case WR_TextMode_Small:
		fontSz = { 7,12 };
		break;
	case WR_TextMode_Med:
		fontSz = { 8,12 };
		break;
	default:
		fontSz = { 4,6 };
		break;
	}


	SetConsoleActiveScreenBuffer(hdle);

	CONSOLE_FONT_INFOEX CFIEX;
	//GetCurrentConsoleFontEx(hdle, FALSE, &CFIEX);
	wcscpy_s(CFIEX.FaceName, L"Raster Fonts");
	CFIEX.cbSize = sizeof(CFIEX);
	CFIEX.dwFontSize = fontSz;
	CFIEX.FontFamily = FF_DONTCARE;
	CFIEX.FontWeight = FW_NORMAL * 2;
	
	SetConsoleScreenBufferSize(hdle, scrbuffsz);
	SetCurrentConsoleFontEx(hdle, FALSE, &CFIEX);
	MoveWindow(GetConsoleWindow(), 0, 0, 1400, 1400, FALSE);

	CONSOLE_SCREEN_BUFFER_INFO CSBI;
	GetConsoleScreenBufferInfo(hdle, &CSBI);
	scrbuffer = new char[CSBI.dwSize.X * CSBI.dwSize.Y];
	scrsz.Y = CSBI.dwSize.Y;
	scrsz.X = CSBI.dwSize.X;
	memset(scrbuffer, ' ', CSBI.dwSize.X * CSBI.dwSize.Y * sizeof(CHAR));

	CONSOLE_CURSOR_INFO CCI;
	GetConsoleCursorInfo(hdle, &CCI);
	CCI.bVisible = FALSE;
	SetConsoleCursorInfo(hdle, &CCI);
	SetConsoleTitle(Title);


}

TextDisplay::~TextDisplay()
{
	if (scrbuffer != nullptr)
		delete[] this->scrbuffer;

}

void TextDisplay::MainLoop()
{

	while (IsRunning)
	{

		fps.updateD();
		UpdateFrame();
		fps.updateI();
	}
	Cleaner();
}

//overload
void TextDisplay::ClearScreen()
{
	memset(scrbuffer, ' ', scrsz.X * scrsz.Y*(sizeof(char)));
}
void TextDisplay::ClearScreen(const COORD& topLeft, const COORD& botRight)
{
	memset(&scrbuffer[topLeft.X + (topLeft.Y * scrsz.X)], ' ', botRight.X * botRight.Y);
}

void TextDisplay::FillScreen(const char& ch)
{
	memset(scrbuffer, ch, scrsz.X * scrsz.Y*(sizeof(char)));
}
void TextDisplay::FillScreen(const char& ch, const COORD& topLeft, const COORD& botRight)
{
	memset(&scrbuffer[topLeft.X + (topLeft.Y * scrsz.X)], ch, botRight.X * botRight.Y);
}
void TextDisplay::DrawScreen(const COORD& topLeft, const COORD& botRight)
{
	DWORD dwBytesWritten;
	WriteConsoleOutputCharacter(hdle, scrbuffer, botRight.X * botRight.Y * sizeof(char), topLeft, &dwBytesWritten);
}
void TextDisplay::DrawScreen()
{
	DWORD dwBytesWritten;
	WriteConsoleOutputCharacter(hdle, scrbuffer, scrsz.X * scrsz.Y * sizeof(char), { 0,0 }, &dwBytesWritten);
}

//DDA line drawing algorith
void TextDisplay::CreateLines_DDA(const LPoints &lpoints, const char &cChar)
{
	short Steps = 0;
	Points def = lpoints.p2 - lpoints.p1;
	float incrementX = lpoints.p1.X, incrementY = lpoints.p1.Y;

	if (abs(def.X) > abs(def.Y))
		Steps = abs(def.X);
	else
		Steps = abs(def.Y);


	for (short i = 0; i < Steps; i++)
	{

		incrementX += (float)def.X / Steps;
		incrementY += (float)def.Y / Steps;
		scrbuffer[(int)incrementX + (int)incrementY *scrsz.X] = cChar;
	}

}


void TextDisplay::DisplayText(const char*chtxt, const COORD& pos)
{
	memcpy(&scrbuffer[pos.X + pos.Y * scrsz.X], chtxt, strlen(chtxt));
}

//overload
void TextDisplay::DisplayText(const std::string chtxt, const COORD& pos)
{
	memcpy(&scrbuffer[pos.X + pos.Y * scrsz.X], &chtxt, chtxt.size());
}

void TextDisplay::DrawAsciiArt(const AsciiArt& art, const COORD& pos)
{
	for (short y = 0; y < art.sz.Y; y++)
	{
		memcpy(&scrbuffer[pos.X + ((y + pos.Y) * scrsz.X)], &art.graphics[0 + y * art.sz.X], art.sz.X);
	}
}
//overload
void TextDisplay::DrawAsciiArt(AsciiArt& art)
{
	char * graphics = &art.graphics[0];
	for (short y = 0; y < art.sz.Y; y++)
	{
		memcpy(&scrbuffer[art.Pos.X + ((y + art.Pos.Y) * scrsz.X)], &graphics[0 + y * art.sz.X], art.sz.X);
	}
}


void TextDisplay::Animate(const AnimSys& Anims, byte nFrame)
{
	for (byte h = 0; h < Anims.frames.FrameSz.Y; h++)
	{
		memcpy(&scrbuffer[Anims.Pos.X + ((h + Anims.Pos.Y) * scrsz.X)], &Anims.frames.frames[nFrame][h * Anims.frames.FrameSz.X], Anims.frames.FrameSz.X);
	}
}