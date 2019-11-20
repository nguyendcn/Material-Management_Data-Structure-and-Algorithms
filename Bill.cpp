#include "Bill.h"


void dslk_Initialize(LIST_BILL &lb)
{
	lb.pHead = lb.pTail = NULL;
}

NODE_BILL* dslk_CreateNodeBill(BILL data)
{
	NODE_BILL *p = new NODE_BILL;
	
	if (p == NULL)
		return NULL;

	p->data = data;
	p->pNext = NULL;

	return p;
}

void dslk_addHead(LIST_BILL &lb, NODE_BILL *itemAdd)
{
	if (lb.pHead == NULL) // empty
	{
		lb.pHead = lb.pTail = itemAdd;
	}
	else
	{
		itemAdd->pNext = lb.pHead;
		lb.pHead = itemAdd;
	}
}

void dslk_addTail(LIST_BILL &lb, NODE_BILL *itemAdd)
{

	if (lb.pHead == NULL) //Danh sách đang rỗng.
	{
		lb.pHead = lb.pTail = itemAdd;  // item vừa là đầu vừa là cuối.
	}
	else
	{
		lb.pTail->pNext = itemAdd;  //Cho pTail trỏ tới pNext tới item
		lb.pTail = itemAdd; //Cập nhật lại pTail la item;
	}
}

void dslk_addHead( NODE_BILL* &lb, NODE_BILL *itemAdd)
{
	if (lb == NULL)
	{
		lb = itemAdd;
	}
	else
	{
		itemAdd->pNext = lb;
		lb = itemAdd;
	}
}

bool dslk_removeNode(LIST_BILL &lb, NODE_BILL *itemDelete)
{
	if (lb.pHead == NULL)
	{
		return false;
	}
	else
	{
		for (NODE_BILL *p = lb.pHead; p->pNext != NULL; p = p->pNext)
		{
			if (strcmp(((p->pNext)->data).billNumber, itemDelete->data.billNumber) == 0)
			{
				NODE_BILL *temp = p->pNext;
				p->pNext = (p->pNext)->pNext;
				delete temp;
				return true;
			}
		}
		return false;
	}
}

int dslk_Count(struct NODE_BILL* lb)
{
	int count = 0;
	for (NODE_BILL *p = lb; p != NULL; p = p->pNext)
	{
		count++;
	}
	return count;
}

string getCodeBill(LIST_BILL lb)
{
	time_t rawtime = time(0);
	struct tm now;
	localtime_s(&now, &rawtime);

	string text = "";
	text += "CB";
	// "CB"

	if (now.tm_mday < 10)
	{
		text += "0";
		text += to_string(now.tm_mday);
	}
	else
	{
		text += to_string(now.tm_mday);
	}

	if (now.tm_mon + 1 < 10)
	{
		text += "0";
		text += to_string(now.tm_mon + 1);
	}
	else
	{
		text += to_string(now.tm_mon + 1);
	}

	text += to_string(now.tm_year + 1900);

	// "CB.day.month.year"

	//add code random
	
	if (lb.pHead != NULL)
	{
		time_t rawtime = time(0);
		struct tm now;
		localtime_s(&now, &rawtime);

		char *temp = _strdup(lb.pTail->data.billNumber);
		char *cut = char_substr(temp, 10, 10);
		int num = atoi(cut);
		int sl = (int)log10(num) + 1;
		num++;
		int slnew = (int)log10(num) + 1;

		if (slnew > sl)
		{
			for (int i = 0; i < 10 - (sl + 1); i++)
			{
				text += "0";
			}
		}
		else
		{
			for (int i = 0; i < 10 - sl; i++)
			{
				text += "0";
			}
		}
		text += to_string(num);
	}
	else
	{
		text += "0000000001"; // first
	}
	// "CB.day.month.year.0000000000"
	
	return text;
}

string getDateNow()
{
	time_t rawtime = time(0);
	struct tm now;
	localtime_s(&now, &rawtime);

	string text = "";

	if (now.tm_mday < 10)
	{
		text += "0";
		text += to_string(now.tm_mday);
		text += "/";
	}
	else
	{
		text += to_string(now.tm_mday);
		text += "/";
	}

	if (now.tm_mon + 1 < 10)
	{
		text += "0";
		text += to_string(now.tm_mon + 1);
		text += "/";
	}
	else
	{
		text += to_string(now.tm_mon + 1);
		text += "/";
	}
	text += to_string(1900 + now.tm_year);


	return text;
}

char* getCodeEmployeesNow()
{
	return "D16CQCN02";
}

void bill_SortUpByCode(LIST_BILL &lb)
{
	for (NODE_BILL *p = lb.pHead; p != lb.pTail; p = p->pNext)
	{
		for (NODE_BILL *q = p->pNext; q != NULL; q = q->pNext)
		{
			if (atoi(char_substr(p->data.billNumber, 10, 10)) > atoi(char_substr(p->data.billNumber, 10, 10)))
			{
				BILL temp = q->data;
				q->data = p->data;
				p->data = temp;
			}
		}
	}
}

double bill_CalMoney(NBD p)
{
	double money = 0;
	for (; p != NULL; p = p->pNext)
	{
		double moneyNoVAT = p->data.quantity * p->data.unitPrice;
		double moneyVAT = moneyNoVAT * (0.1 * p->data.percentVAT / 100);
		money += (moneyNoVAT + moneyVAT);
	}
	return money;
}

int bill_GetQuantity(LIST_BILL lb)
{
	int count = 0;
	for (NODE_BILL *p = lb.pHead; p !=NULL; p = p->pNext )
	{
		count++;
	}
	return count;
}

void bill_initProperties(LIST_PROPERTIES &prop, LIST_BILL lb)
{
	PROPERTIES p;
	strcpy_s(p.variables.data, getCodeBill(lb).c_str());
	strcpy_s(p.variables.name, "Ma Hoa Don");
	strcpy_s(p.variables.notify, "Format: Random");
	p.maxLength = bill_maxSize_Code;
	p.variables.color = ColorCode_DarkWhite;
	p.mode.enable = false;
	p.mode.modeImport = UPPER_NUMBER;

	List_InsertItem(prop, prop.size, p);

	strcpy_s(p.variables.data, "");
	strcpy_s(p.variables.name, "Ma Nhan Vien Lap");
	strcpy_s(p.variables.notify, "A-Z, 0-9");
	p.variables.color = ColorCode_DarkWhite;
	p.maxLength = employees_maxSize_Code;
	p.mode.enable = true;
	p.mode.modeImport = UPPER_NUMBER;

	List_InsertItem(prop, prop.size, p);

	strcpy_s(p.variables.data, getDateNow().c_str());
	strcpy_s(p.variables.name, "Ngay Lap Hoa Don");
	strcpy_s(p.variables.notify, "Auto Update");
	p.maxLength = bill_maxSize_invoiceDate;
	p.variables.color = ColorCode_DarkWhite;
	p.mode.enable = false;
	p.mode.modeImport = UPPER_NUMBER;

	List_InsertItem(prop, prop.size, p);

	strcpy_s(p.variables.data, "");
	strcpy_s(p.variables.name, "Loai Hoa Don");
	strcpy_s(p.variables.notify, "Format: (N : Nhap, X : Xuat)");
	p.variables.color = ColorCode_DarkWhite;
	p.maxLength = 1;
	p.mode.enable = true;
	p.mode.modeImport = TYPEBILL;

	List_InsertItem(prop, prop.size, p);
}

void bill_buildBill(LIST_BILL &lb, struct LIST_EMPLOYEES &le, LIST_MATERIAL &lm)
{
	LOCATION lc; lc.x = lc.y = 5;

	LIST_PROPERTIES prop;
	LIST_ARRAY_CHAR arrData;;

	while (true)
	{
		bill_initProperties(prop, lb);
		while (true)
		{
			enterDataToVariable(arrData, prop, lc);
			if (strcmp(arrData.listSTR[arrData.size - 1].str, "CANCEL") == 0)
			{
				break;
			}
			else
			{
				if (employees_search(le, arrData.listSTR[1].str) == -1)
				{
					strcpy_s(prop.lprop[1].variables.data, "");
					strcpy_s(prop.lprop[1].variables.notify, "Employees not exist");
					prop.lprop[1].variables.color = ColorCode_Red;

				}
				else
				{
					break;
				}
			}
		}

		if (strcmp(arrData.listSTR[arrData.size - 1].str, "CANCEL") == 0)
		{
			system("cls");
			messagebox("Ban da huy qua trinh lap hoa don", YES, lc);
			return;
		}
		else
		{
			NBD listBD;
			dslk_InitBD(listBD);

			char *type = arrData.listSTR[arrData.size - 2].str;

			bool isContinue = true;
			while (isContinue)
			{
				bd_Add(listBD, lm, type[0]);

				if (listBD == NULL)
				{
					system("cls");
					isContinue = messagebox("Danh sach chi tiet hoa don trong. Ban co muon nhap lai khong?", YES_NO, LOCATION(LOCATION()));
					if (!isContinue)
						return;
					system("cls");
				}
				else
				{
					break;
				}
			}

			if (listBD != NULL)
			{
				//Copy data
				BILL item;
				strcpy_s(item.billNumber, arrData.listSTR[0].str);
				strcpy_s(item.employeesCode, arrData.listSTR[1].str);
				strcpy_s(item.invoiceDate, arrData.listSTR[2].str);
				item.type = type[0];
				item.list_BillDetail = listBD;

				// add to list Bill;
				dslk_addTail(lb, dslk_CreateNodeBill(item));

				// add to list bill of employees
				employees_InsertListBill(le, arrData.listSTR[1].str, dslk_CreateNodeBill(item));

				system("cls");
				if (!messagebox("Ban da tao hoa don thanh cong. Ban co muon tao hoa don tiep khong?", YES_NO, lc))
				{
					List_Clear(prop);
					List_Clear(arrData);
					system("cls");
					return;
				}
			}
		}
		system("cls");
		List_Reset(prop);
		List_Reset(arrData);
	}
}

void bill_InitTiTle(LIST_TITLE &title)
{
	TITLE t;
	strcpy_s(t.data, "Ma Hoa Don");
	int size = strlen(t.data);
	t.width = (size > bill_maxSize_Code ? size : bill_maxSize_Code) + 4;

	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "Ma Nhan Vien");
	 size = strlen(t.data);
	t.width = (size > employees_maxSize_Code ? size : employees_maxSize_Code) + 4;

	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "Ngay Lap");
	 size = strlen(t.data);
	t.width = (size > bill_maxSize_invoiceDate ? size : bill_maxSize_invoiceDate) + 4;

	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "Loai");
	 size = strlen(t.data);
	t.width = (size > 1 ? size : 1) + 4;

	List_InsertItem(title, title.size, t);
}

void bill_ViewDetail(LIST_BILL lb, LIST_MATERIAL lm, char *code, LOCATION lcDisPlay, Size &size)
{
	bool isExist = false;
	NODE_BILL *p;
	for (p = lb.pHead; p != NULL; p = p->pNext)
	{
		if (strcmp(p->data.billNumber, code) == 0)
		{
			isExist = true;
			break;
		}
	}

	if (isExist)
	{
		int bottom = 0;

		bd_Show(p->data.list_BillDetail, lm, lcDisPlay, bottom, 0);
	}
}

STR dis_chooseViewDetail( LIST_BILL lb, NBD bd, LIST_EMPLOYEES le,LOCATION lcDis, int widthGird, LIST_ARRAY_CHAR notify, int modeMore)
{
	//return DONE => SUCCESS
	//return code => do something with code
	STR codeCheck;

	LIST_TITLE listTitle;
	LOCATION lcGird, lcDisplay, lcGetCode;
	LOCATION lcBtnDone, lcBtnView, lcTxtCode;
	Size sBtnDone, sBtnView, sTxtCode;
	
	lcGird = { lcDis.x, lcDis.y };
	lcBtnDone = { lcGird.x + 3, lcGird.y + 3};
	sBtnDone = { static_cast<int>(strlen("XONG") + 4), 5 };

	lcTxtCode = { lcBtnDone.x + sBtnDone.width + 15, lcGird.y + 3 };

	if (lb.pHead != NULL)
	{
		sTxtCode = { bill_maxSize_Code + 4 , 5 };
	}
	else if (bd != NULL)
	{
		sTxtCode = { material_maxSize_Code + 4 , 5 };
	}
	else
	{
		sTxtCode = { material_maxSize_Code + 4 , 5 };
	}

	lcBtnView = { lcTxtCode.x + sTxtCode.width + 2, lcGird.y + 3 };

	sBtnView = { static_cast<int>(strlen("XEM") + 4), 5 };

	lcDisplay = { lcGird.x + 3, lcBtnDone.y + sBtnDone.height + 4 };


	if (modeMore == 1)
	{
		button(false, "XEM", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
	}
	else if (modeMore == 0)
	{
		button(false, "XOA", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
	}
	button(true, "XONG", lcBtnDone, sBtnDone, ColorCode_Blue, ColorCode_Black);
	
	drawRectangle(lcGetCode, lcTxtCode, sTxtCode, ColorCode_DarkWhite, ColorCode_DarkWhite);
	gotoxy(lcGetCode.x - 11, lcGetCode.y); std::cout << notify.listSTR[0].str;
	gotoxy(lcGetCode.x, lcGetCode.y - 2); ColorText(notify.listSTR[1].str, ColorCode_DarkWhite);
	//margin = { (lcBtnView.x + sBtnView.width + 3) - lcGird.x ,  lcBtnDone.x + sBtnDone.height + 1 };

	int index = 0;
	char code[30] = {'\0'};
	bool isControl = false;
	while (true)
	{
		if (_kbhit())
		{
			char key = _getch();

			if ((key >= '0' && key <= '9' || key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z') && !isControl)
			{
				//cout << "not is  control" << endl;
				if (index == 1)
				{
					//codeDel = strdup(dataEntry("", ))
				}
			}
			else if (key == -32)
			{
				isControl = true;
			}
			else if (isControl)
			{
				if (key == 80)
				{
					//cout << "DOWN";
				}
				else if (key == 72)
				{
					//cout << "UP";
				}
				else if (key == 75)
				{
					//cout << "LEFT";
					index--;
					if (index < 0)
					{
						index = 2;
						button(false, "XONG", lcBtnDone, sBtnDone, ColorCode_Blue, ColorCode_Black);
						if (modeMore == 1)
						{
							button(true, "XEM", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
						}
						else if (modeMore == 0)
						{
							button(true, "XOA", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
						}
					}
					else if (index == 1) // focus txt
					{
						if (modeMore == 1)
						{
							button(false, "XEM", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
						}
						else if (modeMore == 0)
						{
							button(false, "XOA", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
						}
						drawRectangle(lcGetCode, lcTxtCode, sTxtCode, ColorCode_DarkWhite, ColorCode_Blue);
						if (lb.pHead != NULL)
						{
							strcpy_s(code, dataEntry(code, lcGetCode, UPPER_NUMBER, bill_maxSize_Code));
						}
						else if (le.size != 0)
						{
							strcpy_s(code, dataEntry(code, lcGetCode, UPPER_NUMBER, employees_maxSize_Code));
						}
						else if (bd != NULL)
						{
							strcpy_s(code, dataEntry(code, lcGetCode, UPPER_NUMBER, material_maxSize_Code));
						}
					}
					else if (index == 0)
					{
						drawRectangle(lcGetCode, lcTxtCode, sTxtCode, ColorCode_DarkWhite, ColorCode_Blue);
						button(true, "XONG", lcBtnDone, sBtnDone, ColorCode_Blue, ColorCode_Black);
					}
				}
				else if (key == 77)
				{
					//cout << "RIGHT";
					index++;
					if (index > 2)
					{
						index = 0;
						button(true, "XONG", lcBtnDone, sBtnDone, ColorCode_Blue, ColorCode_Black);
						if (modeMore == 1)
						{
							button(false, "XEM", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
						}
						else if (modeMore == 0)
						{
							button(false, "XOA", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
						}
					}
					else if (index == 2)
					{
						if (modeMore == 1)
						{
							button(true, "XEM", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
						}
						else if (modeMore == 0)
						{
							button(true, "XOA", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
						}
						drawRectangle(lcGetCode, lcTxtCode, sTxtCode, ColorCode_DarkWhite, ColorCode_DarkWhite);
					}
					else if (index == 1)
					{
						button(false, "XONG", lcBtnDone, sBtnDone, ColorCode_Blue, ColorCode_Black);
						drawRectangle(lcGetCode, lcTxtCode, sTxtCode, ColorCode_DarkWhite, ColorCode_Blue);
						if (lb.pHead != NULL)
						{
							strcpy_s(code, dataEntry(code, lcGetCode, UPPER_NUMBER, bill_maxSize_Code));
						}
						else if (le.size != 0)
						{
							strcpy_s(code, dataEntry(code, lcGetCode, UPPER_NUMBER, employees_maxSize_Code));
						}
						else if (bd != NULL)
						{
							strcpy_s(code, dataEntry(code, lcGetCode, UPPER_NUMBER, material_maxSize_Code));
						}
					}
				}
				isControl = false;
			}
			else
			{
				if (key == 8) // backSpace
				{

				}
				if (key == 13)
				{
					if (index == 0)
					{
						strcpy_s(codeCheck.str, "DONE");
						return codeCheck;
					}
					else if (index == 2)
					{
						// check code bill
						if (lb.pHead != NULL)
						{
							for (NODE_BILL *p = lb.pHead; p != NULL; p = p->pNext)
							{
								if (strcmp(p->data.billNumber, code) == 0)
								{
									strcpy_s(codeCheck.str, p->data.billNumber);
									return codeCheck;
								}
							}
						}
						else if (bd != NULL)
						{
							for (NBD bd_run = bd; bd_run != NULL; bd_run = bd_run->pNext)
							{
								if (strcmp(bd_run->data.materialsCode, code) == 0)
								{
									strcpy_s(codeCheck.str, bd_run->data.materialsCode);
									return codeCheck;
								}
							}
						}
						else if (le.size != 0)
						{
							for (int run = 0; run < le.size; run++)
							{
								if (strcmp(le.arr[run].employeesCode, code) == 0)
								{
									strcpy_s(codeCheck.str, le.arr[run].employeesCode);
									return codeCheck;
								}
							}
						}
						//check code material
						
						//not exist
						LOCATION lcWait;
						lcWait = { static_cast<int>(lcGird.x + ((widthGird / 2) - (strlen(notify.listSTR[2].str) / 2))), lcBtnDone.y + sBtnDone.height};
						dis_wait(lcWait, notify.listSTR[2].str, 3, ColorCode_Red);
					}
				}
			}
		}
	}
}

void bill_Show(LIST_BILL lb, LIST_MATERIAL lm, LOCATION lcShow)
{
	LIST_LOCATION listLcResult;
	LIST_TITLE listTitle;
	LOCATION lcDisplay, lcChoose, lcGird;
	LIST_ARRAY_CHAR notify;
	Size sizeGird;
	Size sClearView = { 0, 0 };

	LOCATION bottom;


	STR codeBill;
	strcpy_s(codeBill.str, "");
	int quantity = bill_GetQuantity(lb);

	List_InsertItem(notify, notify.size, "Code Bill");
	List_InsertItem(notify, notify.size, "Format: 0-9, A-Z");
	List_InsertItem(notify, notify.size, "Ma hoa don khong ton tai.");

	lcGird = lcShow;
	lcChoose = { lcGird.x, lcGird.y};
	lcDisplay = { lcGird.x + 3, lcGird.y + 10 };

	bill_InitTiTle(listTitle);

	drawBorder(listLcResult, lcDisplay, quantity, 5, listTitle);

	if (listLcResult.size > 0)
	{
		bottom = { listLcResult.lloca[listLcResult.size - 1].x + listTitle.ltitle[3].width, listLcResult.lloca[listLcResult.size - 1].y + 4 };
	}
	else
	{
		bottom = { 67, lcDisplay.y + 7 };
	}

	if (lb.pHead == NULL)
	{
		sizeGird = { 64, 18 };
	}
	else
	{
		sizeGird = { bottom.x - lcGird.x , bottom.y - lcGird.y };
	}

	drawBox(lcGird, sizeGird, "Hoa Don");

	int count = 0;
	for (NODE_BILL *p = lb.pHead; p != NULL; p = p->pNext)
	{
		int indexNow = count * bill_quantityFields;
		gotoxy(listLcResult.lloca[indexNow].x, listLcResult.lloca[indexNow].y); BGColorText(p->data.billNumber, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLcResult.lloca[indexNow + 1].x, listLcResult.lloca[indexNow + 1].y); BGColorText(p->data.employeesCode, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLcResult.lloca[indexNow + 2].x, listLcResult.lloca[indexNow + 2].y); BGColorText(p->data.invoiceDate, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLcResult.lloca[indexNow + 3].x, listLcResult.lloca[indexNow + 3].y); BGColorText((to_string(p->data.type)).c_str(), ColorCode_Black, ColorCode_DarkWhite);
		count++;
	}

	//action
	while (true)
	{
		STR codeBill;
		NBD bd = NULL;
		LIST_EMPLOYEES le;
		codeBill = dis_chooseViewDetail(lb, bd, le, lcChoose, sizeGird.width, notify, 1);
		if (strcmp(codeBill.str, "DONE") == 0)
		{
			break;
		}
		else
		{
			//view detail
			LOCATION lcView;
			lcView = { lcGird.x + sizeGird.width + 2 , lcGird.y };
			bill_ViewDetail(lb, lm, codeBill.str, lcView, sClearView);
		}
	}

}

#pragma region Show Bill by Date
void bill_EntryDate(LIST_ARRAY_CHAR &data)
{
	LIST_LOCATION lLocationGet;
	LIST_ARRAY_CHAR fields;
	LOCATION lcTemp;
	List_InsertItem(fields, fields.size, "Tu Ngay");
	List_InsertItem(fields, fields.size, "Den Ngay");
	Size sBox = { 9, 3 };
	Size sButton = {8, 5};

	dis_drawEntryDate(lLocationGet, fields);

	//init data
	for (int i = 0; i < lLocationGet.size - 2; i++)
	{
		List_InsertItem(data, data.size, "");
	}


	int index = 0;

	//focus box 1;
	lcTemp = { lLocationGet.lloca[index].x - 2, lLocationGet.lloca[index].y - 1 };
	drawRectangle(lcTemp, lcTemp, sBox, ColorCode_Black, ColorCode_Blue);
	strcpy_s(data.listSTR[index].str, dataEntry(data.listSTR[index].str, lLocationGet.lloca[index], NUMBER, 2));

	bool isCancle = false;
	bool isControl = false;
	while (true)
	{
		if (_kbhit())
		{
			char key = _getch();

			if ((key >= '0' && key <= '9' || key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z') && !isControl)
			{
				//cout << "not is  control" << endl;
				/*if (index != lLocationGet.size - 1 || index != lLocationGet.size - 2)
				{
					if (index == 2 || index == 5)
					{
						strcpy_s(data.listSTR[index].str, dataEntry(data.listSTR[index].str, lLocationGet.lloca[index], NUMBER, 4));
					}
					else
					{
						strcpy_s(data.listSTR[index].str, dataEntry(data.listSTR[index].str, lLocationGet.lloca[index], NUMBER, 2));
					}
				}*/
			}
			else if (key == -32)
			{
				isControl = true;
			}
			else if (isControl)
			{
				if (key == 80)
				{
					//cout << "DOWN";
				}
				else if (key == 72)
				{
					//cout << "UP";
				}
				else if (key == 75)
				{
					//cout << "LEFT";
					index--;
					if (index < 0)
					{
						lcTemp = { lLocationGet.lloca[0].x - 2, lLocationGet.lloca[0].y - 1 };
						drawRectangle(lcTemp, lcTemp, sBox, ColorCode_Black, ColorCode_DarkWhite);
						gotoxy(lcTemp.x, lcTemp.y); std::cout << data.listSTR[0].str;

						index = lLocationGet.size - 1;
						button(true, "HUY.", lLocationGet.lloca[index], sButton, ColorCode_Blue, ColorCode_Black);
					}
					else if (index == lLocationGet.size - 2)
					{
						button(false, "HUY.", lLocationGet.lloca[index + 1], sButton, ColorCode_Blue, ColorCode_Black);
						button(true, "XONG", lLocationGet.lloca[index], sButton, ColorCode_Blue, ColorCode_Black);
					}
					else if (index == lLocationGet.size - 3)
					{
						button(false, "XONG", lLocationGet.lloca[index + 1], sButton, ColorCode_Blue, ColorCode_Black);

						lcTemp = { lLocationGet.lloca[index].x - 2, lLocationGet.lloca[index].y - 1 };
						drawRectangle(lcTemp, lcTemp, sBox, ColorCode_Black, ColorCode_Blue);
						strcpy_s(data.listSTR[index].str, dataEntry(data.listSTR[index].str, lLocationGet.lloca[index], NUMBER, 4));
					}
					else
					{
						lcTemp = { lLocationGet.lloca[index + 1].x - 2, lLocationGet.lloca[index + 1].y - 1 };
						drawRectangle(lcTemp, lcTemp, sBox, ColorCode_Black, ColorCode_DarkWhite);
						gotoxy(lcTemp.x, lcTemp.y); std::cout << data.listSTR[index + 1].str;

						//focus
						lcTemp = { lLocationGet.lloca[index].x - 2, lLocationGet.lloca[index].y - 1 };
						drawRectangle(lcTemp, lcTemp, sBox, ColorCode_Black, ColorCode_Blue);
						gotoxy(lcTemp.x, lcTemp.y); std::cout << data.listSTR[index].str;

						if (index == 2 || index == 5)
						{
							strcpy_s(data.listSTR[index].str, dataEntry(data.listSTR[index].str, lLocationGet.lloca[index], NUMBER, 4));
						}
						else
						{
							strcpy_s(data.listSTR[index].str, dataEntry(data.listSTR[index].str, lLocationGet.lloca[index], NUMBER, 2));
						}
					}
				}
				else if (key == 77)
				{
					//cout << "RIGHT";
					index++;
					if (index >= lLocationGet.size)
					{
						button(false, "HUY.", lLocationGet.lloca[lLocationGet.size - 1], sButton, ColorCode_Blue, ColorCode_Black);
						index = 0;

						lcTemp = { lLocationGet.lloca[index].x - 2, lLocationGet.lloca[index].y - 1 };
						drawRectangle(lcTemp, lcTemp, sBox, ColorCode_Black, ColorCode_Blue);
						gotoxy(lcTemp.x, lcTemp.y); std::cout << data.listSTR[index].str;

						strcpy_s(data.listSTR[index].str, dataEntry(data.listSTR[index].str, lLocationGet.lloca[index], NUMBER, 2));
					}
					else if (index == lLocationGet.size - 1)
					{
						button(true, "HUY.", lLocationGet.lloca[index], sButton, ColorCode_Blue, ColorCode_Black);
						button(false, "XONG", lLocationGet.lloca[index - 1], sButton, ColorCode_Blue, ColorCode_Black);
					}
					else if (index == lLocationGet.size - 2)
					{
						lcTemp = { lLocationGet.lloca[index - 1].x - 2, lLocationGet.lloca[index - 1].y - 1 };
						drawRectangle(lcTemp, lcTemp, sBox, ColorCode_Black, ColorCode_DarkWhite);
						gotoxy(lcTemp.x, lcTemp.y); std::cout << data.listSTR[index - 1].str;

						button(true, "XONG", lLocationGet.lloca[index], sButton, ColorCode_Blue, ColorCode_Black);
					}
					else
					{
						lcTemp = { lLocationGet.lloca[index - 1].x - 2, lLocationGet.lloca[index - 1].y - 1 };
						drawRectangle(lcTemp, lcTemp, sBox, ColorCode_Black, ColorCode_DarkWhite);
						gotoxy(lcTemp.x, lcTemp.y); std::cout << data.listSTR[index - 1].str;

						lcTemp = { lLocationGet.lloca[index].x - 2, lLocationGet.lloca[index].y - 1 };
						drawRectangle(lcTemp, lcTemp, sBox, ColorCode_Black, ColorCode_Blue);

						if (index == 2 || index == 5)
						{
							strcpy_s(data.listSTR[index].str, dataEntry(data.listSTR[index].str, lLocationGet.lloca[index], NUMBER, 4));
						}
						else
						{
							strcpy_s(data.listSTR[index].str, dataEntry(data.listSTR[index].str, lLocationGet.lloca[index], NUMBER, 2));
						}
					}
				}
				isControl = false;
			}
			else
			{
				if (key == 13) // press enter
				{
					if (index == lLocationGet.size - 2)//OK
					{
						for (int i = 0; i < data.size; i++)
						{
							if (strlen(data.listSTR[i].str) == 0)
							{
								lcTemp = { lLocationGet.lloca[i].x - 2, lLocationGet.lloca[i].y - 1 };
								drawRectangle(lcTemp, lcTemp, sBox, ColorCode_Black, ColorCode_Blue);

								if (i == 2 || i == 5)
								{
									strcpy_s(data.listSTR[i].str, dataEntry(data.listSTR[i].str, lLocationGet.lloca[i], NUMBER, 4));
								}
								else
								{
									strcpy_s(data.listSTR[i].str, dataEntry(data.listSTR[i].str, lLocationGet.lloca[i], NUMBER, 2));
								}
							}
						}

						if (!conf_checkDATE(data)) // error
						{
							LOCATION lcDis = { (bill_Location_Gird_x + (75 / 2) - (static_cast<int>(strlen("Dinh Dang Khong Hop Le. Vui Long Nhap Lai!")) / 2)), bill_Location_Gird_y + 1 };
							dis_wait(lcDis, "Dinh Dang Khong Hop Le. Vui Long Nhap Lai!", 3, ColorCode_Red);
						}
						else
						{
							break;
						}

					}
					else if (index == lLocationGet.size - 1)
					{
						isCancle = true;
						break;
					}
				}
			}
		}
	}

	List_Clear(fields);
	List_Clear(lLocationGet);

	if (isCancle)
	{
		List_InsertItem(data, data.size, "CANCEL");
	}
	else
	{
		List_InsertItem(data, data.size, "DONE");
	}
}

void bill_InitTitleShowByDay(LIST_TITLE &title)
{
	TITLE t;
	strcpy_s(t.data, "Ma Hoa Don");
	t.width = bill_maxSize_Code + 4;

	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "Ngay lap hoa Don");
	int size = strlen(t.data);
	t.width = size > bill_maxSize_invoiceDate ? size + 4 : bill_maxSize_invoiceDate + 4;
	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "Loai");
	 size = strlen("Nhap");
	t.width = size > bill_maxSize_invoiceDate ? size + 4 : bill_maxSize_invoiceDate + 4;
	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "Ho & Ten");
	 size = strlen(t.data);
	t.width = size > (employees_maxSize_FirstName + employees_maxSize_FirstName) ? size + 4 : (employees_maxSize_FirstName + employees_maxSize_FirstName) + 4;
	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "Tri Gia");
	t.width = 9 + 4;
	List_InsertItem(title, title.size, t);
}

void bill_ShowListByDate(LIST_BILL lb, LIST_EMPLOYEES le, LIST_MATERIAL lm, LIST_ARRAY_CHAR date)
{
	LIST_TITLE title;
	LIST_LOCATION lcResult;
	LOCATION lcGird, lcShow, lcBtnDone, lcBtnView, lcTextHead, lcTextDay;
	Size sGird, sBtnDone, sBtnView;
	int quantity = 0;

	lcGird = { bill_Location_Gird_x, bill_Location_Gird_y };
	lcShow = { lcGird.x + 3, lcGird.y + 4 };
	bill_InitTitleShowByDay(title);

	quantity = dslk_Count(lb.pHead);

	drawBorder(lcResult, lcShow, quantity, 5, title);
	
	if (lb.pHead != NULL)
	{
		sGird = { ((lcResult.lloca[lcResult.size - 1].x + title.ltitle[title.size - 1].width) - lcGird.x) , (lcResult.lloca[lcResult.size - 1].y + 10) };
	}
	else
	{
		sGird = { 100,25 };
	}
	lcTextHead = { (((sGird.width / 2) + lcGird.y)) - (static_cast<int>(strlen("BANG LIET KE CAC HOA DON TRONG KHOANG THOI GIAN")) / 2),lcGird.y + 1 };
	lcTextDay = { (((sGird.width / 2) + lcGird.y)) - (45 / 2), lcGird.y + 2 };
	gotoxy(lcTextHead.x, lcTextHead.y); ColorText("BANG LIET KE CAC HOA DON TRONG KHOANG THOI GIAN", ColorCode_Red);

	gotoxy(lcTextDay.x, lcTextDay.y); cout << "Tu ngay: " << date.listSTR[0].str << "/" << date.listSTR[1].str << "/" << date.listSTR[2].str << "     " << "Den ngay: " << date.listSTR[3].str << "/" << date.listSTR[4].str << "/" << date.listSTR[5].str;

	drawBox(lcGird, sGird, "Show");

	for (NODE_BILL *p = lb.pHead; p != NULL; p = p->pNext)
	{
		int count = 0;
		for (NODE_BILL *p = lb.pHead; p != NULL; p = p->pNext)
		{
			int indexNow = count * 5;
			gotoxy(lcResult.lloca[indexNow].x, lcResult.lloca[indexNow].y); BGColorText(p->data.billNumber, ColorCode_Black, ColorCode_DarkWhite);
			gotoxy(lcResult.lloca[indexNow + 1].x, lcResult.lloca[indexNow + 1].y); BGColorText(p->data.invoiceDate, ColorCode_Black, ColorCode_DarkWhite);
			if (p->data.type == 'n' || p->data.type == 'N')
			{
				gotoxy(lcResult.lloca[indexNow + 2].x, lcResult.lloca[indexNow + 2].y); BGColorText("Nhap", ColorCode_Black, ColorCode_DarkWhite);
			}
			else if (p->data.type == 'x' || p->data.type == 'X')
			{
				gotoxy(lcResult.lloca[indexNow + 2].x, lcResult.lloca[indexNow + 2].y); BGColorText("Xuat", ColorCode_Black, ColorCode_DarkWhite);
			}
			
			//get full name;
			STR fullName = employees_GetFullName(le, p->data.employeesCode);
			gotoxy(lcResult.lloca[indexNow + 3].x, lcResult.lloca[indexNow + 3].y); BGColorText(fullName.str, ColorCode_Black, ColorCode_DarkWhite);
			//calculate
			int money = (int)bill_CalMoney(p->data.list_BillDetail);
			gotoxy(lcResult.lloca[indexNow + 4].x, lcResult.lloca[indexNow + 4].y); BGColorText(to_string(money).c_str(), ColorCode_Black, ColorCode_DarkWhite);
			count++;
		}
	}
	
	sBtnDone = sBtnView = { static_cast<int>(strlen("XONG")) + 4, 5 };
	lcBtnDone = { lcGird.x + 5, (sGird.height + lcGird.y) - 2 - sBtnDone.height };
	lcBtnView = { (lcGird.x + sGird.width) - 5 - sBtnView.width, (sGird.height + lcGird.y) - 2 - sBtnView.height };

	button(true, "XONG", lcBtnDone, sBtnDone, ColorCode_Blue, ColorCode_Black);
	button(false, "XEM.", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);

	int index = 0;
	while (true)
	{
		if (_kbhit())
		{
			int key = _getch();
			if (key == 75) // LEFT
			{
				index--;
				if (index < 0)
				{
					index = 1;

					button(false, "XONG", lcBtnDone, sBtnDone, ColorCode_Blue, ColorCode_Black);
					button(true, "XEM.", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
				}
				else
				{
					button(true, "XONG", lcBtnDone, sBtnDone, ColorCode_Blue, ColorCode_Black);
					button(false, "XEM.", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
				}
			}
			else if (key == 77) // RIGHT
			{
				index++;
				if (index > 1)
				{
					index = 0;

					button(true, "XONG", lcBtnDone, sBtnDone, ColorCode_Blue, ColorCode_Black);
					button(false, "XEM.", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
				}
				else
				{
					button(false, "XONG", lcBtnDone, sBtnDone, ColorCode_Blue, ColorCode_Black);
					button(true, "XEM.", lcBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
				}
			}
			else if (key == 13) // enter;
			{
				if (index == 0) // press OK
				{
					return;
				}
				else if (index == 1) // press View
				{
					system("cls");
					bill_Show(lb, lm, lcGird);
					return;
				}
			}
		}
	}
}

void bill_ShowByDate(LIST_BILL lb, LIST_EMPLOYEES le, LIST_MATERIAL lm)
{
	LIST_ARRAY_CHAR date, dateCompare;
	LIST_BILL billView; 
	dslk_Initialize(billView);

	bill_EntryDate(date);

	system("cls");

	if (strcmp(date.listSTR[date.size - 1].str, "CANCEL") == 0)
	{
		return;
	}
	else
	{
		for (NODE_BILL *p = lb.pHead; p != NULL; p = p->pNext)
		{
			converDateToArrDate(p->data.invoiceDate, dateCompare);
			if (conf_dateIsBetween(date, dateCompare))
			{
				dslk_addTail(billView, p);
			}
		}
		system("cls");
		
		bill_ShowListByDate(billView, le, lm, date);

		delete billView.pHead;
	}

	List_Clear(date);
	List_Clear(dateCompare);
}
#pragma endregion

void material_showHeightRevenue(LIST_BILL lb, LIST_MATERIAL lm)
{
	// entry day and get bill satisfy
	LIST_ARRAY_CHAR date, dateCompare;
	LIST_BILL billSatisfy;
	dslk_Initialize(billSatisfy);

	bill_EntryDate(date);

	system("cls");

	if (strcmp(date.listSTR[date.size - 1].str, "CANCEL") == 0)
	{
		return;
	}
	else
	{
		for (NODE_BILL *p = lb.pHead; p != NULL; p = p->pNext)
		{
			converDateToArrDate(p->data.invoiceDate, dateCompare);
			if (conf_dateIsBetween(date, dateCompare) && (p->data.type == 'x' || p->data.type == 'X')) //
			{
				dslk_addTail(billSatisfy, p);
			}
		}
	}

	List_Clear(date);
	List_Clear(dateCompare);
	//end

	// calculate money material
	LIST_MATERIAL stack[material_quantityMax];
	int sp = -1;
	LIST_MATERIAL p = lm;
	LIST_MATERIAL lmShow;
	treeInitialize(lmShow);
	int quantity = 0;

	while (p != NULL)
	{
		//xu ly
		MATERIAL m = p->data;
		int sumMoney = 0;
		for (NODE_BILL *nb = billSatisfy.pHead; nb != NULL; nb = nb->pNext)
		{
			for (NBD bd = nb->data.list_BillDetail; bd != NULL; bd = bd->pNext)
			{
				if (strcmp(bd->data.materialsCode, p->data.materialsCode) == 0)
				{
					int moneyNoVAT = (int)(bd->data.quantity * bd->data.unitPrice);
					int moneyVAT = moneyNoVAT + ((bd->data.percentVAT * moneyNoVAT) / 100);

					sumMoney += moneyVAT;
				}
			}
		}
		if (sumMoney != 0)
		{
			m.inventoryNumber = sumMoney; //Assign temp
			tree_insertByMoney(lmShow, m);
			quantity++;
		}

		if (p->pRight != NULL)
		{
			stack[++sp] = p->pRight;
		}
		if (p->pLeft != NULL)
		{
			p = p->pLeft;
		}
		else if (sp == -1)
		{
			break;
		}
		else
		{
			p = stack[sp--];
		}
	}
	//end
	quantity = materials_Count(lmShow);
	material_ViewRevenue(lmShow, quantity);
}