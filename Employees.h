#pragma once
#include "Bill.h"

struct EMPLOYEES
{
	char employeesCode[employees_maxSize_Code + 1];
	char familyName[employees_maxSize_FamilyName + 1];
	char firstName[employees_maxSize_FirstName + 1];
	int sex;
	struct NODE_BILL *list_Bill = NULL;
};

struct  LIST_EMPLOYEES
{
	int size = 0;
	EMPLOYEES *arr = new EMPLOYEES[size];
};

void employees_InsertListBill(LIST_EMPLOYEES &le, char *code, struct NODE_BILL* data);

bool employees_insertItem(LIST_EMPLOYEES &list, int LOCATIONAdd, EMPLOYEES data);
int employees_deleteItem(LIST_EMPLOYEES &list, int LOCATIONDelete);
int employees_search(LIST_EMPLOYEES lm, char *code);
STR employees_GetFullName(LIST_EMPLOYEES le, char *code);
void employees_Edit(LIST_EMPLOYEES &le, LOCATION displayLC);
void employees_Sort(LIST_EMPLOYEES &le);
void employees_Show(LIST_EMPLOYEES le, LIST_MATERIAL lm ,LOCATION displayLC);