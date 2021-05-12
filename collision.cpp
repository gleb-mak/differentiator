#include "collision.h"
#include <string.h>
#include <iostream>

void CatWithBrackets(Attr& result, Attr& expression, int priority_)
{
	if (expression.priority <= priority_ && expression.priority > 0)
	{
		strcat(result.val, "(");
		strcat(result.val, expression.val);
		strcat(result.val, ")");
		return;
	}
	strcat(result.val, expression.val);
}

void PlusCollision(Attr& sum, Attr& term1, Attr& term2)
{
	strcpy(sum.val, "");
	if (!strcmp(term1.val, "0"))
	{
		if (strcmp(term2.val, "0"))
		{
			sum.priority = term2.priority;
			strcat(sum.val, term2.val);
			return;
		}
		sum.priority = 0;
		strcat(sum.val, "0");
		return;
	}
	else
	{
		strcat(sum.val, term1.val);
		if (!strcmp(term2.val, "0"))
		{
			sum.priority = term1.priority;
			return;
		}
		sum.priority = 1;
		strcat(sum.val, "+");
		strcat(sum.val, term2.val);
	}
}

void MinusCollision(Attr& diff, Attr& minuend, Attr& subtrahend)
{
    strcpy(diff.val, "");
    if (!strcmp(minuend.val, "0"))
    {
        if (!strcmp(subtrahend.val, "0"))
        {
            diff.priority = 0;
            strcpy(diff.val, "0");
            return;
        }
        diff.priority = 1;
        strcpy(diff.val, "-");
        CatWithBrackets(diff, subtrahend, 1);
        return;
    }
    strcpy(diff.val, minuend.val);
    if (!strcmp(subtrahend.val, "0"))
    {
        diff.priority = 0;
        return;
    }
    diff.priority = 1;
    strcat(diff.val, "-");
    CatWithBrackets(diff, subtrahend, 1);
}

void MultiplyCollision(Attr& multiply, Attr& factor1_, Attr& factor2)
{
	// Attr factor1(factor1_.val, factor1_.priority);
    char sfactor1[10000] = { '\0' };
    Attr factor1 = {sfactor1, 0};
    factor1.priority = factor1_.priority;
    strcpy(factor1.val, factor1_.val);
    strcpy(multiply.val, "");
    if (!strcmp(factor1.val, "0") || !strcmp(factor2.val, "0"))
    {
        multiply.priority = 0;
        strcat(multiply.val, "0");
        return;
    }
    if (!strcmp(factor1.val, "1"))
    {
        multiply.priority = factor2.priority;
        strcat(multiply.val, factor2.val);
        return;
    }
    if (!strcmp(factor2.val, "1"))
    {
        multiply.priority = factor1.priority;
        strcat(multiply.val, factor1.val);
        return;
    }
    CatWithBrackets(multiply, factor1, 1);
    multiply.priority = 2;
    strcat(multiply.val, "*");
    CatWithBrackets(multiply, factor2, 1);
}

void DivisionCollision(Attr& fraction, Attr& numerator, Attr& denominator)
{
    strcpy(fraction.val, "");
    if (!strcmp(denominator.val, "0"))
    {
        std::cout << "error: division by zero";
        exit(1);
    }
    if (!strcmp(numerator.val, "0"))
    {
        fraction.priority = 0;
        strcpy(fraction.val, "0");
        return;
    }
    fraction.priority = 3;
    CatWithBrackets(fraction, numerator, 2);
    strcat(fraction.val, "/");
    CatWithBrackets(fraction, denominator, 2);
}

void DegreeCollision(Attr& power, Attr& base, Attr& degree)
{
    strcpy(power.val, "");
    if (!strcmp(base.val, "1"))
    {
        power.priority = 0;
        strcpy(power.val, "1");
        return;
    }
    if (!strcmp(base.val, "0"))
    {
        power.priority = 0;
        strcpy(power.val, "0");
        return;
    }
    if (!strcmp(degree.val, "0"))
    {
        power.priority = 0;
        strcpy(power.val, "1");
        return;
    }
    if (!strcmp(degree.val, "1"))
    {
        power.priority = base.priority;
        strcpy(power.val, base.val);
        return;
    }
    CatWithBrackets(power, base, 4);
    power.priority = 4;
    strcat(power.val, "^");
    CatWithBrackets(power, degree, 4);
}

void UnoMinusCollision(Attr& with_minus, Attr& expression)
{
    if (!strcmp(expression.val, "0"))
    {
        with_minus.priority = 0;
        strcpy(with_minus.val, "0");
        return;
    }
    with_minus.priority = 1;
    strcpy(with_minus.val, "-");
    CatWithBrackets(with_minus, expression, 4);
}


void InFunction(Attr& fun, Attr& parametr, const char* fun_name, bool need_clear)
{
    fun.priority = 0;
    if (need_clear)
    {
        strcpy(fun.val, "");
    }
    strcat(fun.val, fun_name);
    strcat(fun.val, "(");
    strcat(fun.val, parametr.val);
    strcat(fun.val, ")");
}

void FunctionCollision(Attr& result, Attr& internal_function, Attr& external_function, const char* begin, const char* end)
{
    strcpy(result.val, "");
    if (!strcmp(external_function.val, "0"))
    {
        result.priority = 0;
        strcpy(result.val, "0");
        return;
    }
    strcat(result.val, begin);
    strcat(result.val, internal_function.val);
    if (!strcmp(external_function.val, "1"))
    {
        result.priority = 0;
        strcat(result.val, end);
        return;
    }
    strcat(result.val, end);
    strcat(result.val, "*");
    CatWithBrackets(result, external_function, 1);
}


