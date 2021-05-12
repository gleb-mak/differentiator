#pragma once

#include "node.h"

void CatWithBrackets(Attr& result, Attr& expression, int priority_);

void InFunction(Attr& fun, Attr& parametr, const char* fun_name, bool need_clear = true);

void PlusCollision(Attr& sum, Attr& term1, Attr& term2);

void MinusCollision(Attr& diff, Attr& minuend, Attr& subtrahend);

void MultiplyCollision(Attr& multiply, Attr& factor1_, Attr& factor2);

void DivisionCollision(Attr& fraction, Attr& numerator, Attr& denominator);

void DegreeCollision(Attr& power, Attr& base, Attr& degree);

void UnoMinusCollision(Attr& with_minus, Attr& expression);

void FunctionCollision(Attr& result, Attr& internal_function, Attr& external_function, const char* begin, const char* end);
