#ifndef DEF_
#define DEF_
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#define WASD 0x1
#define UDLR 0x2

#define VERTICAL 0x1
#define HORIZONTAL 0x2
typedef unsigned char byte;
typedef struct _AsciiData
{
	std::string graphics;
	COORD sz;
	COORD Pos;
}AsciiArt, AsciiData;
typedef struct _Points
{
	short int X;
	short int Y;
}Points;
typedef struct _LinePoints
{
	Points p1;
	Points p2;
}LPoints;
struct vec2i
{
	int X;
	int Y;
};
struct vec2s
{
	short X;
	short Y;
};
struct vec2by
{
	byte X;
	byte Y;
};
struct list
{
	list * next = nullptr;
	list * prev = nullptr;
	int val = 0;
};
typedef unsigned char byte;
typedef char * str;
bool LoadDataFromFile(AsciiArt& art, const char * filename);
//Overload
bool LoadDataFromFile(AsciiArt& art, const std::string& filename);
Points operator-(const Points &p1, const Points &p2);

#endif // !DEF_