#ifndef UTIL_CHAR_CONVERTER_H
#define UTIL_CHAR_CONVERTER_H
#include <string>
char IntToChar(const int& a);
void IntToStr(char * cptr, int n);
void IntToStr(std::string& cptr, int n);
int CharToInt(const char& a);
void FloatToStr(char * chr, const float& n);
void FloatToStr(char * chr, const double& n);
#endif // UTIL_CHAR_CONVERTER_H

