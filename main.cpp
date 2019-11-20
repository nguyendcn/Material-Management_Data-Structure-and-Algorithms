#include "Menu.h"
#include <Windows.h>



int main()
{
	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	//::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	HWND consoleWindow = GetConsoleWindow();
	system("mode 650");
	SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);


	/*LIST_BILL lb;

	dslk_Initialize(lb);

	BILL b;
	strcpy_s(b.employeesCode, "ACX");

	dslk_addTail(lb, dslk_CreateNodeBill(b));


	strcpy_s(b.employeesCode, "ZXCV");

	dslk_addTail(lb, dslk_CreateNodeBill(b));


	strcpy_s(b.employeesCode, "SDFFF");

	dslk_addTail(lb, dslk_CreateNodeBill(b));


	strcpy_s(b.employeesCode, "SSFG");

	dslk_addTail(lb, dslk_CreateNodeBill(b));

	strcpy_s(b.employeesCode, "RYUH");

	dslk_addTail(lb, dslk_CreateNodeBill(b));

	strcpy_s(b.employeesCode, "GFDDFFD");

	dslk_addTail(lb, dslk_CreateNodeBill(b));

	for (NODE_BILL *p = lb.pHead; p != NULL; p = p->pNext)
	{
	cout << p->data.employeesCode << endl;
	}*/
	/*
	//LIST_MATERIAL lm;

	//treeInitialize(lm);

	//MATERIAL m;
	//strcpy_s(m.materialsCode, "N16");
	//strcpy_s(m.materialsName, "asxsdq");
	//strcpy_s(m.countUnit, "ddd");
	//m.inventoryNumber = 100;

	//avl_insert(lm, m);

	//strcpy_s(m.materialsCode, "N12");
	//strcpy_s(m.materialsName, "dfasdfasdf");
	//strcpy_s(m.countUnit, "ddd");
	//m.inventoryNumber = 100;

	//avl_insert(lm, m);

	//strcpy_s(m.materialsCode, "N18");
	//strcpy_s(m.materialsName, "weqrqwer");
	//strcpy_s(m.countUnit, "ddd");
	//m.inventoryNumber = 100;

	//avl_insert(lm, m);

	//strcpy_s(m.materialsCode, "N19");
	//strcpy_s(m.materialsName, "yjtyjyt");
	//strcpy_s(m.countUnit, "ddd");
	//m.inventoryNumber = 100;

	//avl_insert(lm, m);

	//strcpy_s(m.materialsCode, "N15");
	//strcpy_s(m.materialsName, "dfsadsf2");
	//strcpy_s(m.countUnit, "ddd");
	//m.inventoryNumber = 100;

	//avl_insert(lm, m);

	//strcpy_s(m.materialsCode, "N14");
	//strcpy_s(m.materialsName, "asdfvd");
	//strcpy_s(m.countUnit, "ddd");
	//m.inventoryNumber = 100;

	//avl_insert(lm, m);

	//strcpy_s(m.materialsCode, "N11");
	//
	//strcpy_s(m.materialsName, "ASDFSDFSD");
	//strcpy_s(m.countUnit, "ddd");
	//m.inventoryNumber = 100;

	//avl_insert(lm, m);

	//LOCATION lc = {5, 5};

	//
	//LIST_EMPLOYEES le;
	//EMPLOYEES e;
	//strcpy_s(e.employeesCode, "D16CQCN02");
	//strcpy_s(e.familyName, "Dang Cao");
	//strcpy_s(e.firstName, "Nguyen");
	//e.sex = 1;
	//
	//NODE_BILLDETAILS *bd;
	//bd = new NODE_BILLDETAILS;
	//bd->data = {"N16", 100, 100, 10};
	//bd->pNext = NULL;

	//NODE_BILL *nb;
	//nb = new NODE_BILL;
	////nb->data = {"CB01", "D16CQCN02", "2018", 'n'};
	//strcpy_s(nb->data.billNumber, "CB01");
	//strcpy_s(nb->data.employeesCode, "D16CQCN02");
	//strcpy_s(nb->data.invoiceDate, "2018");
	//nb->data.type = 'n';
	//nb->data.list_BillDetail = bd;
	//nb->pNext = NULL;
	//
	//e.list_Bill = nb;

	//employees_insertItem(le, le.size, e);



	///*LIST_MATERIAL l;
	//treeInitialize(l);
	//material_Load(l);
	//employees_Save(le);*/

	system("cls");
	menu_Show();

	/*for (NODE_BILL *p = lb.pHead; p != NULL; p = p->pNext)
	{
	cout << "\n-------------------------------------\n" << endl;
	cout << "Ma hoa don: " << p->data.billNumber << endl;
	cout << "Ma nhan vien: " << p->data.employeesCode << endl;
	cout << "Ngay lap hoa don: " << p->data.invoiceDate << endl;
	cout << "Loai hoa don: " << p->data.type << endl;
	cout << "==============Chi tiet====================" << endl;
	for (NBD z = p->data.list_BillDetail; z != NULL; z = z->pNext)
	{
	cout << "Ma vat tu: " << z->data.materialsCode << endl;
	cout << "So luong : " << z->data.quantity << endl;
	cout << "Don gia: " << z->data.unitPrice << endl;
	cout << "VAT: " << z->data.percentVAT << endl;
	}
	}*/


	system("pause");
	return 0;
}