#include "BillDetail.h"

void dslk_InitBD(NBD &bd)
{
	bd = NULL;
}

NBD dslk_CreateNodeBD(BILLDETAILS data)
{
	NBD p = new NODE_BILLDETAILS;

	if (p == NULL)
		return NULL;

	p->data = data;
	p->pNext = NULL;

	return p;
}

void dslk_addHeadBD(NBD &nb, NBD itemAdd)
{
	if (nb == NULL) // empty
	{
		nb = itemAdd;
	}
	else
	{
		itemAdd->pNext = nb;
		nb = itemAdd;
	}
}

void dslk_addTailBD(NBD &nb, NBD itemAdd)
{

	//if (nb == NULL) //Danh sách đang rỗng.
	//{
	//	nb = itemAdd;  // item vừa là đầu vừa là cuối.
	//}
	//if (nb->pNext == NULL)
	//{
	//	nb->pNext = itemAdd;
	//}
	//else
	//{
	//	NBD p = nb;
	//	while (p->pNext != NULL)
	//	{
	//		p = p->pNext;
	//	}
	//}
}

int dslk_Count(NODE_BILLDETAILS* bd)
{
	int cout = 0;

	for (NODE_BILLDETAILS *p = bd; p != NULL; p = p->pNext)
	{
		cout++;
	}
	return cout;
}

NBD dslk_find(NBD nb, char *code)
{
	for (NBD p = nb; p != NULL; p = p->pNext)
	{
		if (strcmp(p->data.materialsCode, code) == 0)
		{
			return p;
		}
	}
	return NULL;
}

bool dslk_removeNodeBD(NBD &nb, NBD itemDelete)
{
	if (nb == NULL)
	{
		return false;
	}
	else
	{
		if (strcmp((nb->data).materialsCode, itemDelete->data.materialsCode) == 0)
		{
			NBD p = nb;
			nb = nb->pNext;
			delete p;
			return true;
		}
		for (NBD p = nb; p->pNext != NULL; p = p->pNext)
		{
			if (strcmp(((p->pNext)->data).materialsCode, itemDelete->data.materialsCode) == 0)
			{
				NBD temp = p->pNext;
				p->pNext = (p->pNext)->pNext;
				delete temp;
				return true;
			}
		}
		return false;
	}
}

bool dslk_removeByCode(NBD &nb, char *code)
{
	if (nb == NULL)
	{
		return false;
	}
	else
	{
		if (strcmp((nb->data).materialsCode, code) == 0)
		{
			NBD p = nb;
			nb = nb->pNext;
			delete p;
			return true;
		}
		for (NBD p = nb; p->pNext != NULL; p = p->pNext)
		{
			if (strcmp(((p->pNext)->data).materialsCode, code) == 0)
			{
				NBD temp = p->pNext;
				p->pNext = (p->pNext)->pNext;
				delete temp;
				return true;
			}
		}
		return false;
	}
}

void bd_initProperties(LIST_PROPERTIES &prop)
{
	PROPERTIES p;

	strcpy_s(p.variables.data, "");
	strcpy_s(p.variables.name, "Ma Vat Tu");
	strcpy_s(p.variables.notify, "Format: 0-9, A-Z");
	p.variables.color = ColorCode_DarkWhite;
	p.maxLength = material_maxSize_Code;
	p.mode.enable = true;
	p.mode.modeImport = UPPER_NUMBER;

	List_InsertItem(prop, prop.size, p);

	strcpy_s(p.variables.data, "");
	strcpy_s(p.variables.name, "So Luong");
	strcpy_s(p.variables.notify, "Format: 0-9");
	p.variables.color = ColorCode_DarkWhite;
	p.maxLength = billD_maxSize_quantity;
	p.mode.enable = true;
	p.mode.modeImport = NUMBER;

	List_InsertItem(prop, prop.size, p);

	strcpy_s(p.variables.data, "");
	strcpy_s(p.variables.name, "Don Gia");
	strcpy_s(p.variables.notify, "Format: 0-9");
	p.variables.color = ColorCode_DarkWhite;
	p.maxLength = billD_maxSize_unitPrice;
	p.mode.enable = true;
	p.mode.modeImport = NUMBER;

	List_InsertItem(prop, prop.size, p);

	strcpy_s(p.variables.data, "");
	strcpy_s(p.variables.name, "VAT");
	strcpy_s(p.variables.notify, "Format: 0-9");
	p.variables.color = ColorCode_DarkWhite;
	p.maxLength = billD_maxSize_VAT;
	p.mode.enable = true;
	p.mode.modeImport = NUMBER;

	List_InsertItem(prop, prop.size, p);
}

void bd_initTitle(LIST_TITLE &title)
{
	TITLE t;
	strcpy_s(t.data, "Ma Vat Tu");
	int size = strlen(t.data);
	t.width = (size > material_maxSize_Code ? size : material_maxSize_Code) + 4;

	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "So Luong");
	size = strlen(t.data);
	t.width = (size > billD_maxSize_quantity ? size : billD_maxSize_quantity) + 4;

	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "Don Gia");
	size = strlen(t.data);
	t.width = (size > billD_maxSize_unitPrice ? size : billD_maxSize_unitPrice) + 4;

	List_InsertItem(title, title.size, t);

	strcpy_s(t.data, "%VAT");
	size = strlen(t.data);
	t.width = (size > billD_maxSize_VAT ? size : billD_maxSize_VAT) + 4;

	List_InsertItem(title, title.size, t);
}

void bd_Show(NBD bd, LIST_MATERIAL lm, LOCATION lcDisplay, int &bottom, int modeView)
{
	//modeView == 0 => view detail
	//modeView == 1 => just view
	LIST_LOCATION listLC;
	LIST_TITLE title;
	LOCATION headList = { lcDisplay.x + 3, lcDisplay.y + 10 };
	LOCATION  lcChoose;
	LIST_ARRAY_CHAR notify;
	Size sizeGird;
	Size sClearView = { 0, 0 };

	if (modeView == 0)
	{
		List_InsertItem(notify, notify.size, "CMaterial");
		List_InsertItem(notify, notify.size, "0-9, A-Z");
		List_InsertItem(notify, notify.size, "Ma vat tu khong ton tai");

		lcChoose = { lcDisplay.x, lcDisplay.y};
	}

	bd_initTitle(title);

	drawBorder(listLC, headList, dslk_Count(bd), 5, title);

	int count = 0;
	for (NBD p = bd; p != NULL; p = p->pNext)
	{
		int indexNow = count * billD_quantityFields;
		gotoxy(listLC.lloca[indexNow].x, listLC.lloca[indexNow].y);	BGColorText(p->data.materialsCode, ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLC.lloca[indexNow + 1].x, listLC.lloca[indexNow + 1].y); BGColorText(to_string(p->data.quantity).c_str(), ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLC.lloca[indexNow + 2].x, listLC.lloca[indexNow + 2].y); BGColorText(to_string(int(p->data.unitPrice)).c_str(), ColorCode_Black, ColorCode_DarkWhite);
		gotoxy(listLC.lloca[indexNow + 3].x, listLC.lloca[indexNow + 3].y);  BGColorText(to_string(p->data.percentVAT).c_str(), ColorCode_Black, ColorCode_DarkWhite);
		count++;
	}

	if (count > 0)
	{
		bottom = listLC.lloca[(count - 1) * billD_quantityFields].y;
	}
	else
	{
		bottom = lcDisplay.y + 10;
	}
	
	if (modeView == 0)
	{
		sizeGird = { (listLC.lloca[listLC.size - 1].x + title.ltitle[title.size - 1].width - lcDisplay.x) + 2, listLC.lloca[listLC.size - 1].y + 4 - lcDisplay.y };
		drawBox(lcDisplay, sizeGird, "Chi Tiet Hoa Don");
		//action
		while (true)
		{
			STR codeMaterial;
			LIST_BILL temp; temp.pHead = NULL;
			LIST_EMPLOYEES le;

			codeMaterial = dis_chooseViewDetail(temp, bd, le,lcChoose, sizeGird.width, notify, 1);
			if (strcmp(codeMaterial.str, "DONE") == 0)
			{
				LOCATION lcView;
				lcView = { lcDisplay.x + sizeGird.width + 4 , lcDisplay.y };
				dis_Clear(lcDisplay, sizeGird);
				break;
			}
			else
			{
				//view detail
				LOCATION lcView;
				lcView = { lcDisplay.x + sizeGird.width + 4 , lcDisplay.y };
				material_showAlone(treeSearchNode(lm, codeMaterial.str), lcView);
				dis_Clear(lcView, sizeGird);
			}
		}
	}
}

bool bd_AddToList(NBD &bd, LIST_MATERIAL &lm, char type)
{
	LOCATION lcEntry, lcShow;

	lcEntry.x = billD_Location_Gird_x + 3; lcEntry.y = billD_Location_Gird_y + 5;
	lcShow.x = lcEntry.x + 35; lcShow.y = billD_Location_Gird_y + 2;

	material_Show(lm, lcShow, 1);

	int getX = wherex();
	int getY = wherey();

	LOCATION lcGird;
	lcGird.x = billD_Location_Gird_x; lcGird.y = billD_Location_Gird_y;

	Size sizeGird;
	if (lm == NULL)
	{
		sizeGird = {105, 33};
	}
	else
	{
		sizeGird.width = (getX - billD_Location_Gird_x) + 17;
		sizeGird.height = (getY - billD_Location_Gird_y) + 7;
	}

	drawBox(lcGird, sizeGird, "Nhap chi tiet hoa don");

	LIST_PROPERTIES prop;
	LIST_ARRAY_CHAR arrData;

	bd_initProperties(prop);

	while (true)
	{
		bool check = true;
		List_Reset(arrData);
		enterDataToVariable(arrData, prop, lcEntry);

		MATERIAL alpha = treeSearchNode(lm, arrData.listSTR[0].str);
		if (strlen(alpha.materialsCode) == 0)
		{
			if (strcmp(arrData.listSTR[arrData.size - 1].str, "CANCEL") == 0)
			{
				break;
			}
			else
			{
				//update properties
				strcpy_s(prop.lprop[0].variables.notify, "Material not exist");
				prop.lprop[0].variables.color = ColorCode_Red;
				//copy data
				strcpy_s(prop.lprop[1].variables.data, arrData.listSTR[1].str);
				strcpy_s(prop.lprop[2].variables.data, arrData.listSTR[2].str);
				strcpy_s(prop.lprop[3].variables.data, arrData.listSTR[3].str);
				check = false;
			}
		}
		else
		{
			if (type == 'X' || type == 'x')
			{
				if (unsigned(atoi(arrData.listSTR[1].str)) > alpha.inventoryNumber)
				{
					//update properties
					char t[50] = { '\0' };
					strcpy_s(t, "So luong ton: ");
					char c[10] = { '\0' };
					_itoa_s(alpha.inventoryNumber, c, 10);
					strcat_s(t, sizeof t, c);

					strcpy_s(prop.lprop[1].variables.notify, t);
					prop.lprop[1].variables.color = ColorCode_Red;
					//copy data
					strcpy_s(prop.lprop[0].variables.data, arrData.listSTR[0].str);
					strcpy_s(prop.lprop[2].variables.data, arrData.listSTR[2].str);
					strcpy_s(prop.lprop[3].variables.data, arrData.listSTR[3].str);

					check = false;
				}
			}
			else
			{
				//Import
			}
		}

		if (check)
		{
			if (strcpy_s(arrData.listSTR[arrData.size - 1].str, "DONE") == 0)
			{
				BILLDETAILS b;
				strcpy_s(b.materialsCode, arrData.listSTR[0].str);
				b.quantity = atoi(arrData.listSTR[1].str);
				b.unitPrice = atoi(arrData.listSTR[2].str);
				b.percentVAT = atoi(arrData.listSTR[3].str);

				if (type == 'X' || type == 'x')
				{
					materials_EditQuantity(lm, arrData.listSTR[0].str, -b.quantity);
					//alpha->data.inventoryNumber -= b.quantity;  // update new quantity
				}
				else if (type == 'N' || type == 'n')
				{
					materials_EditQuantity(lm, arrData.listSTR[0].str, b.quantity);
					//alpha->data.inventoryNumber += b.quantity;  // update new quantity
				}

				bool isExist = false;
				NBD p = bd;
				for (; p != NULL; p = p->pNext)
				{
					if (strcmp(p->data.materialsCode, b.materialsCode) == 0)
					{
						isExist = true;
						break;
					}
				}

				if (isExist)
				{
					p->data.quantity += b.quantity;
				}
				else
				{
					dslk_addHeadBD(bd, dslk_CreateNodeBD(b));
				}

				List_Clear(prop);
				List_Clear(arrData);
				return true;
			}
			else
			{
				List_Clear(prop);
				List_Clear(arrData);
				return false;
			}
		}
	}
}

void bd_Confirm(NBD &bd, LIST_MATERIAL &lm, char type)
{
	LIST_MATERIAL lmTemp = NULL;
	LIST_BILL lbTemp; lbTemp.pHead = NULL;

	system("cls");
	LOCATION lcShowList, lcGird, lcChoose;
	Size sGird;
	int bottom = 0;
	LIST_ARRAY_CHAR notify;

	List_InsertItem(notify, notify.size, "MVT");
	List_InsertItem(notify, notify.size, "0-9, A-Z");
	List_InsertItem(notify, notify.size, "Ma vat tu khong ton tai");

NguyenDZ:

	lcGird = { billD_Location_Gird_x, billD_Location_Gird_y };
	lcShowList = { lcGird.x, lcGird.y + 3};
	lcChoose = { lcGird.x, lcGird.y };

	bd_Show(bd, lmTemp, lcShowList, bottom, 1);

	if (bd == NULL)
	{
		sGird = { 51 ,bottom + 5 };
	}
	else
	{
		sGird = { 51 ,bottom + 2 };
	}

	drawBox(lcGird, sGird, "Xac Nhan");

	while (true)
	{
		STR codeM;
		LIST_EMPLOYEES le;
		codeM = dis_chooseViewDetail(lbTemp, bd, le, lcChoose, sGird.width, notify, 0);
		//xoa theo code M roi update lai danh sach
		if (strcmp(codeM.str, "DONE") == 0)
		{
			//viet them truong hop xoa het mvt khong co gi trong danh sach
			break;
		}
		else
		{
			NBD nbDel = dslk_find(bd, codeM.str);
			if (dslk_removeByCode(bd, codeM.str)) // remove success
			{
				LOCATION lcTextWait;
				lcTextWait = { static_cast<int>(((sGird.width - lcGird.x) / 2) - (strlen("Dang tien hanh xoa.") / 2)) + 2, lcChoose.x + 8 };
				dis_wait(lcTextWait, "Dang tien hanh xoa.", 3, ColorCode_Red);

				//update new quantity
				if (type == 'N' || type == 'n')
				{
					materials_EditQuantity(lm, codeM.str, -nbDel->data.quantity);
				}
				else if (type == 'X' || type == 'x')
				{
					materials_EditQuantity(lm, codeM.str, nbDel->data.quantity);
				}

				//showlist
				system("cls");
				goto NguyenDZ;
			}
			else
			{
				LOCATION lcTextWait;
				lcTextWait = { static_cast<int>(((sGird.width - lcGird.x) / 2) - (strlen("Khong the tien hanh xoa.") / 2)) + 2, lcChoose.x + 8 };
				dis_wait(lcTextWait, "Khong the tien hanh xoa.", 3, ColorCode_Red);
			}
		}
	}
}

void bd_Add(NBD &bd, LIST_MATERIAL &lm, char type)
{
	LOCATION lcDisplay;
	lcDisplay.x = lcDisplay.y = 5;

	bool isCancel = false;
	while (!isCancel)
	{
		system("cls");
		if (bd_AddToList(bd, lm, type))
		{
			system("cls");
			isCancel = !messagebox("Ban da them vat tu thanh cong. Ban co muon nhap tiep khong?", YES_NO, lcDisplay);
		}
		else
		{
			system("cls");
			isCancel = messagebox("Ban da huy qua trinh nhap vat tu.", YES, lcDisplay);
		}
	}

	bd_Confirm(bd, lm, type);
}