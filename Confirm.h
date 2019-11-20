#pragma once

#include "Graphics.h"
#include "Constant.h"
#include "LIST.h"

char* char_formartText(char *text);
char* char_substr(char *Source, unsigned int lcCut, unsigned int quantity);
char* dataEntry(char *text, LOCATION lc, int mode, int maxLength);
bool dateIsTrue(int day, int month, int year);
void converDateToArrDate(char *date, LIST_ARRAY_CHAR &dateResult);
bool conf_dateIsBetween(LIST_ARRAY_CHAR dateDock, LIST_ARRAY_CHAR dateCompare);
bool conf_checkDATE(LIST_ARRAY_CHAR lDate);