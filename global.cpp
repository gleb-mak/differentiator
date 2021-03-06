#include "table.h"
#include "global.h"

Literal minus = {'-', true, false, 0};
Literal left = {'(', true, false, 1};
Literal sin = {'s', true, false, 2};
Literal cos = {'c', true, false, 3};
Literal ln = {'l', true, false, 4};
Literal ctg = {'1', true, false, 5};
Literal arcsin = {'2', true, false, 6};
Literal arccos = {'3', true, false, 7};
Literal arctg = {'4', true, false, 8};
Literal arcctg = {'5', true, false, 9};
Literal sh = {'6', true, false, 10};
Literal ch = {'7', true, false, 11};
Literal exp = {'8', true, false, 12};
Literal spare = {'9', true, false, 13};
Literal number = {'a', true, false, 14};
Literal x = {'x', true, false, 15};
Literal tg = {'t', true, false, 16};
Literal end = {'$', true, false, 17};
Literal plus = {'+', true, false, 18};
Literal mul = {'*', true, false, 19};
Literal divis = {'/', true, false, 20};
Literal deg = {'^', true, false, 21};
Literal right = {')', true, false, 22};
Literal S = {'S', false, true, 23};
Literal E = {'E', false, false, 24};
Literal T = {'T', false, false, 25};
Literal F = {'F', false, false, 26};
Literal K = {'K', false, false, 27};
Literal G = {'G', false, false, 28};
Literal right0[1] = {E};
Literal right1[3] = {E, plus, T};
Literal right2[3] = {E, minus, T};
Literal right3[1] = {T};
Literal right4[3] = {T, mul, F};
Literal right5[3] = {T, divis, F};
Literal right6[1] = {F};
Literal right7[3] = {F, deg, K};
Literal right8[1] = {K};
Literal right9[2] = {minus, G};
Literal right10[1] = {G};
Literal right11[3] = {left, E, right};
Literal right12[4] = {sin, left, E, right};
Literal right13[4] = {cos, left, E, right};
Literal right14[4] = {ln, left, E, right};
Literal right15[4] = {ctg, left, E, right};
Literal right16[4] = {arcsin, left, E, right};
Literal right17[4] = {arccos, left, E, right};
Literal right18[4] = {arctg, left, E, right};
Literal right19[4] = {arcctg, left, E, right};
Literal right20[4] = {sh, left, E, right};
Literal right21[4] = {ch, left, E, right};
Literal right22[4] = {exp, left, E, right};
Literal right23[4] = {spare, left, E, right};
Literal right24[4] = {tg, left, E, right};
Literal right25[1] = {number};
Literal right26[1] = {x};

Rule rule0(S, right0, 1, 0);
Rule rule1(E, right1, 3, 1);
Rule rule2(E, right2, 3, 2);
Rule rule3(E, right3, 1, 3);
Rule rule4(T, right4, 3, 4);
Rule rule5(T, right5, 3, 5);
Rule rule6(T, right6, 1, 6);
Rule rule7(F, right7, 3, 7);
Rule rule8(F, right8, 1, 8);
Rule rule9(K, right9, 2, 9);
Rule rule10(K, right10, 1, 10);
Rule rule11(G, right11, 3, 11);
Rule rule12(G, right12, 4, 12);
Rule rule13(G, right13, 4, 13);
Rule rule14(G, right14, 4, 14);
Rule rule15(G, right15, 4, 15);
Rule rule16(G, right16, 4, 16);
Rule rule17(G, right17, 4, 17);
Rule rule18(G, right18, 4, 18);
Rule rule19(G, right19, 4, 19);
Rule rule20(G, right20, 4, 20);
Rule rule21(G, right21, 4, 21);
Rule rule22(G, right22, 4, 22);
Rule rule23(G, right23, 4, 23);
Rule rule24(G, right24, 4, 24);
Rule rule25(G, right25, 1, 25);
Rule rule26(G, right26, 1, 26);

