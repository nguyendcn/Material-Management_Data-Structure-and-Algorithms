#include "Menu.h"

void drawText(LOCATION lcDisplay)
{
	fstream FileIn("Intro.TXT", ios::in);

	if (FileIn.fail())
	{
		cout << "ERROR file Text.";
		Sleep(5000);
		exit(0);
	}
	else
	{
		int line = 1;
		while (!FileIn.eof())
		{
			gotoxy(lcDisplay.x, lcDisplay.y + line++);
			string text;
			getline(FileIn, text);
			if (text == "**")
				break;
			else
				std::cout << text << endl;
		}
	}

	FileIn.close();
}

void dropDown(LOCATION lcBtnHead, int index, int &dir, LIST_MATERIAL &lm, LIST_EMPLOYEES &le, LIST_BILL &lb)
{
	LOCATION lcGird = { 2, 2 };
	if (index == 0) // material
	{
		int space = 0;
		Size sBtnShowList, sBtnAdd, sBtnDel, sBtnEdit, sClear;
		LOCATION lBtnShowList, lBtnAdd, lBtnDel, lBtnEdit, lClear;

		sBtnShowList = sBtnAdd = sBtnDel = sBtnEdit = { 15, 5 };
		lBtnShowList = { lcBtnHead.x, lcBtnHead.y + 5 + space };
		lBtnAdd = { lcBtnHead.x, lBtnShowList.y + sBtnShowList.height + space };
		lBtnDel = { lcBtnHead.x, lBtnAdd.y + sBtnAdd.height + space };
		lBtnEdit = { lcBtnHead.x, lBtnDel.y + sBtnDel.height + space };
		lClear = lBtnShowList;
		sClear = { sBtnShowList.width, (lBtnEdit.y + sBtnEdit.height) - lBtnShowList.y };

		button(true, "Xem Vat Tu", lBtnShowList, sBtnShowList, ColorCode_Blue, ColorCode_Black);
		button(false, "Them", lBtnAdd, sBtnAdd, ColorCode_Blue, ColorCode_Black);
		button(false, "Xoa", lBtnDel, sBtnDel, ColorCode_Blue, ColorCode_Black);
		button(false, "Sua", lBtnEdit, sBtnDel, ColorCode_Blue, ColorCode_Black);

		int maxBTN = 4;
		int index = 0;
		bool isControl = false;
		while (true)
		{
			if (_kbhit())
			{
				char key = _getch();

				if (key == -32)
				{
					isControl = true;
				}
				else if (isControl)
				{
					if (key == dir_LEFT)
					{
						//del list
						dis_Clear(lClear, sClear);
						dir = dir_LEFT;
						break;
					}
					else if (key == dir_RIGHT)
					{
						//del list
						dis_Clear(lClear, sClear);
						dir = dir_RIGHT;
						break;
					}
					else if (key == dir_DOWN)
					{
						index++;
						if (index >= maxBTN)
						{
							index = 0;
							button(false, "Sua", lBtnEdit, sBtnDel, ColorCode_Blue, ColorCode_Black);
							button(true, "Xem Vat Tu", lBtnShowList, sBtnShowList, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 1)
						{
							button(false, "Xem Vat Tu", lBtnShowList, sBtnShowList, ColorCode_Blue, ColorCode_Black);
							button(true, "Them", lBtnAdd, sBtnAdd, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 2)
						{
							button(false, "Them", lBtnAdd, sBtnAdd, ColorCode_Blue, ColorCode_Black);
							button(true, "Xoa", lBtnDel, sBtnDel, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 3)
						{
							button(false, "Xoa", lBtnDel, sBtnDel, ColorCode_Blue, ColorCode_Black);
							button(true, "Sua", lBtnEdit, sBtnDel, ColorCode_Blue, ColorCode_Black);
						}
					}
					else if (key == dir_UP)
					{
						index--;
						if (index < 0)
						{
							index = maxBTN - 1;
							button(false, "Xem Vat Tu", lBtnShowList, sBtnShowList, ColorCode_Blue, ColorCode_Black);
							button(true, "Sua", lBtnEdit, sBtnDel, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 2)
						{
							button(true, "Xoa", lBtnDel, sBtnDel, ColorCode_Blue, ColorCode_Black);
							button(false, "Sua", lBtnEdit, sBtnDel, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 1)
						{
							button(true, "Them", lBtnAdd, sBtnAdd, ColorCode_Blue, ColorCode_Black);
							button(false, "Xoa", lBtnDel, sBtnDel, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 0)
						{
							button(true, "Xem Vat Tu", lBtnShowList, sBtnShowList, ColorCode_Blue, ColorCode_Black);
							button(false, "Them", lBtnAdd, sBtnAdd, ColorCode_Blue, ColorCode_Black);
						}
					}

					isControl = false;
				}
				else
				{
					if (key == key_ESC)
					{
						//out
						dir = key_ESC;
						break;
					}
					else if (key == key_ENTER)
					{
						if (index == 0) // view
						{
							system("cls");
							material_Show(lm, lcGird, 0);

							dir = key_SPACE;
							break;
						}
						else if (index == 1) // add
						{
							system("cls");
							materials_Add(lm);

							dir = key_SPACE;
							break;
						}
						else if (index == 2) // remove
						{
							system("cls");
							materials_Remove(lm);

							dir = key_SPACE;
							break;
						}
						else if (index == 3) // edit
						{
							system("cls");
							materials_Edit(lm);

							dir = key_SPACE;
							break;
						}
					}
				}
			}
		}
	}
	else if (index == 1) // employees
	{
		Size sBtnEdit, sBtnView, sClear;
		LOCATION lBtnEdit, lBtnView, lClear;
		int space = 0;

		sBtnEdit = sBtnView = { 15, 5 };
		lBtnEdit = { lcBtnHead.x, lcBtnHead.y + 5 + space };
		lBtnView = { lcBtnHead.x, lBtnEdit.y + sBtnEdit.height + space };
		lClear = { lcBtnHead.x, lcBtnHead.y + 5 };
		sClear = { sBtnView.width, (lBtnView.y + sBtnView.height) - lClear.y };


		button(true, "Sua", lBtnEdit, sBtnEdit, ColorCode_Blue, ColorCode_Black);
		button(false, "Xem", lBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);

		int maxBTN = 2;
		int index = 0;
		bool isControl = false;
		while (true)
		{
			if (_kbhit())
			{
				char key = _getch();

				if (key == -32)
				{
					isControl = true;
				}
				else if (isControl)
				{
					if (key == dir_LEFT)
					{
						//del list
						dis_Clear(lClear, sClear);
						dir = dir_LEFT;
						break;
					}
					else if (key == dir_RIGHT)
					{
						//del list
						dis_Clear(lClear, sClear);
						dir = dir_RIGHT;
						break;
					}
					else if (key == dir_DOWN)
					{
						index++;
						if (index >= maxBTN)
						{
							index = 0;
							button(false, "Xem", lBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
							button(true, "Sua", lBtnEdit, sBtnEdit, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 1)
						{
							button(true, "Xem", lBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
							button(false, "Sua", lBtnEdit, sBtnEdit, ColorCode_Blue, ColorCode_Black);
						}
					}
					else if (key == dir_UP)
					{
						index--;
						if (index < 0)
						{
							index = maxBTN - 1;
							button(false, "Sua", lBtnEdit, sBtnEdit, ColorCode_Blue, ColorCode_Black);
							button(true, "Xem", lBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 0)
						{
							button(true, "Sua", lBtnEdit, sBtnEdit, ColorCode_Blue, ColorCode_Black);
							button(false, "Xem", lBtnView, sBtnView, ColorCode_Blue, ColorCode_Black);
						}
					}
					isControl = false;
				}
				else
				{
					if (key == key_ESC)
					{
						//out
						dir = key_ESC;
						break;
					}
					else if (key == key_ENTER)
					{
						if (index == 0) //edit
						{
							system("cls");
							employees_Edit(le, lcGird);

							dir = key_SPACE;
							break;
						}
						else if (index == 1) // view
						{
							system("cls");
							employees_Show(le, lm, lcGird);

							dir = key_SPACE;
							break;
						}
					}
				}
			}
		}
	}
	else if (index == 2) // bill
	{
		Size sCreate, sShow, sShowByDay, sClear, sTenDay;
		LOCATION lCreate, lShow, lShowByDay, lClear, lTenDay;
		int space = 0;

		sCreate = sShow = sShowByDay = sTenDay = { 15, 5 };
		lCreate = { lcBtnHead.x, lcBtnHead.y + 5 + space };
		lShow = { lCreate.x, lCreate.y + sCreate.height + space };
		lShowByDay = { lShow.x, lShow.y + sShow.height + space };
		lTenDay = { lShowByDay.x, lShowByDay.y + sShowByDay.height + space };

		lClear = { lCreate.x, lCreate.y };
		sClear = { sCreate.width, (lTenDay.y + sTenDay.height) - lClear.y };

		button(true, "Tao Hoa Don", lCreate, sCreate, ColorCode_Blue, ColorCode_Black);
		button(false, "Xem", lShow, sShow, ColorCode_Blue, ColorCode_Black);
		button(false, "Xem Theo Ngay", lShowByDay, sShowByDay, ColorCode_Blue, ColorCode_Black);
		button(false, "10 Ngay", lTenDay, sTenDay, ColorCode_Blue, ColorCode_Black);

		int maxBTN = 4;
		int index = 0;
		bool isControl = false;
		while (true)
		{
			if (_kbhit())
			{
				char key = _getch();

				if (key == -32)
				{
					isControl = true;
				}
				else if (isControl)
				{
					if (key == dir_LEFT)
					{
						//del list
						dis_Clear(lClear, sClear);
						dir = dir_LEFT;
						break;
					}
					else if (key == dir_RIGHT)
					{
						//del list
						dis_Clear(lClear, sClear);
						dir = dir_RIGHT;
						break;
					}
					else if (key == dir_DOWN)
					{
						index++;
						if (index >= maxBTN)
						{
							index = 0;
							button(true, "Tao Hoa Don", lCreate, sCreate, ColorCode_Blue, ColorCode_Black);
							button(false, "10 Ngay", lTenDay, sTenDay, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 1)
						{
							button(false, "Tao Hoa Don", lCreate, sCreate, ColorCode_Blue, ColorCode_Black);
							button(true, "Xem", lShow, sShow, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 2)
						{
							button(false, "Xem", lShow, sShow, ColorCode_Blue, ColorCode_Black);
							button(true, "Xem Theo Ngay", lShowByDay, sShowByDay, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 3)
						{
							button(false, "Xem Theo Ngay", lShowByDay, sShowByDay, ColorCode_Blue, ColorCode_Black);
							button(true, "10 Ngay", lTenDay, sTenDay, ColorCode_Blue, ColorCode_Black);
						}
					}
					else if (key == dir_UP)
					{
						index--;
						if (index < 0)
						{
							index = maxBTN - 1;
							button(false, "Tao Hoa Don", lCreate, sCreate, ColorCode_Blue, ColorCode_Black);
							button(true, "10 Ngay", lTenDay, sTenDay, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 2)
						{
							button(false, "10 Ngay", lTenDay, sTenDay, ColorCode_Blue, ColorCode_Black);
							button(true, "Xem Theo Ngay", lShowByDay, sShowByDay, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 1)
						{
							button(true, "Xem", lShow, sShow, ColorCode_Blue, ColorCode_Black);
							button(false, "Xem Theo Ngay", lShowByDay, sShowByDay, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 0)
						{
							button(true, "Tao Hoa Don", lCreate, sCreate, ColorCode_Blue, ColorCode_Black);
							button(false, "Xem", lShow, sShow, ColorCode_Blue, ColorCode_Black);
						}
					}
					isControl = false;
				}
				else
				{
					if (key == key_ESC)
					{
						//out
						dir = key_ESC;
						break;
					}
					else if (key == key_ENTER)
					{
						if (index == 0) // create
						{
							system("cls");
							bill_buildBill(lb, le, lm);

							dir = key_SPACE;
							break;
						}
						else if (index == 1) // show
						{
							system("cls");
							bill_Show(lb, lm, lcGird);

							dir = key_SPACE;
							break;
						}
						else if (index == 2) // show by day
						{
							system("cls");
							bill_ShowByDate(lb, le, lm);

							dir = key_SPACE;
							break;
						}
						else if (index == 3) // ten day
						{
							system("cls");
							material_showHeightRevenue(lb, lm);

							dir = key_SPACE;
							break;
						}
					}
				}
			}
		}

	}
	else if (index == 3)//data
	{
		Size sBtnSave, sBtnLoad, sClear;
		LOCATION lBtnSave, lBtnLoad, lClear;
		int space = 0;

		sBtnSave = sBtnLoad = { 15, 5 };
		lBtnSave = { lcBtnHead.x, lcBtnHead.y + 5 + space };
		lBtnLoad = { lcBtnHead.x, lBtnSave.y + sBtnSave.height + space };
		lClear = lBtnSave;
		sClear = { sBtnSave.width, (lBtnLoad.y + sBtnLoad.height) - lClear.y };

		button(true, "Save", lBtnSave, sBtnSave, ColorCode_Blue, ColorCode_Black);
		button(false, "Load", lBtnLoad, sBtnLoad, ColorCode_Blue, ColorCode_Black);

		int maxBTN = 2;
		int index = 0;
		bool isControl = false;
		while (true)
		{
			if (_kbhit())
			{
				char key = _getch();

				if (key == -32)
				{
					isControl = true;
				}
				else if (isControl)
				{
					if (key == dir_LEFT)
					{
						//del list
						dis_Clear(lClear, sClear);
						dir = dir_LEFT;
						break;
					}
					else if (key == dir_RIGHT)
					{
						//del list
						dis_Clear(lClear, sClear);
						dir = dir_RIGHT;
						break;
					}
					else if (key == dir_DOWN)
					{
						index++;
						if (index >= maxBTN)
						{
							index = 0;
							button(true, "Save", lBtnSave, sBtnSave, ColorCode_Blue, ColorCode_Black);
							button(false, "Load", lBtnLoad, sBtnLoad, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 1)
						{
							button(false, "Save", lBtnSave, sBtnSave, ColorCode_Blue, ColorCode_Black);
							button(true, "Load", lBtnLoad, sBtnLoad, ColorCode_Blue, ColorCode_Black);
						}
					}
					else if (key == dir_UP)
					{
						index--;
						if (index < 0)
						{
							index = maxBTN - 1;
							button(false, "Save", lBtnSave, sBtnSave, ColorCode_Blue, ColorCode_Black);
							button(true, "Load", lBtnLoad, sBtnLoad, ColorCode_Blue, ColorCode_Black);
						}
						else if (index == 0)
						{
							button(true, "Save", lBtnSave, sBtnSave, ColorCode_Blue, ColorCode_Black);
							button(false, "Load", lBtnLoad, sBtnLoad, ColorCode_Blue, ColorCode_Black);
						}
					}
					isControl = false;
				}
				else
				{
					if (key == key_ESC)
					{
						//out
						dir = key_ESC;
						break;
					}
					else if (key == key_ENTER)
					{
						if (index == 0)//save
						{
							system("cls");
							if (messagebox("Ban co muon luu du lieu khong?", YES_NO, LOCATION()))
							{
								database_SaveMaterial(lm);
								database_SaveEmployees(le);
								database_SaveBill(lb);
								system("cls");
								messagebox("Da luu du lieu thanh cong.", YES, LOCATION());
							}

							dir = key_SPACE; 
							break;
						}
						else if (index == 1) // load
						{
							system("cls");
							
							database_LoadData(lm, le, lb);

							dir = key_SPACE;
							break;
						}
					}
				}
			}
		}
	}
}

bool menu_Select(LOCATION lcDisplay, LIST_MATERIAL &lm, LIST_EMPLOYEES &le, LIST_BILL &lb)
{
	Size sBtnEmployees, sBtnMaterial, sBtnBill, sBtnData, sGird;
	LOCATION lBtnEmployees, lBtnMaterial, lBtnBill, lBtnData;
	int space = 5;

	sBtnEmployees = sBtnMaterial = sBtnBill = sBtnData = { 15, 5 };
	sGird = { sBtnEmployees.width * 3 + space * 2, 40 };
	lBtnMaterial = { lcDisplay.x + 3, lcDisplay.y + 8 };
	lBtnEmployees = { lBtnMaterial.x + sBtnMaterial.width + space, lBtnMaterial.y };
	lBtnBill = { lBtnEmployees.x + sBtnEmployees.width + space, lBtnMaterial.y };
	lBtnData = { lBtnBill.x + sBtnBill.width + space, lBtnMaterial.y };

	button(true, "Vat Tu", lBtnMaterial, sBtnMaterial, ColorCode_Blue, ColorCode_Black);
	button(false, "Nhan Vien", lBtnEmployees, sBtnEmployees, ColorCode_Blue, ColorCode_Black);
	button(false, "Hoa Don", lBtnBill, sBtnBill, ColorCode_Blue, ColorCode_Black);
	button(false, "Du Lieu", lBtnData, sBtnData, ColorCode_Blue, ColorCode_Black);

	int maxBTN = 4;
	int index = 0;
	int key = 0;
	dropDown(lBtnMaterial, index, key, lm, le, lb);
	while (true)
	{
		if (key == dir_LEFT)
		{
			index--;
			if (index < 0)
			{
				index = maxBTN - 1;
			}
			//show
			if (index == 0)
			{
				button(true, "Vat Tu", lBtnMaterial, sBtnMaterial, ColorCode_Blue, ColorCode_Black);
				button(false, "Nhan Vien", lBtnEmployees, sBtnEmployees, ColorCode_Blue, ColorCode_Black);
				dropDown(lBtnMaterial, index, key, lm, le, lb);
			}
			else if (index == 1)
			{
				button(true, "Nhan Vien", lBtnEmployees, sBtnEmployees, ColorCode_Blue, ColorCode_Black);
				button(false, "Hoa Don", lBtnBill, sBtnBill, ColorCode_Blue, ColorCode_Black);
				dropDown(lBtnEmployees, index, key, lm, le, lb);
			}
			else if (index == 2)
			{
				button(true, "Hoa Don", lBtnBill, sBtnBill, ColorCode_Blue, ColorCode_Black);
				button(false, "Du Lieu", lBtnData, sBtnData, ColorCode_Blue, ColorCode_Black);
				dropDown(lBtnBill, index, key, lm, le, lb);
			}
			else if (index == 3)
			{
				button(false, "Vat Tu", lBtnMaterial, sBtnMaterial, ColorCode_Blue, ColorCode_Black);
				button(true, "Du Lieu", lBtnData, sBtnData, ColorCode_Blue, ColorCode_Black);
				dropDown(lBtnData, index, key, lm, le, lb);
			}
		}
		else if (key == dir_RIGHT)
		{
			index++;
			if (index >= maxBTN)
			{
				index = 0;
			}
			//show;
			if (index == 0)
			{
				button(true, "Vat Tu", lBtnMaterial, sBtnMaterial, ColorCode_Blue, ColorCode_Black);
				button(false, "Du Lieu", lBtnData, sBtnData, ColorCode_Blue, ColorCode_Black);
				dropDown(lBtnMaterial, index, key, lm, le, lb);
			}
			else if (index == 1)
			{
				button(false, "Vat Tu", lBtnMaterial, sBtnMaterial, ColorCode_Blue, ColorCode_Black);
				button(true, "Nhan Vien", lBtnEmployees, sBtnEmployees, ColorCode_Blue, ColorCode_Black);
				dropDown(lBtnEmployees, index, key, lm, le, lb);
			}
			else if (index == 2)
			{
				button(false, "Nhan Vien", lBtnEmployees, sBtnEmployees, ColorCode_Blue, ColorCode_Black);
				button(true, "Hoa Don", lBtnBill, sBtnBill, ColorCode_Blue, ColorCode_Black);
				dropDown(lBtnBill, index, key, lm, le, lb);
			}
			else if (index == 3)
			{
				button(false, "Hoa Don", lBtnBill, sBtnBill, ColorCode_Blue, ColorCode_Black);
				button(true, "Du Lieu", lBtnData, sBtnData, ColorCode_Blue, ColorCode_Black);
				dropDown(lBtnData, index, key, lm, le, lb);
			}
		}
		else if (key == key_ESC) // exit
		{
			return false;
		}
		else if (key == key_SPACE) // continue
		{
			return true;
		}
	}
}

void menu_Show()
{
	LIST_MATERIAL lm; treeInitialize(lm);
	LIST_EMPLOYEES le;
	LIST_BILL lb; dslk_Initialize(lb);

	Size sGird;
	LOCATION lGird, lShowText, lShowSelect;

		/*EMPLOYEES e;
		strcpy_s(e.employeesCode, "NV001");
		strcpy_s(e.familyName, "Pham Nguyen");
		strcpy_s(e.firstName, "Hoang");
		e.sex = 0;
		e.list_Bill = NULL;
		employees_insertItem(le, le.size, e);

		strcpy_s(e.employeesCode, "NV002");
		strcpy_s(e.familyName, "Ho Thi");
		strcpy_s(e.firstName, "Hien");
		e.sex = 1;
		e.list_Bill = NULL;
		employees_insertItem(le, le.size, e);

		strcpy_s(e.employeesCode, "NV003");
		strcpy_s(e.familyName, "Nguyen Thi");
		strcpy_s(e.firstName, "Diu");
		e.sex = 1;
		e.list_Bill = NULL;
		employees_insertItem(le, le.size, e);

		strcpy_s(e.employeesCode, "NV004");
		strcpy_s(e.familyName, "Vu Thi");
		strcpy_s(e.firstName, "Huong");
		e.sex = 1;
		e.list_Bill = NULL;
		employees_insertItem(le, le.size, e);

		strcpy_s(e.employeesCode, "NV005");
		strcpy_s(e.familyName, "Tran Van");
		strcpy_s(e.firstName, "Phuoc");
		e.sex = 0;
		e.list_Bill = NULL;
		employees_insertItem(le, le.size, e);

		strcpy_s(e.employeesCode, "NV006");
		strcpy_s(e.familyName, "Tran Dinh");
		strcpy_s(e.firstName, "Loc");
		e.sex = 1;
		e.list_Bill = NULL;
		employees_insertItem(le, le.size, e);

		strcpy_s(e.employeesCode, "NV007");
		strcpy_s(e.familyName, "Tran Thi");
		strcpy_s(e.firstName, "Phuong");
		e.sex = 1;
		e.list_Bill = NULL;
		employees_insertItem(le, le.size, e);

		strcpy_s(e.employeesCode, "NV008");
		strcpy_s(e.familyName, "Nguyen Dai");
		strcpy_s(e.firstName, "Vu");
		e.sex = 0;
		e.list_Bill = NULL;
		employees_insertItem(le, le.size, e);

		strcpy_s(e.employeesCode, "NV009");
		strcpy_s(e.familyName, "Nguyen Thi");
		strcpy_s(e.firstName, "Nga");
		e.sex = 1;
		e.list_Bill = NULL;
		employees_insertItem(le, le.size, e);

		strcpy_s(e.employeesCode, "NV010");
		strcpy_s(e.familyName, "Nguyen Thi");
		strcpy_s(e.firstName, "Lan");
		e.sex = 1;
		e.list_Bill = NULL;
		employees_insertItem(le, le.size, e);*/
	

	lGird = { 20, 2 };

	lShowText = { lGird.x + 13, lGird.y + 1 };
	lShowSelect = { lGird.x + 12, lGird.y + 7 };
	sGird = { 110, 42 };
	while (true)
	{
		system("cls");
		drawBox(lGird, sGird, "");

		drawText(lShowText);
		if (menu_Select(lShowSelect, lm, le, lb) == false) // out
		{
			break;
		}
	}
}