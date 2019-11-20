#pragma once
#include <iostream>

#include "Constant.h"
#include "LIST.h"
#include "Display.h"

enum bf { LH = -1, EH = 0, RH = 1 };

struct MATERIAL
{
	char materialsCode[material_maxSize_Code + 1];
	char materialsName[material_maxSize_Code + 1];
	char countUnit[material_maxSize_CountUnit + 1];
	unsigned int inventoryNumber;
};

struct nodeTree {
	MATERIAL data;
	int balanceFactor;
	struct nodeTree *pLeft;
	struct nodeTree *pRight;
};
typedef nodeTree* LIST_MATERIAL;
typedef nodeTree* TREE;

void avl_insert(TREE &tr, MATERIAL data);
void treeInitialize(TREE &lm);
bool treeNodeIsExists(TREE tr, char *code);
MATERIAL treeSearchNode(TREE tr, char *code);
void tree_insertByMoney(TREE &tr, MATERIAL data);
void NLR(TREE tr);
void materials_EditQuantity(LIST_MATERIAL &tr, char *code, int qunatity);
int materials_Count(TREE tr);

bool materials_AddToList(LIST_MATERIAL &tr);
void materials_Add(LIST_MATERIAL &tr);
bool materials_Remove(LIST_MATERIAL &tr);
bool materials_Edit(LIST_MATERIAL &tr);
void material_Show(LIST_MATERIAL lm, LOCATION lcDisplay, int modeShow);
void material_showAlone(MATERIAL m, LOCATION lcDisplay);
void material_ViewRevenue(LIST_MATERIAL lmShow, int quantity);