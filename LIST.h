#pragma once

#include <string>
#include <string.h>

struct LOCATION
{
	int x;
	int y;
};

struct Size
{
	int width;
	int height;
};

struct TITLE
{
	char data[51];
	int width;
};

struct VARIABLES
{
	int color;
	char notify[51];
	char name[51];
	char data[51];
};

struct MODE
{
	int modeImport;
	bool enable;
};

struct PROPERTIES
{
	VARIABLES variables;
	MODE mode;
	int maxLength;
};

struct LIST_PROPERTIES
{
	int size = 0;
	PROPERTIES *lprop = new PROPERTIES[size];
};

struct STR
{
	char str[100];
};

struct LIST_ARRAY_CHAR
{
	int size = 0;
	STR *listSTR = new STR[size];
};

struct LIST_LOCATION
{
	int size = 0;
	LOCATION *lloca = new LOCATION[size];
};

struct LIST_TITLE
{
	int size = 0;
	TITLE *ltitle = new TITLE[size];
};


void List_Reset(LIST_ARRAY_CHAR &list);
void List_Reset(LIST_PROPERTIES &list);

void List_Clear(LIST_PROPERTIES &list);
void List_Clear(LIST_ARRAY_CHAR &list);
void List_Clear(LIST_LOCATION &list);
void List_Clear(LIST_TITLE &list);

bool List_InsertItem(LIST_PROPERTIES &list, int LOCATIONAdd, PROPERTIES data);
bool List_DeleteItem(LIST_PROPERTIES &list, int LOCATIONDelete);

bool List_InsertItem(LIST_ARRAY_CHAR &list, int LOCATIONAdd, char data[]);
bool List_DeleteItem(LIST_PROPERTIES &list, int LOCATIONDelete);

bool List_InsertItem(LIST_LOCATION &list, int LOCATIONAdd, LOCATION data);
bool List_DeleteItem(LIST_LOCATION &list, int LOCATIONDelete);

bool List_InsertItem(LIST_TITLE &list, int LOCATIONAdd, TITLE data);
bool List_DeleteItem(LIST_TITLE &list, int LOCATIONDelete);
