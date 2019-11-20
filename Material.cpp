#include "Material.h"

int avl_CalHeight(TREE tr)
{
	if (tr != NULL)
	{
		int lh = avl_CalHeight(tr->pLeft);
		int rh = avl_CalHeight(tr->pRight);

		return (lh > rh ? lh : rh) + 1;
	}
	else
		return 0;
}

int avl_calc_difficult(TREE tr)
{
	int lh, rh;

	if (tr == NULL)
	{
		return 0;
	}
	else if (tr->pLeft == NULL)
	{
		lh = 0;
		rh = avl_CalHeight(tr->pRight);
	}
	else if (tr->pRight == NULL)
	{
		rh = 0;
		lh = avl_CalHeight(tr->pLeft);
	}
	else
	{
		lh = avl_CalHeight(tr->pLeft);
		rh = avl_CalHeight(tr->pRight);
	}
	
	return lh - rh;
}

TREE avl_rotate_rr(TREE &parent)
{
	/*			A	
			B		=>		        B
		C		x			C				A
										x
	*/

	TREE temp = parent->pLeft;
	parent->pLeft = temp->pRight;
	temp->pRight = parent;

	return temp;
}

TREE avl_rotate_ll(TREE &parent)
{
	/*		  A (1)
				  B (0)			=>				B(-1)
			x(0)      	C (0)			A (1)			C (0)
											x (0)
	*/

	TREE temp = parent->pRight;
	parent->pRight = temp->pLeft;
	temp->pLeft = parent;

	return temp;
}

TREE avl_rotate_lr(TREE &parent)
{
	/*		A						A
		B			=>			C		=>			C
			C				B					B		A
	*/

	TREE temp = parent->pLeft;
	parent->pLeft = avl_rotate_ll(temp);
	return avl_rotate_rr(parent);
}

TREE avl_rotate_rl (TREE &parent)
{
	/*	A					A
			B		=>			C					C
		C							B			A		B
	*/
	TREE temp = parent->pRight;
	parent->pRight = avl_rotate_rr(temp);
	return avl_rotate_ll(parent);
}

void avl_balance(TREE &tr)
{
	int delta = avl_calc_difficult(tr);

	if (delta > 1) // cay lech ve ben trai
	{
		if (avl_calc_difficult(tr->pLeft) > 0) // lech trai
		{
			//std::cout << "Xoay Phai: " << tr->data.materialsCode << "/delta: " << delta << std::endl;
			tr = avl_rotate_rr(tr);
		}
		else
		{
			//std::cout << "Lech trai phai: rotate_lr: " << tr->data.materialsCode << "/delta: " << delta << std::endl;
			tr = avl_rotate_lr(tr);
		}
	}
	else if (delta < -1) // Ben phai dai hon ben trai // lech phai
	{
		if (avl_calc_difficult(tr->pRight) < 0) // Nhanh con lech phai
		{
			//std::cout << "Lech phai: rotate_ll: " << tr->data.materialsCode << "/delta: " << delta << std::endl;
			tr = avl_rotate_ll(tr);
		}
		else
		{
			//std::cout << "Lech phai trai: rotate_rl: " << tr->data.materialsCode << "/delta: " << delta << std::endl;
			tr = avl_rotate_rl(tr);
		}
	}
}

//insert by name
void avl_insert(TREE &tr, MATERIAL data)
{
	//insert by name
	if (tr == NULL)
	{
		tr = new nodeTree;
		tr->data = data;
		tr->pLeft = tr->pRight = NULL;
	}
	else
	{
		if (strcmp(data.materialsName, tr->data.materialsName) < 0)
		{
			avl_insert(tr->pLeft, data);
		}
		else if (strcmp(data.materialsName, tr->data.materialsName) > 0)
		{
			avl_insert(tr->pRight, data);
		}
	}

	//avl_balance(tr);  // tree BST => AVL 
}

void tree_insertByMoney(TREE &tr, MATERIAL data)
{
	if (tr == NULL)
	{
		tr = new nodeTree;
		tr->data = data;
		tr->pLeft = tr->pRight = NULL;
	}
	else
	{
		if (data.inventoryNumber < tr->data.inventoryNumber)
		{
			tree_insertByMoney(tr->pLeft, data);
		}
		else if (data.inventoryNumber >= tr->data.inventoryNumber)
		{
			tree_insertByMoney(tr->pRight, data);
		}
	}
}

void treeInitialize(TREE &tr)
{
	tr = NULL;
}

void treeRemoveCaseThree(TREE &tr, TREE &treeTemp)
{
	if (tr->pLeft != NULL)
	{
		treeRemoveCaseThree(treeTemp ,tr->pLeft);
	}
	else
	{
		treeTemp->data = tr->data;
		treeTemp = tr;
		tr = treeTemp->pRight;
	}
}

void avl_RemoveNode(TREE &tr, char *code)
{
	if (tr == NULL) // empty => node found
	{
		return;
	}
	else
	{
		if (strcmp(code, tr->data.materialsCode) < 0)
		{
			avl_RemoveNode(tr->pLeft, code);
		}
		else if (strcmp(code, tr->data.materialsCode) > 0)
		{
			avl_RemoveNode(tr->pRight, code);
		}
		else  // found key in tree
		{
			TREE tempTree = tr;

			if (tempTree->pRight == NULL) // have one node child left
			{
				tr = tempTree->pLeft;
			}
			else if (tempTree->pLeft == NULL)
			{
				tr = tempTree->pRight;
			}
			else // have two node child
			{
				treeRemoveCaseThree(tr->pRight, tempTree);
			}

			delete tempTree;
		}
	}

	//avl_balance(tr);
}

bool treeNodeIsExists(TREE tr, char *code)
{
	////LIST_MATERIAL temp;
	////temp = tr;
	//while (tr != NULL)
	//{
	//	if (strcmp(code, tr->data.materialsName) < 0)
	//	{
	//		tr = tr->pLeft;
	//	}
	//	else if (strcmp(code, tr->data.materialsName) > 0)
	//	{
	//		tr = tr->pRight;
	//	}
	//	else
	//	{
	//		//delete temp;
	//		return true;
	//	}
	//}
	//
	////delete temp;
	//return false;

	const int size = 100;
	TREE stack[size];
	int sp = -1;
	TREE temp = tr;
	while (temp != NULL)
	{
		if (strcmp(temp->data.materialsCode, code) == 0)
		{
			return true;
		}

		if (temp->pRight != NULL)
		{
			stack[++sp] = temp->pRight;
		}
		if (temp->pLeft != NULL)
		{
			temp = temp->pLeft;
		}
		else if (sp == -1)
		{
			break;
		}
		else
		{
			temp = stack[sp--];
		}
	}
	return false;
}

MATERIAL treeSearchNode(TREE tr, char *code)
{
	MATERIAL alpha;
	const int size = 100;
	TREE stack[size];
	int sp = -1;
	TREE temp = tr;
	while (temp != NULL)
	{
		if (strcmp(temp->data.materialsCode, code) == 0)
		{
			return temp->data;
		}

		if (temp->pRight != NULL)
		{
			stack[++sp] = temp->pRight;
		}
		if (temp->pLeft != NULL)
		{
			temp = temp->pLeft;
		}
		else if (sp == -1)
		{
			break;
		}
		else
		{
			temp = stack[sp--];
		}
	}
	alpha.materialsCode[0] = '\0'; // not found
	return alpha;
}

void NLR(TREE tr)
{
	if (tr != NULL)
	{
		std::cout << tr->data.materialsCode<< std::endl;
		NLR(tr->pLeft);
		NLR(tr->pRight);
	}
}

void materials_EditQuantity(LIST_MATERIAL &tr, char *code, int quantity)
{
	LIST_MATERIAL stack[material_quantityMax];
	int sp = -1;
	int count = 0;
	LIST_MATERIAL p = tr;

	while (p != NULL)
	{
		//xu ly
		if (strcmp(code, p->data.materialsCode) == 0)
		{
			p->data.inventoryNumber += quantity;
			break;
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
}

bool materials_EditInformation(LIST_MATERIAL &tr, char *code, MATERIAL newData) 
{
	LIST_MATERIAL temp;
	temp = tr;
	while (temp != NULL)
	{
		if (strcmp(code, temp->data.materialsCode) < 0)
		{
			temp = temp->pLeft;
		}
		else if (strcmp(code, temp->data.materialsCode) > 0)
		{
			temp = temp->pRight;
		}
		else
		{
			strcpy_s(temp->data.materialsName, newData.materialsName);
			strcpy_s(temp->data.countUnit, newData.countUnit);
			temp->data.inventoryNumber = newData.inventoryNumber;
			
			tr = temp;
			//delete temp;
			return true;
		}
	}
	//delete temp;
	return false;
}

void materials_InitProperties(LIST_PROPERTIES &prop)
{
	PROPERTIES item;
	item.variables.color = ColorCode_White;

	strcpy_s(item.variables.name, "Ma Vat Tu");
	strcpy_s(item.variables.notify, "Format: 0-9, A-Z");
	strcpy_s(item.variables.data, "");
	item.mode.modeImport = UPPER_NUMBER;
	item.mode.enable = true;
	item.maxLength = material_maxSize_Code;
	List_InsertItem(prop, prop.size, item);

	strcpy_s(item.variables.name, "Ten Vat Tu");
	strcpy_s(item.variables.notify, "0-9, A-Z, a-z, sp");
	strcpy_s(item.variables.data, "");
	item.mode.modeImport = ALL_SPACE;
	item.mode.enable = true;
	item.maxLength = material_maxSize_Name;
	List_InsertItem(prop, prop.size, item);

	strcpy_s(item.variables.name, "Don Vi Tinh");
	strcpy_s(item.variables.notify, "Format: a-z");
	strcpy_s(item.variables.data, "");
	item.mode.modeImport = LOWER;
	item.mode.enable = true;
	item.maxLength = material_maxSize_CountUnit;
	List_InsertItem(prop, prop.size, item);

	strcpy_s(item.variables.name, "So Luong Ton");
	strcpy_s(item.variables.notify, "Format: 0-9");
	strcpy_s(item.variables.data, "");
	item.mode.modeImport = NUMBER;
	item.mode.enable = true;
	item.maxLength = material_maxSize_InventoryNumber;
	List_InsertItem(prop, prop.size, item);
}

STR materials_ImportCodeMaterial(char *notify, int color, char *text)
{
	LIST_PROPERTIES arrProp;
	PROPERTIES item;

	strcpy_s(item.variables.name, "Ma Vat Tu");
	item.variables.color = color;
	strcpy_s(item.variables.notify, notify);
	strcpy_s(item.variables.data, text);
	item.mode.modeImport = UPPER_NUMBER;
	item.mode.enable = true;
	item.maxLength = material_maxSize_Code;
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

MATERIAL materials_DataEntry(LIST_MATERIAL tr, LIST_PROPERTIES prop, bool &isCancel)
{
	MATERIAL item;

	LOCATION lc;
	lc.x = 5; lc.y = 5;

	LIST_ARRAY_CHAR arrData;
	enterDataToVariable(arrData, prop, lc);

	while (true)
	{
		char code[50];
		strcpy_s(code, arrData.listSTR[0].str);
		if (strcmp(arrData.listSTR[arrData.size - 1].str, "DONE") == 0)
		{
			if (treeNodeIsExists(tr, code))
			{
				system("cls");
				prop.lprop[0].variables.color = ColorCode_Red;
				strcpy_s(prop.lprop[0].variables.notify, "Material not exist");
				

				strcpy_s(prop.lprop[0].variables.data, "");
				strcpy_s(prop.lprop[1].variables.data, arrData.listSTR[1].str);
				strcpy_s(prop.lprop[2].variables.data, arrData.listSTR[2].str);
				strcpy_s(prop.lprop[3].variables.data, arrData.listSTR[3].str);

				List_Reset(arrData);

				system("cls");
				enterDataToVariable(arrData, prop, lc);
			}
			else
				break;
		}
		else if (strcmp(arrData.listSTR[arrData.size - 1].str, "CANCEL") == 0)
		{
			List_Clear(arrData);
			break;
		}
	}

	if (arrData.size != 0)
	{
		strcpy_s(item.materialsCode, arrData.listSTR[0].str);
		strcpy_s(item.materialsName, arrData.listSTR[1].str);
		strcpy_s(item.countUnit, arrData.listSTR[2].str);
		item.inventoryNumber = atoi(arrData.listSTR[3].str);

		List_Clear(arrData);
	}
	else
		isCancel = true;

	return item;
}

bool materials_AddToList(LIST_MATERIAL &tr)
{
	bool isCancel = false;
	MATERIAL item;

	LIST_PROPERTIES prop;
	materials_InitProperties(prop); //init

	system("cls");
	item = materials_DataEntry(tr, prop, isCancel);

	if (!isCancel)
	{
		avl_insert(tr, item); // insert to tree
		return true;
	}
	return false;
}

void materials_Add(LIST_MATERIAL &tr)
{
	LOCATION lcDisplay; lcDisplay.x = lcDisplay.y = 5;
	bool isYes = true;
	while (isYes)
	{
		if (materials_AddToList(tr))
		{
			system("cls");
			isYes = messagebox("Ban da them vat tu thanh cong. Ban co muon nhap tiep khong?", YES_NO, lcDisplay);
		}
		else
		{
			system("cls");
			isYes = messagebox("Dan da huy qua trinh nhap. Ban co muon tiep tuc nhap khong?", YES_NO, lcDisplay);
		}
	}
}

bool materials_Remove(LIST_MATERIAL &tr)
{
	STR code;
	code = materials_ImportCodeMaterial("Format: 0-9, A-Z", ColorCode_White, "");
	if (strcmp(code.str, "") == 0)// cancel
	{
		return false;
	}
	else
	{
		while (true)
		{
			if (treeNodeIsExists(tr, code.str))
			{
				avl_RemoveNode(tr, code.str);

				messagebox("Da xoa vat tu thanh cong.", YES, LOCATION());
				return true;

			}
			else
			{
				std::system("cls");
				code = materials_ImportCodeMaterial("Not exist", ColorCode_Red, code.str);
				if (strcmp(code.str, "") == 0)// cancel
				{
					return false;
				}
			}
		}
	}
}


bool materials_Edit(LIST_MATERIAL &tr)
{
	LOCATION displayLC;
	displayLC.x = displayLC.y = 5;

	char notify[maxLengthChar];
	strcpy_s(notify, "Format: 0-9, A-Z");
	int color = ColorCode_White;
	STR code;

	while (true)
	{
		code = materials_ImportCodeMaterial(notify, color, "");

		if (strcmp(code.str, "") == 0)// cancel
		{
			return false;
		}
		else
		{
			if (treeNodeIsExists(tr, code.str))
			{
				break;
			}
			else
			{
				strcpy_s(notify, "Code M not exist");
				color = ColorCode_Red;
			}
		}
	}

	MATERIAL temp = treeSearchNode(tr, code.str);

	//init
	LIST_PROPERTIES prop;
	materials_InitProperties(prop);

	prop.lprop[0].mode.enable = false;
	prop.lprop[3].mode.enable = false;

	//add data to box import data
	strcpy_s(prop.lprop[0].variables.data, temp.materialsCode);
	strcpy_s(prop.lprop[1].variables.data, temp.materialsName);
	strcpy_s(prop.lprop[2].variables.data, temp.countUnit);
	//prop[3].variables.data = "" + temp->data.inventoryNumber;
	char *a = new char[material_maxSize_InventoryNumber];
	_itoa_s(temp.inventoryNumber, a, material_maxSize_InventoryNumber, 10);
	strcpy_s(prop.lprop[3].variables.data, a);
	delete[] a;

	//get data
	system("cls");
	LIST_ARRAY_CHAR data;
	enterDataToVariable(data, prop, displayLC);

	if (strcmp(data.listSTR[data.size - 1].str, "CANCEL") == 0)
	{
		return false;
	}

	//convert data to materials
	MATERIAL item;
	strcpy_s(item.materialsName, data.listSTR[1].str);
	strcpy_s(item.countUnit, data.listSTR[2].str);
	item.inventoryNumber = atoi(data.listSTR[3].str);

	// update new data
	if (materials_EditInformation(tr, code.str, item))
	{
		List_Clear(prop);
		//delete temp;
		return true;
	}
	//delete temp;
	List_Clear(prop);
	return false;
}

int materials_Count(TREE tr)
{
	LIST_MATERIAL stack[material_quantityMax];
	int sp = -1;
	int count = 0;
	LIST_MATERIAL p = tr;

	while (p != NULL)
	{
		//xu ly
		count++;

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
	return count;
}

void materials_InitTitle(LIST_TITLE &title)
{
	TITLE t;

	strcpy_s(t.data, "Ma Vat Tu");
	int size = strlen(t.data);
	t.width = (size > material_maxSize_Code ? size : material_maxSize_Code) + 4;
	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "Ten Vat Tu");
	size = strlen(t.data);
	t.width = (size > material_maxSize_Name ? size : material_maxSize_Name) + 4;
	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "Don Vi Tinh");
	size = strlen(t.data);
	t.width = (size > material_maxSize_CountUnit ? size : material_maxSize_CountUnit) + 4;
	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "So Luong Ton");
	t.width = strlen(t.data) + 4;
	List_InsertItem(title, title.size, t);
}

void material_Show(LIST_MATERIAL lm, LOCATION lcDisplay, int modeShow)
{
	//modeShow = 0 => show view
	//!=0 => show to do something
	int material_quantityNow = materials_Count(lm);

	Size sBtnDONE, sGird;
	LOCATION lBtnDONE, lcDraw;

	sBtnDONE = { static_cast<int>(strlen("XONG") + 4), 5 };
	lcDraw = { lcDisplay.x + 3, lcDisplay.y + 7 };

	LIST_TITLE title;
	materials_InitTitle(title);

	LIST_LOCATION listLC;

	drawBorder(listLC, lcDraw, material_quantityNow, 5, title);
 
	if (listLC.size == 0)
	{
		sGird = {64, 15};
	}
	else
	{
		sGird = { (listLC.lloca[listLC.size - 1].x + title.ltitle[title.size - 1].width + 3) - lcDisplay.x, (listLC.lloca[listLC.size - 1].y + 5) - lcDisplay.y };
	}
	drawBox(lcDisplay, sGird, "Danh Sach Vat Tu");

	lBtnDONE = { (sGird.width / 2) - (sBtnDONE.width / 2) + lcDisplay.x, lcDisplay.y + 2 };
	button(true, "XONG", lBtnDONE, sBtnDONE, ColorCode_Blue, ColorCode_Black);

	LIST_MATERIAL stack[material_quantityMax];
	int sp = -1;
	int count = 0;
	LIST_MATERIAL p = lm;

	//NLR
	/*while (p != NULL)
	{
		//xu ly
		/*int indexNow = count * material_quantityFields;
		gotoxy(listLC.lloca[indexNow].x, listLC.lloca[indexNow].y); BGColorText(p->data.materialsCode, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLC.lloca[indexNow + 1].x, listLC.lloca[indexNow + 1].y); BGColorText(p->data.materialsName, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLC.lloca[indexNow + 2].x, listLC.lloca[indexNow + 2].y); BGColorText(p->data.countUnit, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLC.lloca[indexNow + 3].x, listLC.lloca[indexNow + 3].y); BGColorText(to_string(p->data.inventoryNumber).c_str(), ColorCode_Black, ColorCode_DarkWhite);
		count++;

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
	*/
	
	//RNL
	while (true)
	{
		while (p != NULL)
		{
			stack[++sp] = p;
			p = p->pRight;
		}

		if (sp != -1)
		{
			p = stack[sp--];

			//do something
			int indexNow = count * material_quantityFields;
			gotoxy(listLC.lloca[indexNow].x, listLC.lloca[indexNow].y); BGColorText(p->data.materialsCode, ColorCode_Black, ColorCode_DarkWhite);
			gotoxy(listLC.lloca[indexNow + 1].x, listLC.lloca[indexNow + 1].y); BGColorText(p->data.materialsName, ColorCode_Black, ColorCode_DarkWhite);
			gotoxy(listLC.lloca[indexNow + 2].x, listLC.lloca[indexNow + 2].y); BGColorText(p->data.countUnit, ColorCode_Black, ColorCode_DarkWhite);
			gotoxy(listLC.lloca[indexNow + 3].x, listLC.lloca[indexNow + 3].y); BGColorText(to_string(p->data.inventoryNumber).c_str(), ColorCode_Black, ColorCode_DarkWhite);
			count++;

			p = p->pLeft;
		}
		else
			break;
	}
	
	if (modeShow == 0)
	{
		while (true)
		{
			int key = _getch();
			if (key == key_ENTER)
				break;
		}
	}

	List_Clear(listLC);
	List_Clear(title);
}

void material_showAlone(MATERIAL m, LOCATION lcDisplay)
{
	LIST_TITLE title;
	LIST_LOCATION listLC;

	Size sBtnDONE, sGird;
	LOCATION lBtnDONE, lcDraw;

	sBtnDONE = { static_cast<int>(strlen("XONG") + 4), 5 };
	lcDraw = { lcDisplay.x + 3, lcDisplay.y + 7 };

	materials_InitTitle(title);
	drawBorder(listLC, lcDraw, 1, 5, title);
	
	gotoxy(listLC.lloca[0].x, listLC.lloca[0].y); BGColorText(m.materialsCode, ColorCode_Black, ColorCode_DarkWhite);
	gotoxy(listLC.lloca[1].x, listLC.lloca[1].y); BGColorText(m.materialsName, ColorCode_Black, ColorCode_DarkWhite);
	gotoxy(listLC.lloca[2].x, listLC.lloca[2].y); BGColorText(m.countUnit, ColorCode_Black, ColorCode_DarkWhite);
	
	char temp[material_maxSize_InventoryNumber + 2];
	_itoa_s(m.inventoryNumber, temp, 10);
	gotoxy(listLC.lloca[3].x, listLC.lloca[3].y); BGColorText(temp, ColorCode_Black, ColorCode_DarkWhite);

	sGird = { ((listLC.lloca[listLC.size - 1].x + title.ltitle[title.size - 1].width) - lcDisplay.x), (listLC.lloca[listLC.size - 1].y + 4) - lcDisplay.y };
	drawBox(lcDisplay, sGird, "Thong tin vat tu");

	lBtnDONE = {(sGird.width / 2) - (sBtnDONE.width / 2) + lcDisplay.x, lcDisplay.y + 2};
	button(true, "XONG", lBtnDONE, sBtnDONE, ColorCode_Blue, ColorCode_Black);

	while (true)
	{
		int key = _getch();
		if (key == 13)
		{
			dis_Clear(lcDisplay, sGird); // remove show
			return;
		}
	}
}

void initShowRevenue(LIST_TITLE &title)
{
	TITLE t;
	strcpy_s(t.data, "Ma Vat Tu");
	t.width = strlen(t.data) + 4;

	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "Ten Vat Tu");
	int size = strlen(t.data);
	t.width = size > material_maxSize_Name ? (size + 4) : (material_maxSize_Name + 4);

	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "Doanh Thu (000 d)");
	t.width = strlen(t.data) + 4;

	List_InsertItem(title, title.size, t);
}

void material_ViewRevenue(LIST_MATERIAL lmShow, int quantity)
{
	LIST_TITLE title;
	LIST_LOCATION lcResult;
	LOCATION lcGird, lcShow;
	Size sGird;

	lcGird = { 2, 2 };
	lcShow = { lcGird.x + 3, lcGird.y + 4 };
	initShowRevenue(title);

	if (quantity < 10)
	{
		drawBorder(lcResult, lcShow, quantity, 5, title);
	}
	else
	{
		drawBorder(lcResult, lcShow, 10, 5, title);
	}

	if (quantity == 0)
	{
		sGird = {55, 15};
	}
	else
	{
		sGird = { (lcResult.lloca[lcResult.size - 1].x + title.ltitle[title.size - 1].width) - lcGird.x, (lcResult.lloca[lcResult.size - 1].y + 5) - lcGird.y };
	}

	drawBox(lcGird, sGird, "Vat Tu Co Doanh Thu Cao");

	int count = 0;
	nodeTree *p;
	while (lmShow)
	{
		if (lmShow->pRight == NULL)
		{
			//cout << lmShow->data << " ";
			int indexNow = count * title.size;
			gotoxy(lcResult.lloca[indexNow].x, lcResult.lloca[indexNow].y); BGColorText(lmShow->data.materialsCode, ColorCode_Black, ColorCode_DarkWhite);
			gotoxy(lcResult.lloca[indexNow + 1].x, lcResult.lloca[indexNow + 1].y); BGColorText(lmShow->data.materialsName, ColorCode_Black, ColorCode_DarkWhite);
			char money[12];
			_itoa_s(lmShow->data.inventoryNumber, money, 10);
			gotoxy(lcResult.lloca[indexNow + 2].x, lcResult.lloca[indexNow + 2].y); BGColorText(money, ColorCode_Black, ColorCode_DarkWhite);
			count++;
			if (count >= 10)
				break;
			lmShow = lmShow->pLeft;
		}
		else
		{
			p = lmShow->pRight;
			while (p->pLeft && p->pLeft != lmShow)
			{
				p = p->pLeft;
			}
			if (p->pLeft == NULL)
			{
				p->pLeft = lmShow;
				lmShow = lmShow->pRight;
			}
			else
			{
				p->pLeft = NULL;
				//cout << lmShow->data << " ";
				int indexNow = count * title.size;
				gotoxy(lcResult.lloca[indexNow].x, lcResult.lloca[indexNow].y); BGColorText(lmShow->data.materialsCode, ColorCode_Black, ColorCode_DarkWhite);
				gotoxy(lcResult.lloca[indexNow + 1].x, lcResult.lloca[indexNow + 1].y); BGColorText(lmShow->data.materialsName, ColorCode_Black, ColorCode_DarkWhite);
				char money[12];
				_itoa_s(lmShow->data.inventoryNumber, money, 10);
				gotoxy(lcResult.lloca[indexNow + 2].x, lcResult.lloca[indexNow + 2].y); BGColorText(money, ColorCode_Black, ColorCode_DarkWhite);
				count++;
				if (count >= 10)
					break;
				lmShow = lmShow->pLeft;
			}
		}
	}
	_getch();
}