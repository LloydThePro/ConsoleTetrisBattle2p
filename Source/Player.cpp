#include "Player.h"


Player::Player(int x, int y, int mode)
{
	
	CurrentTetro.sz = { 4,4 };
	HoldTetro.sz = { 4,4 };
	HoldTetro.Pos = { (short)x - 4, (short)y+1 };
	ControlMode = mode;
	for (byte i = 0; i < 4; i++)
	{
		if (i < 3)
			Rotations[i].next = &Rotations[i + 1];
		else
			Rotations[i].next = &Rotations[0];

		if (i > 0)
			Rotations[i].prev = &Rotations[i - 1];
		else
			Rotations[i].prev = &Rotations[3];


		Rotations[i].val = i * 90;
	}
	holdbar.graphics =
		"-HOLD-"
		"|    |"
		"|    |"
		"|    |"
		"|    |"
		"******";
	holdbar.sz = { 6,6 };
	holdbar.Pos = {(short) x - 6,(short)y};
	CurrentRotation = &Rotations[0];
	nPrevRotation = CurrentRotation;
	PlayGround.Pos = { (short)x, (short)y };
	PlayGround.sz = { 12, 20 };
	PlayGround.graphics =
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"*          *"
		"************"
		;
	ClearPlayGround = PlayGround.graphics;
	Tetrominos[0] =
		"  # "
		" ###"
		"    "
		"    ";
	Tetrominos[1] =
		"  # "
		"  # "
		" ## "
		"    ";
	Tetrominos[2] =
		" #  "
		" #  "
		" ## "
		"    ";
	Tetrominos[3] =
		"    "
		" ## "
		" ## "
		"    ";
	Tetrominos[4] =

		"  # "
		"  # "
		"  # "
		"  # ";
	Tetrominos[5] =
		"##  "
		" ## "
		"    "
		"    ";
	Tetrominos[6] =
		" ## "
		"##  "
		"    "
		"    ";
	nCurrent = rand() % 7;
	cptr = &PlayGround.graphics[0];
	ptr = &ClearPlayGround[0];
	
	CurrentTetro.graphics = Tetrominos[nCurrent];
	CurrentTetroPtr = &CurrentTetro.graphics[0];
	Playgroundptr = &PlayGround.graphics[0];




	OnGameOverScreen.sz = { 20,8 };
	OnGameOverScreen.Pos = { PlayGround.Pos.X , PlayGround.Pos.Y + 5};
	LoadDataFromFile(OnGameOverScreen, "Assets/GameOver.txt");




	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 12; x++)
			if (Playgroundptr[x + y * 12] == '*')
				isFilled[x + (y * 12)] = 3;

}

void Player::Input()
{
	
	
	if (nCurrent > 2)
		nMaxRotation = &Rotations[1];
	else
		nMaxRotation = &Rotations[3];


	//PlayGround.graphics = ClearPlayGround;
	memcpy(cptr, ptr, PlayGround.sz.X * PlayGround.sz.Y);
	



	switch (ControlMode)
	{

		//For up down left right
	case UDLR:
		if (GetAsyncKeyState(VK_RIGHT) & 0x1)
		{
			CurrentPos.X++;
			if (!DoesItFit())
				CurrentPos.X--;
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x1)
		{

			CurrentPos.X--;
			if (!DoesItFit())
				CurrentPos.X++;
		}


		if (GetAsyncKeyState(VK_UP) & 0x1)
		{

			nPrevRotation = CurrentRotation;
			CurrentRotation = CurrentRotation->prev;
			Player::RotateTetro(CurrentRotation->val);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x1)
		{

			nPrevRotation = CurrentRotation;
			CurrentRotation = CurrentRotation->next;
			Player::RotateTetro(CurrentRotation->val);
		}


		if (GetAsyncKeyState(VK_RSHIFT) & 0x1)
		{
			while (DoesItFit())
			{
				CurrentPos.Y++;
			}

		}

		if (GetAsyncKeyState(VK_RCONTROL) & 0x1)
		{
			if (nHold < 0 && nHold >= 6)
			{
				nHold = nCurrent;
				HoldTetro.graphics = Tetrominos[nHold];

			}
			else
			{
				byte temp = nHold;
				nHold = nCurrent;
				HoldTetro.graphics = Tetrominos[nHold];
				if (temp < 7)
				{
					nCurrent = temp;
					CurrentTetro.graphics = Tetrominos[nCurrent];
				}
				else
				{
					nCurrent = rand() % 7;
					CurrentTetro.graphics = Tetrominos[nCurrent];
					Player::RotateTetro(CurrentRotation->val);
					CurrentPos.Y = -2;
					CurrentPos.X = 6;
				}
			}
		}

		break;

	//For WASD inputs
	case WASD:
		if (GetAsyncKeyState(68) & 0x1)
		{
			CurrentPos.X++;
			if (!DoesItFit())
				CurrentPos.X--;
		}

		if (GetAsyncKeyState(65) & 0x1)
		{

			CurrentPos.X--;
			if (!DoesItFit())
				CurrentPos.X++;
		}


		if (GetAsyncKeyState(87) & 0x1)
		{

			nPrevRotation = CurrentRotation;
			CurrentRotation = CurrentRotation->prev;
			Player::RotateTetro(CurrentRotation->val);

		}

		if (GetAsyncKeyState(83) & 0x1)
		{
			nPrevRotation = CurrentRotation;
			CurrentRotation = CurrentRotation->next;
			Player::RotateTetro(CurrentRotation->val);
		}


		if (GetAsyncKeyState(VK_SPACE) & 0x1)
		{
			while (DoesItFit())
			{
				CurrentPos.Y++;
			}
				

		}

		if (GetAsyncKeyState(VK_LSHIFT) & 0x1)
		{
			
			
			if (nHold < 0 && nHold >= 6)
			{
				nHold = nCurrent;
				HoldTetro.graphics = Tetrominos[nHold];
				
			}
			else
			{
				byte temp = nHold;
				nHold = nCurrent;
				HoldTetro.graphics = Tetrominos[nHold];
				if (temp < 7)
				{
					nCurrent = temp;
					CurrentTetro.graphics = Tetrominos[nCurrent];
				}
				else
				{
					nCurrent = rand() % 7;
					CurrentTetro.graphics = Tetrominos[nCurrent];
					Player::RotateTetro(CurrentRotation->val);
					CurrentPos.Y = -2;
					CurrentPos.X = 6;
				}
			}
		}


		if (GetAsyncKeyState(VK_F1) & 0x1)
		{
			Player::AddLines(5);
			//Player::Reset();
		}
		

		break;

	default:
		break;
	}
	


	if (isWall() && CurrentPos.X > 6)
		CurrentPos.X--;
	if (isWall() && CurrentPos.X < 6)
		CurrentPos.X++;

	/*if (CurrentPos.Y < 0)
		CurrentPos.Y = 0;*/

	
	//Player::RotateTetro(CurrentRotation->val);


	EmbedTetro();
}

void Player::EmbedTetroObj()
{

	if (!isActive)
	{
		Player::isThereABomb();
		for (byte y = 0; y < 4; y++)
			for (byte x = 0; x < 4; x++)
			{
				if (CurrentTetroPtr[x + y * 4] != ' ')
				{
					if ((y + CurrentPos.Y > -1 && y + CurrentPos.Y < 20))
					{
						cptr[(x + CurrentPos.X) + ((y + CurrentPos.Y) * 12)] = CurrentTetroPtr[x + y * 4];
						isFilled[(x + CurrentPos.X) + ((y + CurrentPos.Y) * 12)] = 1;
					}
					else
					{
						isGameOver = true;
						return;
					}
						
					
					
				}

			}

		

		nCurrent = rand() % 7;
		isActive = true;
		CurrentPos.Y = -2;
		CurrentPos.X = 6;
		Player::RotateTetro(CurrentRotation->val);
	
	}

}

bool Player::DoesItFit()
{
	
	for (byte y = 0; y < 4; y++)
		for (byte x = 0; x < 4; x++)
		{
			if (CurrentTetroPtr[x + (y * 4)] != ' ')
			{
				if ((bool)isFilled[(x + CurrentPos.X) + ((y + CurrentPos.Y) * 12)])
					return false;
			}

		}
	return true;
}

void Player::EmbedTetro()
{
	
	for (byte y = 0; y < 4; y++)
		for (byte x = 0; x < 4; x++)
		{
			if (CurrentTetroPtr[x + y * 4] != ' ')
			{
				if(y + CurrentPos.Y > -1)
					Playgroundptr[(x + CurrentPos.X) + ((y + CurrentPos.Y) * 12)] = CurrentTetroPtr[x + y * 4];
			}
		}
}

void Player::FillBlock()
{
	
	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 12; x++)
			if (isFilled[x + (y * 12)] == 1)
				Playgroundptr[x + (y * 12)] = (char)254;
			else if (isFilled[x + (y * 12)] == 2)
				Playgroundptr[x + (y * 12)] = (char)1;
			else if (isFilled[x + (y * 12)] == 3)
				Playgroundptr[x + (y * 12)] = (char)219;
			else if (x == 0 || x == 11 || y == 19)
				Playgroundptr[x + (y * 12)] = '#';
}

void Player::RotateTetro(int nRotation)
{

	char sample[4 * 4];
	switch (nRotation)
	{
	case 0:
		CurrentTetro.graphics = Tetrominos[nCurrent];
		break;
	case 90:
		
		for (byte y = 0; y < 4; y++)
			for (byte x = 0; x < 4; x++)
			{
				sample[x + (y * 4)] = Tetrominos[nCurrent][x + ((3 - y) * 4)];
				CurrentTetroPtr[y + (x * 4)] = sample[x + (y * 4)];
			}
		
		break;
	case 180:
		
		for (byte y = 0; y < 4; y++)
			for (byte x = 0; x < 4; x++)
			{
				sample[x + (y * 4)] = Tetrominos[nCurrent][(3 - y) + ((3 - x) * 4)];
				CurrentTetroPtr[y + (x * 4)] = sample[x + (y * 4)];
			}
		break;
	case 270:
		
		for (byte y = 0; y < 4; y++)
			for (byte x = 0; x < 4; x++)
			{
				sample[x + (y * 4)] = Tetrominos[nCurrent][(3 - y) + (x * 4)];
				CurrentTetroPtr[x + (y * 4)] = sample[x + (y * 4)];
			}
		break;

	}

	
}
bool Player::isWall()
{
	
	for (byte y = 0; y < 4; y++)
		for (byte x = 0; x < 4; x++)
		{
			if (CurrentTetroPtr[x + (y * 4)] != ' ')
			{
				if ((CurrentPos.X + x) == 0 || (CurrentPos.X + x) == 11)
					return true;
			}
		}


	return false;
}
//Erases lines when it is completed
void Player::CheckLines()
{
	int nLines = 0;
	for (int y = 18; y > 0; y--)
	{
		bool isLine = true;
		for (int x = 1; x < 11; x++)
		{
			//Move to EmbedTetroObj()
			/*if ((y < 3) && (isFilled[x + (y * 12)] == 1))
			{
				isGameOver = true;
			}*/
			

			if (isFilled[x + (y * 12)] == 0 || isFilled[x + (y * 12)] > 1)
			{
				isLine = false;
				break;
			}
				

		}
		if (isLine)
		{
			nLines++;

			for (int Y = y; Y > 0; Y--)
				memcpy(&isFilled[1 + (Y * 12)], &isFilled[1 + ((Y - 1) * 12)], sizeof(byte) * 12);

		}

	}
	nScore += nLines * 10;

	//Throws lines to the enemy... if there is
	if (Enemy != nullptr)
		Enemy->AddLines(nLines);

}
void Player::AddLines(byte nLines)
{
	byte bombloc = 2;
	for (byte i = 0; i < nLines; i++)
	{
		for (byte y = 2; y < 19; y++)
		{
			memcpy(&isFilled[1 + ((y - 1) * 12)], &isFilled[1 + (y * 12)], sizeof(byte) * 10);
			memset(&isFilled[1 + (y * 12)], 0, sizeof(byte) * 10);
		}
		memset(&isFilled[1 + (18 * 12)], 1, sizeof(byte) * 10);
		isFilled[(1 + rand() % 10) + (18 * 12)] = 2;
	}
		
	
}
void Player::RemoveLines(byte yLoc)
{
	memset(&isFilled[1 + (yLoc * 12)], 1, sizeof(byte) * 10);
}
void Player::isThereABomb()
{
	//char * Tetros = &CurrentTetro.graphics[0];
	for(byte y = 0; y < 4; y++)
		for (byte x = 0; x < 4; x++)
		{
			if (CurrentTetroPtr[x + y * 4] != ' ')
			{
				if (isFilled[(x + CurrentPos.X) + (y + CurrentPos.Y) * 12] == 2)
				{
					RemoveLines(y + CurrentPos.Y);


					//For loop check for bombs that are below existing bomb
					for (byte r = y + 1; r < 18; r++)
					{
						if (isFilled[(x + CurrentPos.X) + (r + CurrentPos.Y) * 12] == 2)
						{
							RemoveLines(r + CurrentPos.Y);
						}
						else
							return;
					}

					//isFilled[(x + CurrentPos.X) + (y + CurrentPos.Y) * 12] == 1;
					return;
				}

				else if (isFilled[(x + CurrentPos.X) + (y + CurrentPos.Y + 1) * 12] == 2)
				{
					RemoveLines(y + CurrentPos.Y + 1);

					for (byte r = y + 2; r < 18; r++)
					{
						if (isFilled[(x + CurrentPos.X) + (r + CurrentPos.Y) * 12] == 2)
						{
							RemoveLines(r + CurrentPos.Y);
						}
						else
							return;
					}

					//isFilled[(x + CurrentPos.X) + (y + CurrentPos.Y + 1) * 12] == 1;
					return;
				}
			}
		}
	
}
void Player::Update()
{
	if (!Player::isGameOver)
	{
		Player::Input();
		if (!Player::DoesItFit() && !Player::isWall() && CurrentPos.Y > -1)
		{

			while (!Player::DoesItFit())
			{

				CurrentPos.Y--;
			}
			//Player::isThereABomb();
			isActive = false;
		}
		Player::EmbedTetroObj();
		Player::CheckLines();
		Player::FillBlock();
	}
	/*else
		Reset();*/

}
void Player::Reset()
{
	for (int y = 0; y < 19; y++)
		memset(&isFilled[1 + y * 12], 0, 10);


	nScore = 0;
	nCurrent = rand() % 7;
	isActive = true;
	isGameOver = false;
	CurrentPos.Y = -2;
	CurrentPos.X = 6;
	nHold = 7;
	Player::RotateTetro(CurrentRotation->val);

}