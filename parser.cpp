#include "parser.h"
#include "global.h"
#include "string.h"
#include <iostream>

void Parser(Literal* result, char* input, Stack<char*>& coefficents)
{
    int len = strlen(input);
    int result_index = 0;
    for (int i = 0; i < len; ++i)
    {
        if (i < (len - 2) && input[i] == 's' && input[i + 1] == 'i' && input[i + 2] == 'n')
        {
            result[result_index] = sin;
            i += 2;
            result_index++;
            continue;
        }
        if (i < (len - 2) && input[i] == 'c' && input[i + 1] == 'o' && input[i + 2] == 's')
        {
            result[result_index] = cos;
            i += 2;
            result_index++;
            continue;
        }
        if (i < (len - 1) && input[i] == 't' && input[i + 1] == 'g')
        {
            result[result_index] = tg;
            i += 1;
            result_index++;
            continue;
        }
        if (i < (len - 1) && input[i] == 'l' && input[i + 1] == 'n')
        {
            result[result_index] = ln;
            i += 1;
            result_index++;
            continue;
        }
        if (i < (len - 2) && input[i] == 'c' && input[i + 1] == 't' && input[i + 2] == 'g')
        {
            result[result_index] = ctg;
            i += 2;
            result_index++;
            continue;
        }
        if (i < (len - 5) && input[i] == 'a' && input[i + 1] == 'r' && input[i + 2] == 'c' && input[i + 3] == 's' && input[i + 4] == 'i' && input[i + 5] == 'n')
        {
            result[result_index] = arcsin;
            i += 5;
            result_index++;
            continue;
        }
        if (i < (len - 5) && input[i] == 'a' && input[i + 1] == 'r' && input[i + 2] == 'c' && input[i + 3] == 'c' && input[i + 4] == 'o' && input[i + 5] == 's')
        {
            result[result_index] = arccos;
            i += 5;
            result_index++;
            continue;
        }
        if (i < (len - 4) && input[i] == 'a' && input[i + 1] == 'r' && input[i + 2] == 'c' && input[i + 3] == 't' && input[i + 4] == 'g')
        {
            result[result_index] = arctg;
            i += 4;
            result_index++;
            continue;
        }
        if (i < (len - 5) && input[i] == 'a' && input[i + 1] == 'r' && input[i + 2] == 'c' && input[i + 3] == 'c' && input[i + 4] == 't' && input[i + 5] == 'g')
        {
            result[result_index] = arcctg;
            i += 5;
            result_index++;
            continue;
        }
        if (i < (len - 1) && input[i] == 's' && input[i + 1] == 'h')
        {
            result[result_index] = sh;
            i += 1;
            result_index++;
            continue;
        }
        if (i < (len - 1) && input[i] == 'c' && input[i + 1] == 'h')
        {
            result[result_index] = ch;
            i += 1;
            result_index++;
            continue;
        }
        if (i < (len - 2) && input[i] == 'e' && input[i + 1] == 'x' && input[i + 2] == 'p')
        {
            result[result_index] = exp;
            i += 2;
            result_index++;
            continue;
        }
        if (input[i] == 'f')
        {
            result[result_index] = spare;
            result_index++;
            continue;
        }
        int number_index = 0;
        int input_index = i;
        if ((isdigit(input[input_index]) || input[input_index] == '.') && input_index < len)
        {
            coefficents.push(new char[10]);
            char* num = coefficents.top();
            while ((isdigit(input[input_index]) || input[input_index] == '.') && input_index < len)
            {
                memcpy(num + strlen(num), &input[input_index], 1);
                input_index++;
                number_index++;
            }
            i += number_index - 1;
            result[result_index] = number;
            result_index++;
            continue;
        }
        switch (input[i])
        {
            case '(':
                result[result_index] = left;
                break;
            case 'x':
                result[result_index] = x;
                break;
            case '+':
                result[result_index] = plus;
                break;
            case '*':
                result[result_index] = mul;
                break;
            case ')':
                result[result_index] = right;
                break;
            case '-':
                result[result_index] = minus;
                break;
            case '^':
                result[result_index] = deg;
                break;
            case '/':
                result[result_index] = divis;
                break;
            default:
                std::cout << "Недопустимый ввод\n";
                exit(1);
                break;
        }
        result_index++;
    }
    result[result_index] = end;
}


