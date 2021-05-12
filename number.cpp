#include "number.h"
#include <cctype>
#include <string.h>
#include <cstdlib>
#include <stdio.h>

bool IsNumber(char* str)
{
	int len = strlen(str);
	bool is_dot = false;
	for (int i = 0; i < len; ++i)
	{
		if (!isdigit(str[i]) && str[i] != '.')
			return false;
		if (str[i] == '.')
		{
			if (is_dot || i == (len - 1) || i == 0)
				return false;
			is_dot = true;
		}
	}
	return true;
}

void DecNumber(char* str)
{
	int int_part = atoi(str);
	if (int_part != 0)
		int_part--;
	char new_int_part[100] = { '\0' };
	sprintf(new_int_part, "%d", int_part);
	char float_part[100] = { '\0' };
	for (int i = 0; i < strlen(str); ++i)
	{
		if (str[i] == '.')
		{
			memcpy(float_part, str + i, strlen(str) - i + 1);
			break;
		}
	}
	strcpy(str, "");
	if (int_part == 0)
		strcat(str, "(-");
	strcat(str, new_int_part);
	strcat(str, float_part);
	if (int_part == 0)
		strcat(str, ")");
}
