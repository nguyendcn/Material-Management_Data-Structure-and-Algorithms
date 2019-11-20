#include "Display.h"

void dis_wait(LOCATION lcDisplay, char *caption, int time, int color)
{
	gotoxy(lcDisplay.x, lcDisplay.y); ColorText(caption, color);
	int drTime_x = lcDisplay.x + (strlen(caption) / 2);
	gotoxy(drTime_x, lcDisplay.y + 1); std::cout << time;

	while (true)
	{
		Sleep(1000);
		time--;
		gotoxy(drTime_x, lcDisplay.y + 1); std::cout << "    ";
		if (time < 0)
			break;
		gotoxy(drTime_x, lcDisplay.y + 1); std::cout << time;
	}

	for (int i = 0; i < static_cast<int>(strlen(caption)); i++)
	{
		gotoxy(lcDisplay.x++, lcDisplay.y);  std::cout << " ";
	}
}

void dis_Clear(LOCATION lcHeadClear, Size size)
{
	LOCATION LCtemp = lcHeadClear;
	for (int i = 0; i < size.height; i++)
	{
		for (int j = 0; j < size.width; j++)
		{
			gotoxy(lcHeadClear.x, lcHeadClear.y);
			cout << " ";
			lcHeadClear.x++;
		}
		lcHeadClear.x = LCtemp.x;
		lcHeadClear.y++;
	}
}

void drawRectangle(LOCATION &result, LOCATION lc, Size s, int colorBG, int colorBorder)
{
	LOCATION LCtemp = lc;
	for (int i = 0; i < s.height; i++)
	{
		for (int j = 0; j < s.width; j++)
		{
			TextColor(colorBorder); // set color border
			if (i == 0 || j == 0 || i == s.height - 1 || j == s.width - 1)
			{
				gotoxy(lc.x, lc.y);
				if (i == 0 && j == 0)
				{
					std::cout << (char)201;  // ╔
				}
				else if (i == 0 && j == s.width - 1)
				{
					std::cout << (char)187; // ╗
				}
				else if (i == s.height - 1 && j == 0)
				{
					std::cout << (char)200; // ╚
				}
				else if (i == s.height - 1 && j == s.width - 1)
				{
					std::cout << (char)188; // ╝
				}
				else if (i == 0 || i == s.height - 1)
				{
					std::cout << (char)205; // ═
				}
				else if (j == 0 || j == s.width - 1)
				{
					std::cout << (char)186;  // ║
				}
			}
			else
			{
				BGColorText(" ", ColorCode_DarkWhite, colorBG); // set color bg
			}
			lc.x++;
		}
		lc.x = LCtemp.x;
		lc.y++;
	}
	
	TextColor(ColorCode_DarkWhite); // reset color text;

	result.y = LCtemp.y + (s.height / 2);
	result.x = LCtemp.x + 2;
}

void drawBox(LOCATION lcDisplay, Size size, char *caption)
{
	LOCATION LCtemp = lcDisplay;
	for (int i = 0; i < size.height; i++)
	{
		for (int j = 0; j < size.width; j++)
		{
			if (i == 0 || j == 0 || i == size.height - 1 || j == size.width - 1)
			{
				gotoxy(lcDisplay.x, lcDisplay.y);
				if (i == 0 && j == 0)
				{
					std::cout << (char)201;  // ╔
				}
				else if (i == 0 && j == size.width - 1)
				{
					std::cout << (char)187; // ╗
				}
				else if (i == size.height - 1 && j == 0)
				{
					std::cout << (char)200; // ╚
				}
				else if (i == size.height - 1 && j == size.width - 1)
				{
					std::cout << (char)188; // ╝
				}
				else if (i == 0 || i == size.height - 1)
				{
					std::cout << (char)205; // ═
				}
				else if (j == 0 || j == size.width - 1)
				{
					std::cout << (char)186;  // ║
				}
			}
			lcDisplay.x++;
		}
		lcDisplay.x = LCtemp.x;
		lcDisplay.y++;
	}

	if (static_cast<int>(strlen(caption)) + 5 < size.width)
	{
		gotoxy(LCtemp.x + 2, LCtemp.y); std::cout << caption;
	}
}

void drawBorder(LIST_LOCATION &lcResult, LOCATION displayLC, int rowQuantity, int heightOne, LIST_TITLE title)
{
	int tempX = displayLC.x;
	for (int i = 0; i < rowQuantity + 1; i++)
	{
		for (int j = 0; j < title.size; j++)
		{
			Size s;
			LOCATION temp;
			s.height = heightOne;
			s.width = title.ltitle[j].width;

			if (i == 0)
			{
				//drawRectangle(temp, displayLC, s, ColorCode_DarkWhite, ColorCode_DarkWhite, title.ltitle[j].data);
				button(false, title.ltitle[j].data, displayLC, s, ColorCode_DarkWhite, ColorCode_DarkRed); // title
			}
			else
			{
				drawRectangle(temp, displayLC, s, ColorCode_DarkWhite, ColorCode_DarkWhite);
				List_InsertItem(lcResult, lcResult.size, temp);
			}

			displayLC.x += (title.ltitle[j].width - 1);
		}
		displayLC.x = tempX;
		displayLC.y += heightOne;
	}
}

int variFindMaxSize(LIST_ARRAY_CHAR arrC)
{
	if (arrC.size == 0)
		return 0;
	int maxSize = strlen(arrC.listSTR[0].str);
	for (int i = 1; i < arrC.size; i++)
	{
		if (static_cast<int>(strlen(arrC.listSTR[i].str)) > maxSize)
			maxSize = strlen(arrC.listSTR[i].str);
	}
	return maxSize;
}

int findMax(int a[], int size)
{
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (a[i] > max)
			max = a[i];
	}
	return max;
}

void hButton(int text, int x, int y) // button back
{
	int Check;
	do {
		setBGColor(15);
		TextColor(0);
		gotoxy(x, y);
		std::cout << text;
		if (_kbhit())
		{
			Check = _getch();
			if (Check == 49)
				break;
		}
	} while (true);
	setBGColor(0);
	TextColor(7);
}

void button(bool isFocus, char *text, LOCATION lc, Size sizeBTN, int colorFocus, int colornFocus)
{
	LOCATION l;
	int padding = 4;

	LOCATION result;
	result.x = lc.x + (sizeBTN.width / 2) - (strlen(text) / 2);
	result.y = lc.y + (sizeBTN.height / 2);

	if (isFocus) //Focusing
	{
		drawRectangle(l, lc, sizeBTN, colorFocus, colorFocus);
		
		if (result.x <= lc.x) // length text > size width => cut: abcef => a...
		{
			gotoxy(lc.x + 1, result.y);
			BGColorText(char_substr(text, 0, sizeBTN.width - 5), ColorCode_DarkWhite, colorFocus);
			BGColorText("...", ColorCode_DarkWhite, colorFocus);
		}
		else
		{
			gotoxy(result.x, result.y);
			BGColorText(text, ColorCode_DarkWhite, colorFocus);
		}
	}
	else
	{
		drawRectangle(l, lc, sizeBTN, colornFocus, ColorCode_DarkWhite);
		
		if (result.x <= lc.x) // length text > size width => cut: abcef => a...
		{
			gotoxy(lc.x + 1, result.y);
			BGColorText(char_substr(text, 0, sizeBTN.width - 5), ColorCode_DarkWhite, colornFocus);
			BGColorText("...", ColorCode_DarkWhite, colornFocus);
		}
		else
		{
			gotoxy(result.x, result.y);
			BGColorText(text, ColorCode_DarkWhite, colornFocus);
		}
	}
	setBGColor(ColorCode_Black); // reset;
}

bool messagebox(char *content, int notifyButton, LOCATION lcDisplay)
{
	LOCATION l;
	Size sizeMessageBox;
	sizeMessageBox.height = 15;
	sizeMessageBox.width = strlen(content) + 5;

	Size sizePerButton;
	sizePerButton.height = 5;
	sizePerButton.width = 4; // 4 + length;

	int margin_left = 3;
	int margin_right = 3;
	int margin_buttom = 2;

	if (notifyButton == YES_NO)
	{
		drawRectangle(l, lcDisplay, sizeMessageBox, ColorCode_DarkWhite, ColorCode_DarkWhite);
		gotoxy(lcDisplay.x + 5, lcDisplay.y + 2); BGColorText("Thong Bao", ColorCode_Blue, ColorCode_DarkWhite);
		gotoxy(lcDisplay.x + 3, lcDisplay.y + 4); BGColorText(content, ColorCode_Blue, ColorCode_DarkWhite);

		int index = 0;
		LOCATION lcbtnYES, lcbtnNO;
		lcbtnYES.x = lcDisplay.x + margin_left;
		lcbtnYES.y = (lcDisplay.y + sizeMessageBox.height) - (margin_buttom + sizePerButton.height);
		lcbtnNO.x = (lcDisplay.x + sizeMessageBox.width) - (margin_right + sizePerButton.width + 3);
		lcbtnNO.y = (lcDisplay.y + sizeMessageBox.height) - (margin_buttom + sizePerButton.height);

		sizePerButton.width = sizePerButton.width + strlen("YES");

  		button(true, "YES", lcbtnYES , sizePerButton, ColorCode_Blue, ColorCode_Black);
		button(false, "NO", lcbtnNO, sizePerButton, ColorCode_Blue, ColorCode_Black);

		while (true)
		{
			if (_kbhit())
			{
				int key = _getch();

				if (key == 75) // LEFT
				{
					index--;
					if (index < 0)
					{
						index = 1;
						button(false, "YES", lcbtnYES, sizePerButton, ColorCode_Blue, ColorCode_Black);
						button(true, "NO", lcbtnNO, sizePerButton, ColorCode_Blue, ColorCode_Black);
					}
					else
					{
						button(true, "YES", lcbtnYES, sizePerButton, ColorCode_Blue, ColorCode_Black);
						button(false, "NO", lcbtnNO, sizePerButton, ColorCode_Blue, ColorCode_Black);
					}

				}
				else if (key == 77) // RIGHT
				{
					index++;
					if (index > 1)
					{
						index = 0;
						button(true, "YES", lcbtnYES, sizePerButton, ColorCode_Blue, ColorCode_Black);
						button(false, "NO", lcbtnNO, sizePerButton, ColorCode_Blue, ColorCode_Black);
					}
					else
					{
						button(false, "YES", lcbtnYES, sizePerButton, ColorCode_Blue, ColorCode_Black);
						button(true, "NO", lcbtnNO, sizePerButton, ColorCode_Blue, ColorCode_Black);
					}
				}
				else if (key == 13)
				{
					if (index == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
	else if (notifyButton == YES || notifyButton == NO || notifyButton == CANCEL)
	{
		char *text = new char[7];
		strcpy_s(text, 6, notifyButton == YES ? "YES" : (notifyButton == NO ? "NO" : "CANCEL"));

		drawRectangle(l, lcDisplay, sizeMessageBox, ColorCode_DarkWhite, ColorCode_DarkWhite);
		gotoxy(lcDisplay.x + 5, lcDisplay.y + 2); BGColorText("Thong Bao", ColorCode_Blue, ColorCode_DarkWhite);
		gotoxy(lcDisplay.x + 3, lcDisplay.y + 4); BGColorText(content, ColorCode_Blue, ColorCode_DarkWhite);

		sizePerButton.width = 4 + strlen("CANCEL");

		LOCATION lcBTN;
		lcBTN.x = (lcDisplay.x + (sizeMessageBox.width / 2)) - (sizePerButton.width / 2);
		lcBTN.y = (lcDisplay.y + sizeMessageBox.height) - (sizePerButton.height + margin_buttom);

		button(true, text, lcBTN, sizePerButton, ColorCode_Blue, ColorCode_DarkWhite);

		while (true)
		{
			int key = _getch();
			if (key == 13)
			{
				return true;
			}
		}
	}
	return false;
}

void drawEnterData(LIST_LOCATION &lcResult, LIST_PROPERTIES prop, LOCATION displayLC)
{
	LOCATION lcTemp, getLC, lS;
	Size s;
	s.height = 3;
	lS = displayLC;

	// find max size name variable
	LIST_ARRAY_CHAR text;
	int arrLength[15];

	for (int i = 0; i < prop.size; i++)
	{
		List_InsertItem(text, text.size, prop.lprop[i].variables.name);
		arrLength[i] = prop.lprop[i].maxLength;
	}

	int maxSizeVariables = variFindMaxSize(text) + 3;
	int maxSizeData = findMax(arrLength, prop.size);
	s.width = maxSizeData + 3;

	List_Clear(text); // delete list "text"

	for (int i = 0; i < prop.size; i++)
	{
		gotoxy(displayLC.x, displayLC.y); cout << prop.lprop[i].variables.name; // draw text variables

		lcTemp.x = displayLC.x + maxSizeVariables;
		lcTemp.y = displayLC.y - 1;

		drawRectangle(getLC, lcTemp, s, ColorCode_DarkWhite, ColorCode_Blue); // draw box

		gotoxy(lcTemp.x, lcTemp.y - 1); ColorText(prop.lprop[i].variables.notify, prop.lprop[i].variables.color); // print notify;

		lcTemp.x = displayLC.x + maxSizeVariables + 1;
		lcTemp.y = displayLC.y;

		gotoxy(lcTemp.x, lcTemp.y); cout << prop.lprop[i].variables.data;  // print data

		List_InsertItem(lcResult, lcResult.size, lcTemp);
		displayLC.y += (s.height + 1);
	}

	lcTemp.x = displayLC.x + 3;
	lcTemp.y += 4;

	// add two button in bottom 
	Size sbtn;
	sbtn.height = 5;
	sbtn.width = 9;
	List_InsertItem(lcResult, lcResult.size, lcTemp);
	button(false, "XONG", lcTemp, sbtn, ColorCode_Blue, ColorCode_Black);

	lcTemp.x = displayLC.x + maxSizeVariables + s.width - 9; // distance between two button

	List_InsertItem(lcResult, lcResult.size, lcTemp);
	button(false, "HUY", lcTemp, sbtn, ColorCode_Blue, ColorCode_Black);

	Size sGird;
	LOCATION lGird;
	lGird = {lS.x - 2, lS.y - 3};
	sGird = { (lcTemp.x + 15) - lGird.x, lcTemp.y + 8 - lGird.x };
	drawBox(lGird, sGird, "Nhap Du Lieu");
}

void enterDataToVariable(LIST_ARRAY_CHAR &dataVariables, LIST_PROPERTIES prop, LOCATION displayLC)
{
	Size sBTN; sBTN.height = 5; sBTN.width = 9;
	LIST_LOCATION arrLC;
	drawEnterData(arrLC, prop, displayLC); // draw

	int sizeLC = arrLC.size;

	for (int i = 0; i < prop.size; i++) // add existing data to list "dataVariable"
	{
		List_InsertItem(dataVariables, dataVariables.size, prop.lprop[i].variables.data);
	}

	//find data field empty
	for (int i = 0; i < prop.size; i++)
	{
		if (strcmp(dataVariables.listSTR[i].str, "") == 0)
		{
			strcpy_s(dataVariables.listSTR[i].str, dataEntry(dataVariables.listSTR[i].str, arrLC.lloca[i], prop.lprop[i].mode.modeImport, prop.lprop[i].maxLength)); // entry
		}
	}

	button(true, "XONG", arrLC.lloca[sizeLC - 2], sBTN, ColorCode_Blue, ColorCode_Black); // focus to button "XONG"

	int index = sizeLC - 2; // focusing is btn OK
	bool focusButton = false;

	bool isControl = false;
	while (true)
	{
		if (_kbhit())
		{
			char key = _getch();

			if ((key >= '0' && key <= '9' || key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z') && !isControl)
			{
				//cout << "not is  control" << endl;
			}
			else if (key == -32)
			{
				isControl = true;
			}
			else if (isControl)
			{
				if (key == 80)
				{
					//cout << "DOWN";
					index++;
					if (index < prop.size)
					{
						if (!prop.lprop[index].mode.enable) // no enable import data
							index++;
					}

					if (index > sizeLC - 1)
					{
						index = 0;
						if (!prop.lprop[index].mode.enable) // no enable import data
						{
							index++;
							button(false, "HUY", arrLC.lloca[sizeLC - 1], sBTN, ColorCode_Blue, ColorCode_Black);
						}
						else
						{
							button(false, "HUY", arrLC.lloca[sizeLC - 1], sBTN, ColorCode_Blue, ColorCode_Black);
							strcpy_s(dataVariables.listSTR[index].str, dataEntry(dataVariables.listSTR[index].str, arrLC.lloca[index], prop.lprop[index].mode.modeImport, prop.lprop[index].maxLength));
						}
					}

					if (index == sizeLC - 2) // focus button XONG
					{
						button(true, "XONG", arrLC.lloca[sizeLC - 2], sBTN, ColorCode_Blue, ColorCode_Black);
						//button(false, "HUY", arrLC.lloca[sizeLC - 1], sBTN, ColorCode_Blue, ColorCode_Black);
					}
					else if (index == sizeLC - 1) // focus button HUY
					{
						button(false, "XONG", arrLC.lloca[sizeLC - 2], sBTN, ColorCode_Blue, ColorCode_Black);
						button(true, "HUY", arrLC.lloca[sizeLC - 1], sBTN, ColorCode_Blue, ColorCode_Black);
					}
					else
					{
						strcpy_s(dataVariables.listSTR[index].str, dataEntry(dataVariables.listSTR[index].str, arrLC.lloca[index], prop.lprop[index].mode.modeImport, prop.lprop[index].maxLength));
					}
				}
				else if (key == 72)
				{
					//cout << "UP";
					index--;
					if (index < prop.size)
					{
						if (!prop.lprop[index].mode.enable)
							index--;
					}
					if (index < 0)
					{
						index = sizeLC - 1;
						button(true, "HUY", arrLC.lloca[sizeLC - 1], sBTN, ColorCode_Blue, ColorCode_Black);
					}
					else if (index == arrLC.size - 1)
					{
						button(true, "HUY", arrLC.lloca[sizeLC - 1], sBTN, ColorCode_Blue, ColorCode_Black);
						//button(false, "XONG", arrLC.lloca[sizeLC - 2], sBTN, ColorCode_Blue, ColorCode_Black);
					}
					else if (index == sizeLC - 2)
					{
						button(false, "HUY", arrLC.lloca[sizeLC - 1], sBTN, ColorCode_Blue, ColorCode_Black);
						button(true, "XONG", arrLC.lloca[sizeLC - 2], sBTN, ColorCode_Blue, ColorCode_Black);
					}
					else if (index <= arrLC.size - 3)
					{
						button(false, "XONG", arrLC.lloca[sizeLC - 2], sBTN, ColorCode_Blue, ColorCode_Black);
						strcpy_s(dataVariables.listSTR[index].str, dataEntry(dataVariables.listSTR[index].str, arrLC.lloca[index], prop.lprop[index].mode.modeImport, prop.lprop[index].maxLength));
					}
					else
					{
						strcpy_s(dataVariables.listSTR[index].str, dataEntry(dataVariables.listSTR[index].str, arrLC.lloca[index], prop.lprop[index].mode.modeImport, prop.lprop[index].maxLength));
					}
				}
				else if (key == 75)
				{
					//cout << "LEFT";
				}
				else if (key == 77)
				{
					//cout << "RIGHT";
				}
				isControl = false;
			}
			else
			{
				if (key == 13 && index == sizeLC - 2)
				{
					//cout << "ENTER";
					List_InsertItem(dataVariables, dataVariables.size, "DONE");
					break;
				}
				else if (key == 13 && index == sizeLC - 1)
				{
					//cout << "ENTER";
					List_InsertItem(dataVariables, dataVariables.size, "CANCEL");
					break;
				}
			}
		}
	}
	List_Clear(arrLC);
}

void dis_drawEntryDate(LIST_LOCATION &lLocationGetData, LIST_ARRAY_CHAR quantityEntry)
{
	LOCATION lcGird = { bill_Location_Gird_x, bill_Location_Gird_y };
	Size sGird;

	char *day = "Ngay";	char *month = "Thang";	char *year = "Nam";
	LOCATION lcText = { lcGird.x + 3, lcGird.y + 4 };
	LOCATION lcGet, lcBox;
	Size sBox = { 9, 3 };

	Size sButton = { 8, 5 };
	LOCATION lcButton;

	int maxSize = variFindMaxSize(quantityEntry);

	for (int run = 0; run < quantityEntry.size; run++)
	{
		gotoxy(lcText.x, lcText.y); std::cout << quantityEntry.listSTR[run].str << ":";

		for (int field = 0; field < 3; field++)
		{
			if (field == 0) // day
			{
				int size = strlen(day);
				gotoxy(lcText.x + maxSize + 3, lcText.y); std::cout << day;
				lcBox = { lcText.x + maxSize + 3 + size + 1, lcText.y - 1};
				drawRectangle(lcGet, lcBox, sBox, ColorCode_Black, ColorCode_DarkWhite);
				List_InsertItem(lLocationGetData, lLocationGetData.size, lcGet);
			}
			else if (field == 1) // month
			{
				int size = strlen(month);
				gotoxy(lcBox.x + sBox.width + 5, lcText.y);	std::cout << month;
				lcBox = { lcBox.x + sBox.width + 5 + size + 1, lcText.y - 1};
				drawRectangle(lcGet, lcBox, sBox, ColorCode_Black, ColorCode_DarkWhite);
				List_InsertItem(lLocationGetData, lLocationGetData.size, lcGet);
			}
			else if (field == 2) // year
			{
				int size = strlen(year);
				gotoxy(lcBox.x + sBox.width + 5, lcText.y);	std::cout << year;
				lcBox = { lcBox.x + sBox.width + 5 + size + 1, lcText.y - 1};
				drawRectangle(lcGet, lcBox, sBox, ColorCode_Black, ColorCode_DarkWhite);
				List_InsertItem(lLocationGetData, lLocationGetData.size, lcGet);
			}
		}
		lcText = { lcGird.x + 3, lcText.y + (sBox.height / 2) + 3 };
	}
	
	// draw 2 button
	lcButton = { lcGird.x + 11, lcText.y + 4 - sButton.height };
	button(false, "XONG", lcButton, sButton, ColorCode_Blue, ColorCode_Black);
	List_InsertItem(lLocationGetData, lLocationGetData.size, lcButton);
	lcButton = { (lcBox.x + sBox.width + 3) - 11 - sBox.width, lcText.y + 4 - sButton.height };
	button(false, "HUY.", lcButton, sButton, ColorCode_Blue, ColorCode_Black);
	List_InsertItem(lLocationGetData, lLocationGetData.size, lcButton);
	
	//draw gird
	sGird = { (lcBox.x + sBox.width + 3) - lcGird.x, (lcText.y - lcGird.y) + 5};
	drawBox(lcGird, sGird, "Nhap ngay");
}