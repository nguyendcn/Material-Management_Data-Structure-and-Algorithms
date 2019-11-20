#pragma once

#include "LIST.h"
#include "Graphics.h"
#include "Constant.h"
#include "Confirm.h"

void dis_wait(LOCATION lcDisplay, char *caption, int time, int color);
void dis_Clear(LOCATION lcHeadClear, Size size);
void drawRectangle(LOCATION &result, LOCATION lc, Size s, int colorBG, int colorBorder);
void drawBox(LOCATION lcDisplay, Size size, char *caption);
void drawBorder(LIST_LOCATION &lcResult, LOCATION displayLC, int rowQunatity, int heightOne, LIST_TITLE title);
void button(bool isFocus, char *text, LOCATION lc, Size sizeBTN, int colorFocus, int colornFocus);
bool messagebox(char *content, int notifyButton, LOCATION lc);
void hButton(int text, int x, int y);
void enterDataToVariable(LIST_ARRAY_CHAR &dataVariables, LIST_PROPERTIES prop, LOCATION displayLC);
void dis_drawEntryDate(LIST_LOCATION &lLocationGetData, LIST_ARRAY_CHAR quantityEntry);