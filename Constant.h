#pragma once

enum keyControl {dir_LEFT = 75, dir_RIGHT = 77, dir_UP = 72, dir_DOWN = 80, key_SPACE = 32, key_ENTER = 13, key_ESC = 27};
enum notifyButton{YES, NO, CANCEL,YES_NO, YES_CANCEL};
enum eModeImportData {NUMBER, LOWER, UPPER, ALL, UPPER_LOWER ,UPPER_NUMBER, ALL_SPACE, SEX, TYPEBILL};

const unsigned int material_maxSize_Code = 11;
const unsigned int material_maxSize_Name = 11;
const unsigned int material_maxSize_CountUnit = 11;
const unsigned int material_maxSize_InventoryNumber = 8;
const unsigned int material_quantityFields = 4;
const unsigned int material_quantityMax = 50;
//int material_quantityNow = 0;

const unsigned int employees_quantityMax = 500;
const unsigned int employees_maxSize_Code = 11;
const unsigned int employees_maxSize_FamilyName = 11;
const unsigned int employees_maxSize_FirstName = 11;
const unsigned int employees_quantityFields = 4;

const  int bill_maxSize_Code = 20;
const unsigned int bill_maxSize_invoiceDate = 10;
const unsigned int bill_quantityFields = 4;


const unsigned int billD_maxSize_quantity = 4;
const unsigned int billD_maxSize_VAT = 3;
const unsigned int billD_maxSize_unitPrice = 9;
const unsigned int billD_quantityFields = 4;
//display
const int billD_Location_Gird_x = 2;
const int billD_Location_Gird_y = 2;

const int bill_Location_Gird_x = 2;
const int bill_Location_Gird_y = 2;


#define text_Key                "NguyenPTIT"
#define ColorCode_Black			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define maxLengthChar             70