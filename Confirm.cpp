#include "Confirm.h"

bool checkMode(int mode, int key)
{
	if (mode == UPPER_LOWER)
	{
		if (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z')
			return true;
		return false;
	}
	else if (mode == NUMBER)
	{
		if (key >= '0' && key <= '9')
			return true;
		return false;
	}
	else if (mode == UPPER)
	{
		if (key >= 'A' && key <= 'Z')
			return true;
		return false;
	}
	else if (mode == LOWER)
	{
		if (key >= 'a' && key <= 'z')
			return true;
		return false;
	}
	else if (mode == ALL)
	{
		if (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key >= '0' && key <= '9' || key == 32)
			return true;
		return false;
	}
	else if (mode == ALL_SPACE)
	{
		if (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key >= '0' && key <= '9' || key == 32)
			return true;
		return false;
	}
	else if (mode == UPPER_NUMBER)
	{
		if (key >= 'A' && key <= 'Z' || key >= '0' && key <= '9')
			return true;
		return false;
	}
	else if (mode == SEX)
	{
		if (key == '0' || key == '1')
			return true;
		return false;
	}
	else if (mode == TYPEBILL)
	{
		if (key == 'n' || key == 'N' || key == 'x' || key == 'X')
			return true;
		return false;
	}
	return false;
}

char* char_toUpper(char *text)
{
	int size = strlen(text);
	for (int run = 0; run < size; run++)
	{
		if (text[run] >= 'a' && text[run] <= 'z')
		{
			text[run] -= 32;
		}
	}
	return text;
}

char* char_toLower(char *text)
{
	int size = strlen(text);
	for (int run = 0; run < size; run++)
	{
		if (text[run] >= 'A' && text[run] <= 'Z')
		{
			text[run] += 32;
		}
	}
	return text;
}

void char_erase(char *&list, int LOCATIONDelete)
{
	if (LOCATIONDelete < 0 /*|| LOCATIONDelete > MaxEmployees*//* || List_IsEmpty(list)*/)
	{
		return;
	}
	int length = strlen(list);
	for (int i = LOCATIONDelete + 1; i < length; i++)
	{
		list[i - 1] = list[i];
	}
	list[length - 1] = '\0';
}

char* char_formartText(char *text)
{	
	int run = strlen(text) - 1;
	if (run >= 0)
	{
		// delete right
		while (text[run] == ' ')
		{
			run--;
			if (run < 0)
				return "";
		}

		if (run < static_cast<int>(strlen(text)) - 1)
		{
			text[run + 1] = '\0';
		}

		//delete left
		while (text[0] == ' ' || text[0] == '\0')
		{
			if (text[0] == '\0')
				return "";
			char_erase(text, 0);
		}

		int size = strlen(text) - 1;
		run = 0;
		//delete between
		if (size > 2)
		{
			for(int i = 0; i < size; i++)
			{
				if (text[i] == ' ' && text[i + 1] == ' ')
				{
					char_erase(text, i);
					i--;
					size = strlen(text) - 1;
				}
			}
		}

		//upper lower
		size = strlen(text);
		for (int i = 0; i < size; i++)
		{
			if (i == 0 && (text[0] >= 'a' && text[0] <= 'z'))
			{
				text[0] -= 32;
			}
			else if (text[i - 1] == ' ' && (text[i] >= 'a' && text[i] <= 'z'))
			{
				text[i] -= 32;
			}
			else
			{
				if (text[i] >= 'A' && text[i] <= 'Z')
				{
					text[i] += 32;
				}
			}
		}
		return text;
	}
	else
		return "";
}

char* char_substr(char *Source, unsigned int lcCut, unsigned int quantity)
{
	char *temp = new char[quantity + 1];
	temp[quantity] = '\0';
	if (lcCut >= strlen(Source) || lcCut + quantity  > strlen(Source))
	{
		return temp;
	}
	else
	{
		int size = strlen(Source);
		for (int i = 0; i < size; i++)
		{
			if (i == lcCut)
			{
				for (unsigned int j = 0; j < quantity; j++)
				{
					temp[j] = Source[i + j];
				}
				return temp;
			}
		}
	}
	return temp;
}

void char_insert(char *list, int LOCATIONAdd, char data)
{
	if (LOCATIONAdd < 0 || LOCATIONAdd > static_cast<int>(strlen(list)) /*|| isFull(list)*/)
	{
		return;
	}

	int length = strlen(list);
	for (int i = length - 1; i >= LOCATIONAdd; i--)
	{
		list[i + 1] = list[i];
	}
	list[LOCATIONAdd] = data;
	list[length + 1] = '\0';
}

char* dataEntry(char *text, LOCATION lc, int mode, int maxLength) // TEXT NUMBER UPPER LOWER ALL
{
	gotoxy(lc.x, lc.y); std::cout << text;
	int head = lc.x;

	bool isControl = false;
	while (true)
	{
		if (_kbhit())
		{// cho datansap xep lon xon,roi dung gi de load ra 1 file, co che no ntn
			char key = _getch();

			if ((key >= '0' && key <= '9' || key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z') && !isControl)
			{
				//cout << "not is  control" << endl;
				int lengthText = strlen(text);
				if (checkMode(mode, key) && lengthText <= maxLength) // condition
				{
					if (wherex() == head + lengthText && lengthText < maxLength)
					{
						char_insert(text, strlen(text), key);
						std::cout << key;
					}
					else
					{
						if (wherex() < (head + lengthText))
							text[wherex() - head] = (char)key;

						int x = wherex();
						gotoxy(head, wherey()); std::cout << text;
						gotoxy(x, wherey());
					}
				}
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
				}
				else if (key == 72)
				{
					//cout << "UP";
				}
				else if (key == 75)
				{
					//cout << "LEFT";
					if (wherex() > head)
					{
						gotoxy(wherex() - 1, wherey());
					}
				}
				else if (key == 77)
				{
					//cout << "RIGHT";
					int lengthText = strlen(text);
					if (wherex() < head + lengthText)
					{
						gotoxy(wherex() + 1, wherey());
					}
				}
				isControl = false;
			}
			else
			{
				if (key == 8) // backSpace
				{
					int lengthText = strlen(text);
					if (wherex() == head + lengthText && strcmp(text, "") != 0)
					{
						char_erase(text, lengthText - 1);
						gotoxy(head, wherey()); std::cout << text << " ";
						gotoxy(wherex() - 1, wherey());
					}
					else
					{
						if (strcmp(text, "") != 0 && wherex() >= head)
						{
							if (wherex() == head)
							{
								char_erase(text, 0);
								gotoxy(head, wherey()); std::cout << text << " ";
								gotoxy(head, wherey());
							}
							else
							{
								int x = wherex();
								char_erase(text, wherex() - head);
								gotoxy(head, wherey()); std::cout << text << " ";
								gotoxy(x - 1, wherey());
							}
						}
					}
				}
				if (key == 13 && strcmp(text, "") != 0)
				{
					break;
				}
			}
		}
	}
	return text;
}

bool dateIsTrue(int day, int month, int year)
{
	time_t rawtime = time(0);
	struct tm now;
	localtime_s(&now, &rawtime);

	if (day <= 0 || day > 31)
		return false;
	else if (month <= 0 || month > 12)
		return false;
	else if (year < (now.tm_year + 1900 - 10) || year >(now.tm_year + 1900))
		return false;

	return true;
}

void converDateToArrDate(char *input, LIST_ARRAY_CHAR &dateResult)
{
	string date = input;
	string strTemp = "";
	
	strTemp += date[0]; strTemp += date[1];
	List_InsertItem(dateResult, dateResult.size, (char*)strTemp.c_str());

	strTemp = "";
	strTemp += (date[3]); strTemp += (date[4]);
	List_InsertItem(dateResult, dateResult.size, (char*)strTemp.c_str());

	strTemp = "";
	strTemp += (date[6]); strTemp += (date[7]); strTemp += (date[8]); strTemp += (date[9]);
	List_InsertItem(dateResult, dateResult.size, (char*)strTemp.c_str());
}

bool conf_dateIsBetween(LIST_ARRAY_CHAR dateDock, LIST_ARRAY_CHAR dateCompare)
{
	int day_1, month_1, year_1;
	int day_2, month_2, year_2;
	int day_3, month_3, year_3;

	day_1 = atoi(dateDock.listSTR[0].str);
	month_1 = atoi(dateDock.listSTR[1].str);
	year_1 = atoi(dateDock.listSTR[2].str);

	day_2 = atoi(dateDock.listSTR[3].str);
	month_2 = atoi(dateDock.listSTR[4].str);
	year_2 = atoi(dateDock.listSTR[5].str);

	day_3 = atoi(dateCompare.listSTR[0].str);
	month_3 = atoi(dateCompare.listSTR[1].str);
	year_3 = atoi(dateCompare.listSTR[2].str);

	if (year_3 > year_2 || year_3 < year_1) // outside
	{
		return false;
	}
	else if (year_3 < year_2 && year_3 > year_1) // year between => true
	{
		return true;
	}
	else if (year_3 == year_2 && year_3 != year_1) // equal
	{
		if (month_3 > month_2)
			return false;
		else if (month_3 == month_2)
		{
			if (day_3 > day_2)
				return false;
			else
				return true;
		}
		else
			return true;
	}
	else if (year_3 == year_1 && year_3 != year_2)
	{
		if (month_3 < month_1)
		{
			return false;
		}
		else if (month_3 == month_1)
		{
			if (day_3 > day_1)
				return false;
			else
				return true;
		}
		else
			return true;
	}
	else // year_3 == year_2 == year_1
	{
		if (month_3 == month_2 && month_3 == month_1)
		{
			if (day_1 == day_2 && day_1 == day_3)
				return true;
			else if (day_3 > day_2)
				return false;
			else if (day_3 < day_1)
				return false;
		}
		else if (month_3 > month_2)
			return false;
		else if (month_3 < month_1)
			return false;
		else if (month_3 == month_2)
		{
			if (day_3 > day_2)
				return false;
			else
				return true;
		}
		else if (month_3 == month_1)
		{
			if (day_3 < day_1)
				return false;
			else
				return true;
		}
	}
	return false;
}

bool conf_checkDATE(LIST_ARRAY_CHAR lDate)
{
	int day_1, month_1, year_1;
	int day_2, month_2, year_2;

	day_1 = atoi(lDate.listSTR[0].str);
	month_1 = atoi(lDate.listSTR[1].str);
	year_1 = atoi(lDate.listSTR[2].str);

	day_2 = atoi(lDate.listSTR[3].str);
	month_2 = atoi(lDate.listSTR[4].str);
	year_2 = atoi(lDate.listSTR[5].str);

	if (dateIsTrue(day_1, month_1, year_1) && dateIsTrue(day_2, month_2, year_2))
	{
		if (year_2 < year_1)
		{
			return false;
		}
		else if (year_2 == year_1)
		{
			if (month_2 < month_1)
				return false;
			else if (month_2 == month_1)
			{
				if (day_2 < day_1)
					return false;
				return true;
			}
		}
		return true;
	}
	else
		return false;
}