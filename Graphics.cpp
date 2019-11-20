#include "Graphics.h"

void gotoxy(int x, int y)
{
	COORD co = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), co);
}

int wherex(void)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X;
}

int wherey(void)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y;
}

void TextColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void setBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
void AnConTro()
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}
void HienConTro()
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = TRUE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}
void TextBT(int xGoc, int yGoc, int xDich, int yDich, char *InPut, int Delay, int Color, int Space)
{
	int i, j = 0;
	TextColor(Color);
	if (xGoc == xDich && yGoc > yDich && Space == 1)
	{
		for (j = 0; j <= static_cast<int>(strlen(InPut)); j++)
		{
			if (InPut[j] != 32)
				for (i = yGoc; i >= yDich; i--)
				{
					gotoxy(xGoc, i);       _putch(InPut[j]);
					gotoxy(xGoc, i + 1);   _putch(' ');
					Sleep(Delay);
				}
			else
			{
				gotoxy(xGoc, yDich);       _putch(' ');
			}
			xGoc++;
		}
	}

	if (yDich == yGoc && xGoc > xDich && Space == 1)
	{
		for (j = 0; j <= static_cast<int>(strlen(InPut)); j++)
		{
			if (InPut[j] != 32)
				for (i = xGoc; i >= xDich; i--)
				{
					gotoxy(i, yGoc);     cout << InPut[i];
					Sleep(Delay);
				}
			else { gotoxy(xGoc, yDich);     _putch(' '); }
			xDich++;
		}

	}
}

void ColorText(int number, int Color)
{
	TextColor(Color);
	cout << number;
	TextColor(7);
}
void ColorText(char Text, int Color)
{
	TextColor(Color);
	cout << Text;
	TextColor(7);
}
void ColorText(string Text, int Color)
{
	TextColor(Color);
	cout << Text;
	TextColor(7);
}

void BGColorText(char *text, int colorText, int colorBG)
{
	setBGColor(colorBG);
	TextColor(colorText);
	cout << text;
	TextColor(7);
	setBGColor(0);
}

void BGColorText(const char *text, int colorText, int colorBG)
{
	setBGColor(colorBG);
	TextColor(colorText);
	cout << text;
	TextColor(7);
	setBGColor(0);
}