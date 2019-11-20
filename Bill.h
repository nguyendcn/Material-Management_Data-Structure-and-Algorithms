#pragma once

#include<time.h>

#include "BillDetail.h"
#include "Employees.h"


struct BILL
{
	char billNumber[bill_maxSize_Code + 1];
	char employeesCode[employees_maxSize_Code + 1];
	char invoiceDate[bill_maxSize_invoiceDate + 1];
	char type;
	struct NODE_BILLDETAILS *list_BillDetail = NULL;
};

struct NODE_BILL
{
	BILL data;
	struct NODE_BILL *pNext;
};

struct LIST_BILL
{
	NODE_BILL *pHead;
	NODE_BILL *pTail;
};


void dslk_Initialize(LIST_BILL &lb);
NODE_BILL* dslk_CreateNodeBill(BILL data);
void dslk_addTail(LIST_BILL &lb, NODE_BILL *itemAdd);
void dslk_addHead(NODE_BILL* &lb, NODE_BILL *itemAdd);
int dslk_Count(struct NODE_BILL* lb);
void bill_SortUpByCode(LIST_BILL &lb);
void bill_buildBill(LIST_BILL &lb, struct LIST_EMPLOYEES &le, LIST_MATERIAL &lm);
STR dis_chooseViewDetail(LIST_BILL lb, struct NODE_BILLDETAILS* nb, LIST_EMPLOYEES le,LOCATION lcDis, int widthGird, LIST_ARRAY_CHAR notify, int modeMore);
void bill_Show(LIST_BILL lb, LIST_MATERIAL lm, LOCATION lcShow);
void bill_ShowByDate(LIST_BILL lb, LIST_EMPLOYEES le, LIST_MATERIAL lm);
void bill_EntryDate(LIST_ARRAY_CHAR &data);
void material_showHeightRevenue(LIST_BILL lb, LIST_MATERIAL lm);