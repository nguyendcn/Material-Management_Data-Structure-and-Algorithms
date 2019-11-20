#include "Employees.h"

void employees_InsertListBill(LIST_EMPLOYEES &le, char *code, struct NODE_BILL* data)
{
	for (int run = 0; run < le.size; run++)
	{
		if (strcmp(le.arr[run].employeesCode, code) == 0)
		{
			//le.arr[run].list_Bill = data;
			dslk_addHead(le.arr[run].list_Bill, data);
		}
	}
}

void REALLOC(EMPLOYEES *&list, int oldSize, int newSize)
{
	EMPLOYEES *temp = new EMPLOYEES[oldSize];

	for (int i = 0; i < oldSize; i++)
	{
		temp[i] = list[i];
	}

	delete[] list;

	list = new EMPLOYEES[newSize];

	int min = oldSize < newSize ? oldSize : newSize;

	for (int i = 0; i < min; i++)
	{
		list[i] = temp[i];
	}

	delete[] temp;
}

bool isEmpty(LIST_EMPLOYEES list)
{
	return list.size == 0;
}

bool isFull(LIST_EMPLOYEES list)
{
	return list.size == employees_quantityMax;
}

bool employees_insertItem(LIST_EMPLOYEES &list, int LOCATIONAdd, EMPLOYEES data)
{
	if (LOCATIONAdd < 0 || LOCATIONAdd > list.size || isFull(list))
	{
		return false;
	}

	REALLOC(list.arr, list.size, list.size + 1);

	for (int i = list.size - 1; i >= LOCATIONAdd; i--)
	{
		list.arr[i + 1] = list.arr[i];
	}

	list.arr[LOCATIONAdd] = data;
	list.size++;
	return true;
}

int employees_deleteItem(LIST_EMPLOYEES &list, int LOCATIONDelete)
{
	if (LOCATIONDelete < 0 || LOCATIONDelete > employees_quantityMax || isEmpty(list))
	{
		return false;
	}

	for (int i = LOCATIONDelete + 1; i < list.size; i++)
	{
		list.arr[i - 1] = list.arr[i];
	}
	REALLOC(list.arr, list.size, list.size - 1);
	list.size--;
	return true;
}

bool isExits(LIST_EMPLOYEES le, char *code)
{
	for (int run = 0; run < le.size; run++)
	{
		if (strcmp(le.arr[run].employeesCode, code) == 0)
		{
			return true;
		}
	}
	return false;
}

void swap(EMPLOYEES &a, EMPLOYEES &b)
{
	EMPLOYEES temp;
	temp = b;
	b = a;
	a = temp;
}

void employees_Sort(LIST_EMPLOYEES &le)
{
	for (int run = 0; run < le.size - 1; run++)
	{
		for (int runin = run + 1; runin < le.size; runin++)
		{
			if (strcmp(le.arr[run].firstName, le.arr[runin].firstName) > 0)
			{
				swap(le.arr[run], le.arr[runin]);
			}
			else if (strcmp(le.arr[run].firstName, le.arr[runin].firstName) == 0)
			{
				if (strcmp(le.arr[run].familyName, le.arr[runin].familyName) > 0)
				{
					swap(le.arr[run], le.arr[runin]);
				}
			}
		}
	}
}

int employees_search(LIST_EMPLOYEES lm, char *code)
{
	for (int run = 0; run < lm.size; run++)
	{
		if (strcmp(lm.arr[run].employeesCode, code) == 0)
		{
			return run;
		}
	}
	return -1;
}

STR employees_GetFullName(LIST_EMPLOYEES le, char *code)
{
	STR fullName = {'\0'};
	for (int run = 0; run < le.size; run++)
	{
		if (strcmp(le.arr[run].employeesCode, code) == 0)
		{
			strcpy_s(fullName.str, le.arr[run].familyName);
			strcat_s(fullName.str, " ");
			strcat_s(fullName.str, le.arr[run].firstName);
			return fullName;
		}
	}
	return fullName;
}

STR employees_EntryCode(char *notify, int color, char *text)
{
	LIST_PROPERTIES arrProp;
	PROPERTIES item;

	strcpy_s(item.variables.name, "Ma Nhan Vien");
	item.variables.color = color;
	strcpy_s(item.variables.notify, notify);
	strcpy_s(item.variables.data, text);
	item.mode.modeImport = UPPER_NUMBER;
	item.mode.enable = true;
	item.maxLength = employees_maxSize_Code;
	List_InsertItem(arrProp, arrProp.size, item);

	LOCATION lc;
	lc.x = 5; lc.y = 5;

	//get data
	LIST_ARRAY_CHAR destination;
	enterDataToVariable(destination, arrProp, lc);

	//handling
	if (strcmp(destination.listSTR[destination.size - 1].str, "CANCEL") == 0) // cancel
	{
		STR temp;
		strcpy_s(temp.str, "");
		return temp;
	}

	STR temp;
	temp = destination.listSTR[0];

	// delete
	List_Clear(destination);

	return temp;
}

void employees_InitProperties(LIST_PROPERTIES &lprop)
{
	PROPERTIES prop;
	strcpy_s(prop.variables.name, "Ma Nhan Vien");
	strcpy_s(prop.variables.data, "");
	strcpy_s(prop.variables.notify, "Format: 0-9, A-Z");
	prop.mode.enable = false;
	prop.mode.modeImport = UPPER_NUMBER;
	prop.maxLength = employees_maxSize_Code;

	List_InsertItem(lprop, lprop.size, prop);

	strcpy_s(prop.variables.name, "Ho va Ten Lot");
	strcpy_s(prop.variables.data, "");
	strcpy_s(prop.variables.notify, "Format: a-z, A-Z");
	prop.mode.enable = true;
	prop.mode.modeImport = UPPER_LOWER;
	prop.maxLength = employees_maxSize_FamilyName;

	List_InsertItem(lprop, lprop.size, prop);

	strcpy_s(prop.variables.name, "Ten");
	strcpy_s(prop.variables.data, "");
	strcpy_s(prop.variables.notify, "Format: a-z, A-Z");
	prop.mode.enable = true;
	prop.mode.modeImport = UPPER_LOWER;
	prop.maxLength = employees_maxSize_FirstName;

	List_InsertItem(lprop, lprop.size, prop);

	strcpy_s(prop.variables.name, "Gioi Tinh");
	strcpy_s(prop.variables.data, "");
	strcpy_s(prop.variables.notify, "0: Nam; 1: Nu");
	prop.mode.enable = true;
	prop.mode.modeImport = SEX;
	prop.maxLength = 1;

	List_InsertItem(lprop, lprop.size, prop);
}

void employees_InitTiTle(LIST_TITLE &lt)
{
	TITLE t;
	int size;

	strcpy_s(t.data, "Ma Nhan Vien");
	size = strlen(t.data);
	t.width = (size > employees_maxSize_Code ? size : employees_maxSize_Code) + 4;

	List_InsertItem(lt, lt.size, t);

	strcpy_s(t.data, "Ho va Ten Dem");
	size = strlen(t.data);
	t.width = (size > employees_maxSize_FamilyName ? size : employees_maxSize_FamilyName) + 4;

	List_InsertItem(lt, lt.size, t);

	strcpy_s(t.data, "Ten");
	size = strlen(t.data);
	t.width = (size > employees_maxSize_FirstName ? size : employees_maxSize_FirstName) + 4;

	List_InsertItem(lt, lt.size, t);

	strcpy_s(t.data, "Gioi Tinh");
	size = strlen(t.data);
	t.width = size + 4;

	List_InsertItem(lt, lt.size, t);
}

void employees_Edit(LIST_EMPLOYEES &le, LOCATION displayLC)
{
/*
	LOCATION displayLC;
	displayLC.x = displayLC.y = 5;

	char notify[maxLengthChar];
	strcpy_s(notify, "Format: 0-9, A-Z");
	int color = ColorCode_White;
	STR code;

	while (true)
	{
		code = employees_EntryCode(notify, color, "");

		if (strcmp(code.str, "") == 0)// cancel
		{
			return;
		}
		else
		{
			if (isExits(le, code.str))
			{
				break;
			}
			else
			{
				strcpy_s(notify, "Ma nhan vien khong ton tai");
				color = ColorCode_Red;
			}
		}
	}

	int check = employees_search(le, code.str);
	if (check != -1)
	{
		EMPLOYEES temp = le.arr[check];

		LIST_PROPERTIES lprop;
		employees_InitProperties(lprop);

		strcpy_s(lprop.lprop[0].variables.data, temp.employeesCode);
		strcpy_s(lprop.lprop[1].variables.data, temp.familyName);
		strcpy_s(lprop.lprop[2].variables.data, temp.firstName);
		
		char *a = new char[2];
		_itoa_s(temp.sex, a, 2, 10);
		strcpy_s(lprop.lprop[3].variables.data, a);
		delete[] a;
		
		system("cls");
		LIST_ARRAY_CHAR arrData;
		enterDataToVariable(arrData, lprop, displayLC);

		if (strcmp(arrData.listSTR[arrData.size - 1].str, "DONE") == 0)
		{
			strcpy_s(le.arr[check].familyName, char_formartText(arrData.listSTR[1].str));
			strcpy_s(le.arr[check].firstName, char_formartText(arrData.listSTR[2].str));
			le.arr[check].sex = atoi(arrData.listSTR[3].str);
			
			messagebox("Ban da cap nhat thong tin thanh cong.", YES, displayLC);
			return;
		}
		else
		{
			messagebox("Ban da huy qua trinh cap nhat thong tin.", YES, displayLC);
			return;
		}
	}
	messagebox("Khong tim thay voi ma nhan vien tuong ung.", YES, displayLC);
	return;*/

	LOCATION lChoose, lShow;
	Size sGird;
	LIST_TITLE title;
	LIST_ARRAY_CHAR notify;

	employees_InitTiTle(title);

	LIST_LOCATION listLC;

	List_InsertItem(notify, notify.size, "Employees");
	List_InsertItem(notify, notify.size, "0-9, A-Z");
	List_InsertItem(notify, notify.size, "Ma nhan vien khong ton tai.");

	lChoose = { displayLC.x + 6, displayLC.y + 1 };
	lShow = { displayLC.x + 3, displayLC.y + 13 };

	drawBorder(listLC, lShow, le.size, 5, title);

	for (int run = 0; run < le.size; run++)
	{
		int indexNow = run * employees_quantityFields;
		gotoxy(listLC.lloca[indexNow].x, listLC.lloca[indexNow].y);				BGColorText(le.arr[run].employeesCode, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLC.lloca[indexNow + 1].x, listLC.lloca[indexNow + 1].y);		BGColorText(le.arr[run].familyName, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLC.lloca[indexNow + 2].x, listLC.lloca[indexNow + 2].y);		BGColorText(le.arr[run].firstName, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLC.lloca[indexNow + 3].x, listLC.lloca[indexNow + 3].y);
		if (le.arr[run].sex == 0)
		{
			BGColorText("Nam", ColorCode_Black, ColorCode_DarkWhite);
		}
		else if (le.arr[run].sex == 1)
		{
			BGColorText("Nu", ColorCode_Black, ColorCode_DarkWhite);
		}
	}

	if (le.size == 0)
	{
		sGird = { 64, 20 };
	}
	else
	{
		sGird = { (listLC.lloca[listLC.size - 1].x + title.ltitle[title.size - 1].width) - displayLC.x, (listLC.lloca[listLC.size - 1].y + 5) - displayLC.y };
	}
	drawBox(displayLC, sGird, "Danh Sach Nhan Vien");

	//action
	while (true)
	{
		STR codeBill;
		NBD bd = NULL;
		LIST_BILL lb;	dslk_Initialize(lb);
		codeBill = dis_chooseViewDetail(lb, bd, le, lChoose, sGird.width, notify, 1);
		if (strcmp(codeBill.str, "DONE") == 0)
		{
			break;
		}
		else
		{
			//edit
			int check = employees_search(le, codeBill.str);
			displayLC = { displayLC.x = 3, displayLC.y + 3 };
			if (check != -1)
			{
				EMPLOYEES temp = le.arr[check];

				LIST_PROPERTIES lprop;
				employees_InitProperties(lprop);

				strcpy_s(lprop.lprop[0].variables.data, temp.employeesCode);
				strcpy_s(lprop.lprop[1].variables.data, temp.familyName);
				strcpy_s(lprop.lprop[2].variables.data, temp.firstName);

				char *a = new char[2];
				_itoa_s(temp.sex, a, 2, 10);
				strcpy_s(lprop.lprop[3].variables.data, a);
				delete[] a;

				system("cls");
				LIST_ARRAY_CHAR arrData;
				enterDataToVariable(arrData, lprop, displayLC);

				if (strcmp(arrData.listSTR[arrData.size - 1].str, "DONE") == 0)
				{
					strcpy_s(le.arr[check].familyName, char_formartText(arrData.listSTR[1].str));
					strcpy_s(le.arr[check].firstName, char_formartText(arrData.listSTR[2].str));
					le.arr[check].sex = atoi(arrData.listSTR[3].str);

					employees_Sort(le);

					messagebox("Ban da cap nhat thong tin thanh cong.", YES, displayLC);
					return;
				}
				else
				{
					messagebox("Ban da huy qua trinh cap nhat thong tin.", YES, displayLC);
					return;
				}
			}
			messagebox("Khong tim thay voi ma nhan vien tuong ung.", YES, displayLC);
			return;
		}
	}

	List_Clear(listLC);
	List_Clear(title);
}

void employees_Show(LIST_EMPLOYEES le, LIST_MATERIAL lm, LOCATION displayLC)
{
	LOCATION lChoose, lShow;
	Size sGird;
	LIST_TITLE title;
	LIST_ARRAY_CHAR notify;

	employees_InitTiTle(title);

	LIST_LOCATION listLC;

	List_InsertItem(notify, notify.size, "Employees");
	List_InsertItem(notify, notify.size, "0-9, A-Z");
	List_InsertItem(notify, notify.size, "Ma nhan vien khong ton tai.");

	lChoose = { displayLC.x + 6, displayLC.y + 1};
	lShow = { displayLC.x + 3, displayLC.y + 13};

	drawBorder(listLC, lShow, le.size, 5, title);

	for (int run = 0; run < le.size; run++)
	{
		int indexNow = run * employees_quantityFields;
		gotoxy(listLC.lloca[indexNow].x, listLC.lloca[indexNow].y);				BGColorText(le.arr[run].employeesCode, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLC.lloca[indexNow + 1].x, listLC.lloca[indexNow + 1].y);		BGColorText(le.arr[run].familyName, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLC.lloca[indexNow + 2].x, listLC.lloca[indexNow + 2].y);		BGColorText(le.arr[run].firstName, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLC.lloca[indexNow + 3].x, listLC.lloca[indexNow + 3].y);
		if (le.arr[run].sex == 0)
		{
			BGColorText("Nam", ColorCode_Black, ColorCode_DarkWhite);
		}
		else if (le.arr[run].sex == 1)
		{
			BGColorText("Nu", ColorCode_Black, ColorCode_DarkWhite);
		}
	}
	
	if (le.size == 0)
	{
		sGird = { 64, 20 };
	}
	else
	{
		sGird = { (listLC.lloca[listLC.size - 1].x + title.ltitle[title.size - 1].width) - displayLC.x, (listLC.lloca[listLC.size - 1].y + 5) - displayLC.y };
	}
	drawBox(displayLC, sGird, "Danh Sach Nhan Vien");

	//action
	while (true)
	{
		STR codeBill;
		NBD bd = NULL;
		LIST_BILL lb;	dslk_Initialize(lb);
		codeBill = dis_chooseViewDetail(lb, bd, le, lChoose, sGird.width, notify, 1);
		if (strcmp(codeBill.str, "DONE") == 0)
		{
			break;
		}
		else
		{
			//show
			for (int run = 0; run < le.size; run++)
			{
				if (strcmp(codeBill.str, le.arr[run].employeesCode) == 0)
				{
					//show bill
					LIST_BILL lbill;
					lbill.pHead = le.arr[run].list_Bill;

					LOCATION lcShow;
					lcShow = {displayLC.x + sGird.width + 3, displayLC.y};
					bill_Show(lbill, lm, lcShow);

					dis_Clear(lcShow, {70, 40});
				}
			}
		}
	}

	List_Clear(listLC);
	List_Clear(title);
}