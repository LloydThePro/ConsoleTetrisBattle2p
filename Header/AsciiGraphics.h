#ifndef ASCII_GRAP_H
#define ASCII_GRAP_H
//1.2.2


//No Unicode allowed!!!




//Move to "definition.h" so it can be shared
/*typedef struct _AsciiArt
{
	std::string graphics;
    COORD sz;
	COORD Pos;
	_AsciiArt operator= (const _AsciiArt& art)
	{
		return{ {art.graphics},art.sz,art.Pos };
	}

}AsciiArt;*/






//some functions
#include "definition.h"




















namespace txt
{


    namespace util
    {
		/*typedef struct _UtilTimer
		{

			std::chrono::high_resolution_clock::time_point initTime;
			std::chrono::high_resolution_clock::time_point deltaTime;
			
			float elapseTime = 0.0f;
			_UtilTimer()
			{
				initTime = std::chrono::high_resolution_clock::now();
				deltaTime = std::chrono::high_resolution_clock::now();
			}

			void UpdateDTime()
			{
				std::chrono::duration<float> timeDuration;
				deltaTime = std::chrono::high_resolution_clock::now();
				timeDuration = deltaTime - initTime;
				elapseTime = timeDuration.count();
			}

			bool IsTimesUp(const unsigned int& Seconds)
			{
				if (elapseTime >= Seconds)
				{
					initTime = std::chrono::high_resolution_clock::now();
					return true;
				}

				else
					return false;

			}

		}UtilTimer;*/

		
       
		//round off the floating point
		//ex: 10.5 = 10 or 7.3 = 7
		

    }




/*class TextDisplay
{
private:
HANDLE hdle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL,CONSOLE_TEXTMODE_BUFFER,nullptr);
public:
char * scrbuffer = nullptr;
COORD scrsz;
bool IsRunning = true;
txt::util::FrameCounter fps;

char Title[50] = "TextDisplay";


private:
	void Cleaner()
	{

		delete[] scrbuffer;
		scrbuffer = nullptr;
	}

public:
    void InitTextDisplay(const int& Res,const COORD& scrbuffsz)
    {
        COORD fontSz;

        switch(Res)
        {
        case WR_High:
            fontSz = {4,6};
            break;
        case WR_Med:
            fontSz = {8,8};
            break;
        case WR_Low:
            fontSz = {5,12};
            break;
        case WR_TextMode_Small:
            fontSz = {7,12};
            break;
        case WR_TextMode_Med:
            fontSz = {8,12};
            break;
        default:
            fontSz = {4,6};
            break;
        }


        SetConsoleActiveScreenBuffer(hdle);

        CONSOLE_FONT_INFOEX CFIEX;
        GetCurrentConsoleFontEx(hdle,FALSE,&CFIEX);
        wcscpy_s(CFIEX.FaceName, L"Raster Fonts");
        CFIEX.cbSize = sizeof(CFIEX);
        CFIEX.dwFontSize = fontSz;
		CFIEX.FontFamily = FF_DONTCARE;
        CFIEX.FontWeight = FW_NORMAL;
        SetConsoleScreenBufferSize(hdle,scrbuffsz);
        SetCurrentConsoleFontEx(hdle,FALSE,&CFIEX);
        MoveWindow(GetConsoleWindow(),0,0,1400, 1400,FALSE);

        CONSOLE_SCREEN_BUFFER_INFO CSBI;
        GetConsoleScreenBufferInfo(hdle,&CSBI);
        scrbuffer = new char[CSBI.dwSize.X * CSBI.dwSize.Y];
        scrsz.Y = CSBI.dwSize.Y;
        scrsz.X = CSBI.dwSize.X;
        memset(scrbuffer,' ',CSBI.dwSize.X * CSBI.dwSize.Y *sizeof(CHAR));



        CONSOLE_CURSOR_INFO CCI;
        GetConsoleCursorInfo(hdle,&CCI);
        CCI.bVisible = FALSE;
        SetConsoleCursorInfo(hdle,&CCI);
        SetConsoleTitle(Title);


    }

    ~TextDisplay()
    {
		if(scrbuffer != nullptr)
        delete[] this->scrbuffer;

    }

	

    void MainLoop()
    {
		
        while(IsRunning)
        {

            fps.updateD();
			UpdateFrame();
            fps.updateI();
        }
		Cleaner();
    }

public:
	virtual void UpdateFrame() = 0;
	//overload
	void ClearScreen()
	{
		memset(scrbuffer, ' ', scrsz.X * scrsz.Y*(sizeof(char)));
	}
	void ClearScreen(const COORD& topLeft, const COORD& botRight)
	{
		memset(&scrbuffer[topLeft.X + (topLeft.Y * scrsz.X)], ' ', botRight.X * botRight.Y);
	}




	void FillScreen(const char& ch)
	{
		memset(scrbuffer, ch, scrsz.X * scrsz.Y*(sizeof(char)));
	}
	void FillScreen(const char& ch, const COORD& topLeft, const COORD& botRight)
	{
		memset(&scrbuffer[topLeft.X + (topLeft.Y * scrsz.X)], ch, botRight.X * botRight.Y);
	}


	void DrawScreen(const COORD& topLeft, const COORD& botRight)
	{
		DWORD dwBytesWritten;
		WriteConsoleOutputCharacter(hdle, scrbuffer, botRight.X * botRight.Y * sizeof(char), topLeft, &dwBytesWritten);
	}
	void DrawScreen()
	{
		DWORD dwBytesWritten;
		WriteConsoleOutputCharacter(hdle, scrbuffer, scrsz.X * scrsz.Y * sizeof(char), {0,0}, &dwBytesWritten);
	}

	//DDA line drawing algorith
    void CreateLines_DDA(const LPoints &lpoints , const char &cChar)
    {
            short Steps = 0;
            Points def = lpoints.p2 - lpoints.p1;
            float incrementX = lpoints.p1.X, incrementY = lpoints.p1.Y;

            if(abs(def.X) > abs(def.Y))
                Steps = abs(def.X);
            else
                Steps = abs(def.Y);


            for(short i =0; i < Steps; i++)
            {

                incrementX += (float)def.X/Steps;
                incrementY += (float)def.Y/Steps;
                scrbuffer[util::RoundOff(incrementX)+util::RoundOff(incrementY)*scrsz.X] = cChar;
            }

    }

	
    void DisplayText(const char*chtxt,const COORD& pos)
    {
        memcpy(&scrbuffer[pos.X + pos.Y * scrsz.X],chtxt,strlen(chtxt));
    }

	//overload
    void DisplayText(const std::string chtxt,const COORD& pos )
    {
        memcpy(&scrbuffer[pos.X + pos.Y * scrsz.X],&chtxt,chtxt.size());
    }


	void DrawAsciiArt(const AsciiArt& art, const COORD& pos)
	{
		for (short y = 0; y < art.sz.Y; y++)
		{
			memcpy(&scrbuffer[pos.X + ((y + pos.Y) * scrsz.X)], &art.graphics[0 + y * art.sz.X],art.sz.X);
		}
	}
	//overload
	void DrawAsciiArt(AsciiArt& art)
	{
		char * graphics = &art.graphics[0];
		for (short y = 0; y < art.sz.Y; y++)
		{
			memcpy(&scrbuffer[art.Pos.X + ((y + art.Pos.Y) * scrsz.X)], &graphics[0 + y * art.sz.X], art.sz.X);
		}
	}

	


};*/


}

/*
namespace key
{

	enum keycode
	{
		A = 0x41, B, C, D, E, F,
		G, H, I, J, K, L, M, N, O, P,
		Q, R, S, T, U, V, W, X, Y, Z
	};

	typedef struct _keystroke
	{
		
		int keycode;
		int iDelay;
	
		_keystroke(const int& kycd, const unsigned int& delay)
		{
			keycode = kycd;
			iDelay = delay;
		}

		_keystroke(const int & kycd)
		{
			keycode = kycd;
			iDelay = 5;
		}

		bool IsKbhit()
		{
			if (iDelay == 0)
				iDelay = 1;
			if (GetAsyncKeyState(keycode) % iDelay != 0)
			{
				return true;
			}
			
			return false;
		}

		bool IsKbhit(TextDisplay* clasS)
		{
			if (GetAsyncKeyState(keycode) != 0 && clasS->fps.tickframes % iDelay == 0)
			{
				
				return true;
			}
			
			return false;
		}

		
		bool IsKbhit(txt::util::UtilTimer& timer)
		{
			if (GetAsyncKeyState(keycode) != 0 && timer.IsTimesUp(iDelay))
			{
				
				return true;
			}
			
				
			return false;
		}

		

	}keystroke;

}


*/
#endif // ASCII_GRAP_H
