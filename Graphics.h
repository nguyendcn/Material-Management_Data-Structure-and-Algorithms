#pragma once

#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <MMSystem.h>
#include <ctime>
#include <fstream>
#include <string.h>

using namespace std;

void gotoxy(int x, int y);
int wherex();
int wherey();
void TextColor(WORD color);
void setBGColor(WORD);
void resizeConsole(int width, int height);
void clrscr();
void AnConTro();
void HienConTro();
void TextBT(int xGoc, int yGoc, int xDich, int yDich, char *InPut, int Delay, int Color, int Space);
void ColorText(int, int);
void ColorText(char, int);
void ColorText(string, int);
void BGColorText(char *text, int colorText, int colorBG);
void BGColorText(const char *text, int colorText, int colorBG);