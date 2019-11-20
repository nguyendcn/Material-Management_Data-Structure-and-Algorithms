#pragma once
#include "Employees.h"
#include "Material.h"
#include "Bill.h"

void database_SaveBill(LIST_BILL lb);
bool database_LoadBill(LIST_BILL &lb, LIST_EMPLOYEES le);

void database_SaveEmployees(LIST_EMPLOYEES le);
bool database_LoadEmployees(LIST_EMPLOYEES &le);

void database_SaveMaterial(LIST_MATERIAL lm);
bool database_LoadMaterial(LIST_MATERIAL &t);

void database_LoadData(LIST_MATERIAL &lm, LIST_EMPLOYEES &le, LIST_BILL &lb);