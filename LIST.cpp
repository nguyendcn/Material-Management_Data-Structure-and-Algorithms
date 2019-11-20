#include "LIST.h"

#pragma region Realloc in here

void REALLOC(PROPERTIES *&list, int oldSize, int newSize)
{
	PROPERTIES *temp = new PROPERTIES[oldSize];

	for (int i = 0; i < oldSize; i++)
	{
		temp[i] = list[i];
	}

	delete[] list;

	list = new PROPERTIES[newSize];

	int min = oldSize < newSize ? oldSize : newSize;

	for (int i = 0; i < min; i++)
	{
		list[i] = temp[i];
	}

	delete[] temp;
}

void REALLOC(STR *&list, int oldSize, int newSize)
{
	STR *temp = new STR[oldSize];

	for (int i = 0; i < oldSize; i++)
	{
		temp[i] = list[i];
	}

	delete[] list;

	list = new STR[newSize];

	int min = oldSize < newSize ? oldSize : newSize;

	for (int i = 0; i < min; i++)
	{
		list[i] = temp[i];
	}

	delete[] temp;
}

void REALLOC(LOCATION *&list, int oldSize, int newSize)
{
	LOCATION *temp = new LOCATION[oldSize];

	for (int i = 0; i < oldSize; i++)
	{
		temp[i] = list[i];
	}

	delete[] list;

	list = new LOCATION[newSize];

	int min = oldSize < newSize ? oldSize : newSize;

	for (int i = 0; i < min; i++)
	{
		list[i] = temp[i];
	}

	delete[] temp;
}

void REALLOC(TITLE *&list, int oldSize, int newSize)
{
	TITLE *temp = new TITLE[oldSize];

	for (int i = 0; i < oldSize; i++)
	{
		temp[i] = list[i];
	}

	delete[] list;

	list = new TITLE[newSize];

	int min = oldSize < newSize ? oldSize : newSize;

	for (int i = 0; i < min; i++)
	{
		list[i] = temp[i];
	}

	delete[] temp;
}

#pragma endregion

#pragma region Check

bool List_IsEmpty(LIST_PROPERTIES list)
{
	return list.size == 0;
}

bool List_IsEmpty(LIST_ARRAY_CHAR list)
{
	return list.size == 0;
}

bool List_IsEmpty(LIST_LOCATION list)
{
	return list.size == 0;
}

bool List_IsEmpty(LIST_TITLE list)
{
	return list.size == 0;
}

#pragma endregion

#pragma region Reset
void List_Reset(LIST_PROPERTIES &list)
{
	list.size = 0;
	delete list.lprop;
	list.lprop = new PROPERTIES[list.size];
}

void List_Reset(LIST_ARRAY_CHAR &list)
{
	list.size = 0;
	delete list.listSTR;
	list.listSTR = new STR[list.size];
}
#pragma endregion


#pragma region Clear list

void List_Clear(LIST_PROPERTIES &list)
{
	list.size = 0;
	delete[] list.lprop;
}

void List_Clear(LIST_ARRAY_CHAR &list)
{
	list.size = 0;
	delete[] list.listSTR;
}

void List_Clear(LIST_LOCATION &list)
{
	list.size = 0;
	delete[] list.lloca;
}

void List_Clear(LIST_TITLE &list)
{
	list.size = 0;
	delete[] list.ltitle;
}

#pragma endregion

#pragma region Method insert

bool List_InsertItem(LIST_PROPERTIES &list, int LOCATIONAdd, PROPERTIES data)
{
	if (LOCATIONAdd < 0 || LOCATIONAdd > list.size /*|| isFull(list)*/)
	{
		return false;
	}

	REALLOC(list.lprop, list.size, list.size + 1);

	for (int i = list.size - 1; i >= LOCATIONAdd; i--)
	{
		list.lprop[i + 1] = list.lprop[i];
	}

	list.lprop[LOCATIONAdd] = data;
	list.size++;
	return true;
}

bool List_InsertItem(LIST_ARRAY_CHAR &list, int LOCATIONAdd, char data[])
{
	if (LOCATIONAdd < 0 || LOCATIONAdd > list.size /*|| isFull(list)*/)
	{
		return false;
	}
	REALLOC(list.listSTR, list.size, list.size + 1);

	for (int i = list.size - 1; i >= LOCATIONAdd; i--)
	{
		strcpy_s(list.listSTR[i + 1].str, list.listSTR[i].str);
	}

	strcpy_s(list.listSTR[LOCATIONAdd].str, data);
	list.size++;
	return true;
}

bool List_InsertItem(LIST_LOCATION &list, int LOCATIONAdd, LOCATION data)
{
	if (LOCATIONAdd < 0 || LOCATIONAdd > list.size /*|| isFull(list)*/)
	{
		return false;
	}
	REALLOC(list.lloca, list.size, list.size + 1);

	for (int i = list.size - 1; i >= LOCATIONAdd; i--)
	{
		list.lloca[i + 1] = list.lloca[i];
	}

	list.lloca[LOCATIONAdd] = data;
	list.size++;
	return true;
}

bool List_InsertItem(LIST_TITLE &list, int LOCATIONAdd, TITLE data)
{
	if (LOCATIONAdd < 0 || LOCATIONAdd > list.size /*|| isFull(list)*/)
	{
		return false;
	}
	REALLOC(list.ltitle, list.size, list.size + 1);

	for (int i = list.size - 1; i >= LOCATIONAdd; i--)
	{
		strcpy_s(list.ltitle[i + 1].data, list.ltitle[i].data);
		list.ltitle[i + 1].width = list.ltitle[i].width;
	}

	strcpy_s(list.ltitle[LOCATIONAdd].data, data.data);
	list.ltitle[LOCATIONAdd].width = data.width;

	list.size++;
	return true;
}

#pragma endregion

#pragma region Method Remove

bool List_DeleteItem(LIST_PROPERTIES &list, int LOCATIONDelete)
{
	if (LOCATIONDelete < 0 /*|| LOCATIONDelete > MaxEmployees*/ || List_IsEmpty(list))
	{
		return false;
	}

	for (int i = LOCATIONDelete + 1; i < list.size; i++)
	{
		list.lprop[i - 1] = list.lprop[i];
	}
	REALLOC(list.lprop, list.size, list.size - 1);
	list.size--;
	return true;
}

bool List_DeleteItem(LIST_ARRAY_CHAR &list, int LOCATIONDelete)
{
	if (LOCATIONDelete < 0 /*|| LOCATIONDelete > MaxEmployees*/ || List_IsEmpty(list))
	{
		return false;
	}

	for (int i = LOCATIONDelete + 1; i < list.size; i++)
	{
		strcpy_s(list.listSTR[i - 1].str, list.listSTR[i].str);
	}
	REALLOC(list.listSTR, list.size, list.size - 1);
	list.size--;
	return true;
}

bool List_DeleteItem(LIST_LOCATION &list, int LOCATIONDelete)
{
	if (LOCATIONDelete < 0 /*|| LOCATIONDelete > MaxEmployees*/ || List_IsEmpty(list))
	{
		return false;
	}

	for (int i = LOCATIONDelete + 1; i < list.size; i++)
	{
		list.lloca[i - 1] = list.lloca[i];
	}
	REALLOC(list.lloca, list.size, list.size - 1);
	list.size--;
	return true;
}

bool List_DeleteItem(LIST_TITLE &list, int LOCATIONDelete)
{
	if (LOCATIONDelete < 0 /*|| LOCATIONDelete > MaxEmployees*/ || List_IsEmpty(list))
	{
		return false;
	}

	for (int i = LOCATIONDelete + 1; i < list.size; i++)
	{
		strcpy_s(list.ltitle[i - 1].data, list.ltitle[i].data);
		list.ltitle[i - 1].width, list.ltitle[i].width;
	}
	REALLOC(list.ltitle, list.size, list.size - 1);
	list.size--;
	return true;
}

#pragma endregion