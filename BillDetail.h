#pragma once

#include "Material.h"
#include "Bill.h"

struct BILLDETAILS
{
	char materialsCode[material_maxSize_Code];
	int quantity;
	double unitPrice;
	int percentVAT;
};

struct NODE_BILLDETAILS
{
	BILLDETAILS data;
	struct NODE_BILLDETAILS *pNext;
};
typedef struct NODE_BILLDETAILS* NBD;


void dslk_InitBD(NBD &bd);
NBD dslk_CreateNodeBD(BILLDETAILS data);
void dslk_addHeadBD(NBD &nb, NBD itemAdd);
bool dslk_removeNodeBD(NBD &nb, NBD itemDelete);
int dslk_Count(NODE_BILLDETAILS* bd);

void bd_Show(NBD bd, LIST_MATERIAL lm, LOCATION lcDisplay, int &bottom, int modeView);
void bd_Add(NBD &bd, LIST_MATERIAL &lm, char type);
void bd_Confirm(NBD &bd, LIST_MATERIAL &lm, char type);
