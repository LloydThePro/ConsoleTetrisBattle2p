#include "Player.h"
#include "MenuSystem.h"
#include "DebugCode.h"
#include "Renderer.h"
#include "UtilityCharConverter.h"

/*UNFINISHED*/

class Tetris : public TextDisplay
{
private:
	Player** playerptr = nullptr;
	byte nCurrentEvent = 5;
	MenuSystem startMenu = MenuSystem("Assets/Menu_Start.txt", { 12, 7 }, { scrsz.X/2, scrsz.Y/2 }, { 2 , 2});
	char buffer[16] = "SCORE:";
	char buffer2[15] = "AVE:";
	AverageFrames ave;
	short timeming = 1;
	AnimSys Anims = AnimSys(11, { 12,3 }, {30,20});
	byte nFrame = 0;

private:
	void Init2pMode()
	{
		playerptr[0]->Enemy = playerptr[1];
		playerptr[1]->Enemy = playerptr[0];

		playerptr[0]->Reset();
		playerptr[1]->Reset();
	}

	void Init1pMode()
	{
		playerptr[0]->Enemy = nullptr;
		playerptr[0]->Reset();
	}




public:
	Tetris()
	{
		fps.frames = 1;
		fps.tickframes = 1;
		InitTextDisplay(WR_TextMode_Med, { 100, 40 });
		Anims.LoadAnimFromFile("Assets/Anim.txt");

		playerptr = new Player*[2];
		srand(time(0));
		playerptr[0] = new Player(20, 10, WASD);
		srand(rand() * 4);
		playerptr[1] = new Player(50, 10, UDLR);
		startMenu.MenuGUI.Pos = { scrsz.X / 2 - 8, scrsz.Y / 2 - 6 };
		timeming = (playerptr[0]->nFallSpeedDelay * 0.4) + (fps.tickframes * 0.4) * 0.4;
		
	}
	~Tetris()
	{
		for (int i = 0; i < 2; i++)
			delete playerptr[i];

		Anims.FreeMem();

		if (playerptr != nullptr)
			delete[] playerptr;
	}
	void UpdateFrame()override
	{
		TextDisplay::ClearScreen();
		

		if (fps.elapseTime >= 1)
		{
			IntToStr(&Title[11], fps.frames);
			SetConsoleTitle(Title);
			ave.ResetAveFrames(fps.frames, 40);
			IntToStr(&buffer2[4], ave.Average);
			timeming = (playerptr[0]->nFallSpeedDelay * 0.4) + (fps.tickframes * 0.4) * 0.2;
			if (nCurrentEvent == 5) nCurrentEvent = 3;

		}

		
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		/*
			Event System
		*/

		switch (nCurrentEvent)
		{
 //----------------------------------------------------------------------------
		/*On Menu*/
		case 0:

			switch (startMenu.MenuInputs(WASD, VERTICAL, { 2,4 }, { 0,0 }))
			{
			case 2:
				nCurrentEvent = 1;
				Init2pMode();
				break;
			case 3:
				nCurrentEvent = 2;
				Init1pMode();
				break;
			case 4:
				nCurrentEvent = 3;
				break;
			}



			//Renders menuGUI
			DrawAsciiArt(startMenu.MenuGUI);
			
			
			break;
		
	//----------------------------------------------------------------------------

	

		/*Versus Mode*/
		case 1:

			for (int i = 0; i < 2; i++)
			{
				

				IntToStr(&buffer[6], playerptr[i]->nScore);
				DisplayText(buffer, { 0, (short)i });

				playerptr[i]->Update();
				DrawAsciiArt(playerptr[i]->PlayGround);
				DrawAsciiArt(playerptr[i]->holdbar);

				if (playerptr[i]->nHold < 7)
					DrawAsciiArt(playerptr[i]->HoldTetro);

				if (playerptr[i]->isGameOver)
				{
					DrawAsciiArt(playerptr[i]->OnGameOverScreen);
				}


				if (fps.tickframes % (timeming + playerptr[i]->nFallSpeedDelay) == 0)
				{
					playerptr[i]->CurrentPos.Y++;
				}

				if (playerptr[0]->isGameOver && playerptr[1]->isGameOver)
				{
					nCurrentEvent = 0;
				}
				
			}
			TextDisplay::DisplayText(buffer2, { 0, 5 });
			break;
	

	//----------------------------------------------------------------------------
	/*Single player*/
		case 2:
			
			IntToStr(&buffer[6], playerptr[0]->nScore);
			DisplayText(buffer, { 0, (short)0 });

			playerptr[0]->Update();
			DrawAsciiArt(playerptr[0]->PlayGround);
			DrawAsciiArt(playerptr[0]->holdbar);

			if (playerptr[0]->nHold < 7)
				DrawAsciiArt(playerptr[0]->HoldTetro);


			if (fps.tickframes % (timeming + playerptr[0]->nFallSpeedDelay) == 0)
			{
				playerptr[0]->CurrentPos.Y++;
			}

			if (playerptr[0]->isGameOver)
				nCurrentEvent = 0;

			TextDisplay::DisplayText(buffer2, { 0, 5 });
			break;

	//----------------------------------------------------------------------------

		/*OnPause*/
		case 3:
			/*Animate(Anims, nFrame);
			if (fps.tickframes % fps.frames == 0)
				nFrame++;
			if (nFrame > Anims.frames.nFrames - 1) nCurrentEvent = 0;
			break;*/

	//----------------------------------------------------------------------------

	//----------------------------------------------------------------------------

	/*Loading Animation*/
		case 4:
			Animate(Anims, nFrame);
			if (fps.tickframes % 5000 == 0)
				nFrame++;
			if (nFrame > Anims.frames.nFrames - 1) nCurrentEvent = 0;
			break;

			//----------------------------------------------------------------------------


		}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



		TextDisplay::DrawScreen();
	}
};



int main()
{
	Tetris tetris;tetris.MainLoop();return 0;
}

