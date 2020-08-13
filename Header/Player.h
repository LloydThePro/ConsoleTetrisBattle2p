#ifndef PLAY_MAP
#define PLAY_MAP

#include "UtilStructs.h"
#include <cstdlib>
#include <ctime>





class Player
{
private:
	list * CurrentRotation = nullptr;
	list * nPrevRotation = nullptr;
	
	std::string Tetrominos[7];
	byte isFilled[12 * 20];
	list * nMaxRotation = nullptr;
	std::string ClearPlayGround;
	bool isActive = true;
	list Rotations[4];
	short ControlMode = 0;
	
	byte nCurrent = 6;
	AsciiArt CurrentTetro;
	char * cptr = &PlayGround.graphics[0];
	char * ptr = &ClearPlayGround[0];
	char * Playgroundptr = nullptr;
	char * CurrentTetroPtr = nullptr;
public:
	bool isGameOver = false;
	Player * Enemy = nullptr;
	byte nHold = 8;
	AsciiData holdbar;
	AsciiData HoldTetro;
	AsciiData OnGameOverScreen;
	int nFallSpeedDelay = 700;
	AsciiArt PlayGround;
	vec2i CurrentPos = { 3, -4 };
	int nScore = 0;
public:
	Player(int x, int y, int mode);
	void Input();
	void Update();
	void Reset();
private:
	void AddLines(byte);
	void RemoveLines(byte);
	void isThereABomb();
	void EmbedTetroObj();
	bool DoesItFit();
	void EmbedTetro();
	void FillBlock();
	void RotateTetro(int);
	bool isWall();
	void CheckLines();
	
};





#endif
