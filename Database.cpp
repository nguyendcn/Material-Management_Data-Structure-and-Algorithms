#include "Database.h"

void database_SaveBill(LIST_BILL lb)
{
	/*fstream FileOut("Data\\BILL.TXT", ios::out | ios::binary);

	int sizeBill = sizeof(BILL) - sizeof(NODE_BILLDETAILS*);
	int quantityBill = dslk_Count(lb.pHead);
	FileOut << quantityBill;
	NODE_BILL *nb = lb.pHead;
	while (nb != NULL)
	{
		FileOut.write(reinterpret_cast<const char*>(nb), sizeBill);
		int quantityBD = dslk_Count(lb.pHead->data.list_BillDetail);
		FileOut << quantityBD;
		NODE_BILLDETAILS *bd = nb->data.list_BillDetail;
		while (bd != NULL)
		{
			FileOut.write(reinterpret_cast<const char *>(bd), sizeof(BILLDETAILS));
			bd = bd->pNext;
		}
		nb = nb->pNext;
	}

	FileOut.close();*/
}

bool database_LoadBill(LIST_BILL &lb, LIST_EMPLOYEES le)
{
	/*fstream FileIn("Data\\BILL.TXT", ios::in | ios::binary);

	if (FileIn.fail())
	{
		return false;
	}

	int sizeBill = sizeof(BILL) - sizeof(NODE_BILLDETAILS*);
	int quantityBill = 0;
	FileIn >> quantityBill;
	for (int runB = 0; runB < quantityBill; runB++)
	{
		NODE_BILL* nb = new NODE_BILL;
		FileIn.read(reinterpret_cast<char*>(nb), sizeBill);
		nb->data.list_BillDetail = NULL;
		nb->pNext = NULL;

		int quantityBD = 0;
		FileIn >> quantityBD;

		for (int runbd = 0; runbd < quantityBD; runbd++)
		{
			NODE_BILLDETAILS *bd = new NODE_BILLDETAILS;
			bd->pNext = NULL;
			FileIn.read(reinterpret_cast<char*>(bd), sizeof(BILLDETAILS));
			dslk_addHeadBD(nb->data.list_BillDetail, bd);
		}
		dslk_addTail(lb, nb);
	}

	FileIn.close();
	return true;*/

	for (int i = 0; i < le.size; i++)
	{
		for (NODE_BILL *p = le.arr[i].list_Bill; p != NULL; p = p->pNext)
		{
			dslk_addTail(lb, p);
			bill_SortUpByCode(lb);
		}
	}
	return true;
}

void database_SaveEmployees(LIST_EMPLOYEES le)
{
	fstream FileOut("Data\\EMPLOYEES.TXT", ios::out | ios::binary);
	int sizeEmploy = sizeof(EMPLOYEES) - sizeof(NODE_BILL*);
	int sizeBill = sizeof(BILL) - sizeof(NODE_BILLDETAILS*);

	FileOut << le.size;
	for (int run = 0; run < le.size; run++)
	{
		FileOut.write(reinterpret_cast<const char*>(&le.arr[run]), sizeEmploy);
		FileOut << dslk_Count(le.arr[run].list_Bill);
		NODE_BILL *nb = le.arr[run].list_Bill;
		while (nb != NULL)
		{
			FileOut.write(reinterpret_cast<const char*>(nb), sizeBill);
			NODE_BILLDETAILS *bd = nb->data.list_BillDetail;
			FileOut << dslk_Count(nb->data.list_BillDetail);
			while (bd != NULL)
			{
				FileOut.write(reinterpret_cast<const char *>(bd), sizeof(BILLDETAILS));
				bd = bd->pNext;
			}
			nb = nb->pNext;
		}
	}

	FileOut.close();
}

bool database_LoadEmployees(LIST_EMPLOYEES &le)
{
	fstream FileIn("Data\\EMPLOYEES.TXT", ios::in | ios::binary);

	if (FileIn.fail())
	{
		return false;
	}

	int sizeEmploy = sizeof(EMPLOYEES) - sizeof(NODE_BILL*);
	int sizeBill = sizeof(BILL) - sizeof(NODE_BILLDETAILS*);
	int quantityEmp = 0;
	FileIn >> quantityEmp;
	for (int runemp = 0; runemp < quantityEmp; runemp++)
	{
		employees_insertItem(le, le.size, EMPLOYEES());
		FileIn.read(reinterpret_cast<char*>(&le.arr[le.size - 1]), sizeEmploy);
		int quantityBill = 0;
		FileIn >> quantityBill;

		le.arr[le.size - 1].list_Bill = NULL;
		for (int run = 0; run < quantityBill; run++)
		{
			NODE_BILL* nb = new NODE_BILL;
			FileIn.read(reinterpret_cast<char*>(nb), sizeBill);
			nb->data.list_BillDetail = NULL;
			nb->pNext = NULL;

			int quantityBD = 0;
			FileIn >> quantityBD;

			for (int runbd = 0; runbd < quantityBD; runbd++)
			{
				NODE_BILLDETAILS *bd = new NODE_BILLDETAILS;
				bd->pNext = NULL;
				FileIn.read(reinterpret_cast<char*>(bd), sizeof(BILLDETAILS));
				dslk_addHeadBD(nb->data.list_BillDetail, bd);
			}

			employees_InsertListBill(le, le.arr[le.size - 1].employeesCode, nb);
		}

	}

	FileIn.close();

	employees_Sort(le);

	return true;
}

void material_WriteToFile(nodeTree* p, fstream &file, int size)
{
	if (p != NULL)
	{
		file.write(reinterpret_cast<const char*>(&p->data), size);
		material_WriteToFile(p->pLeft, file, size);
		material_WriteToFile(p->pRight, file, size);
	}
}

void database_SaveMaterial(LIST_MATERIAL lm)
{
	fstream FileOut("Data\\MATERIAL.TXT", ios::out | ios::binary);

	int material_quantityNow = materials_Count(lm);

	FileOut << material_quantityNow;
	int sizeData = sizeof(MATERIAL);
	LIST_MATERIAL temp = lm;
	material_WriteToFile(temp, FileOut, sizeData);

	FileOut.close();
}

bool database_LoadMaterial(LIST_MATERIAL &t)
{
	fstream FileIn("Data\\MATERIAL.TXT", ios::in | ios::binary);

	if (FileIn.fail())
	{
		return false;
	}

	int quantity = 0;
	int sizeData = sizeof(MATERIAL);

	FileIn >> quantity;

	MATERIAL item;
	for (int i = 0; i <= quantity; i++)
	{
		FileIn.read(reinterpret_cast<char*>(&item), sizeData);
		avl_insert(t, item);
	}
	return true;
}

void database_LoadData(LIST_MATERIAL &lm, LIST_EMPLOYEES &le, LIST_BILL &lb)
{
	if (messagebox("Ban co muon tai du lieu len khong?", YES_NO, LOCATION()))
	{
		bool loadM, loadE, loadB;
		loadM = database_LoadMaterial(lm);
		loadE = database_LoadEmployees(le);
		loadB = database_LoadBill(lb, le);
		system("cls");
		if (!loadM)
		{
			messagebox("ERROR: can't load file MATERIAL.TXT", YES, LOCATION());
		}
		else if (!loadE)
		{
			messagebox("ERROR: can't load file EMPLOYEES.TXT", YES, LOCATION());
		}
		else if (!loadB)
		{
			messagebox("ERROR: can't load file BILL.TXT", YES, LOCATION());
		}
		else if (!loadM && !loadE)
		{
			messagebox("ERROR: can't load file MATERIAL.TXT && EMPLOYEES.TXT", YES, LOCATION());
		}
		else if (!loadM && !loadB)
		{
			messagebox("ERROR: can't load file MATERIAL.TXT && BILL.TXT", YES, LOCATION());
		}
		else if (!loadE && !loadB)
		{
			messagebox("ERROR: can't load file EMPLOYEES.TXT && BILL.TXT", YES, LOCATION());
		}
		else if (!loadM && !loadE && !loadB)
		{
			messagebox("ERROR: can't load file MATERIAL.TXT && EMPLOYEES.TXT && BILL.TXT", YES, LOCATION());
		}
		else
		{
			messagebox("Da tai du lieu len thanh cong!", YES, LOCATION());
		}
	}
}