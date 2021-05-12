#include "node.h"
#include <cctype>
#include <string.h>
#include <iostream>
#include "number.h"
#include "collision.h"

Node::Node() :
    childs(new Stack<Node*>())
{
    attr_n = {nullptr, 0};
    attr_d = {nullptr, 0};
    parent = nullptr;
}

Node::Node(Rule* rule_) :
    childs(new Stack<Node*>())
{
    attr_n = {nullptr, 0};
    attr_d = {nullptr, 0};
    rule = rule_;
    val = rule_->Left();
    for (int i = 0; i < rule->Size(); ++i)
    {

        Node* child = new Node();
        child->Initialize(rule->Right()[i], this);
        childs->push(child);
    }
}

Node::~Node()
{
	delete childs;
	delete[] attr_n.val;
	delete[] attr_d.val;
}

void Node::SetChilds(Rule* rule)
{
	for (int i = 0; i < rule->Size(); ++i)
    {
        Node* child = new Node();
		child->Initialize(rule->Right()[i], this);
        childs->push(child);
    }
}

void Node::Initialize(Literal& val_, Node* parent_, Rule* rule_)
{
	val = val_;
	parent = parent_;
	rule = rule_;
}

void Node::SetVal(Literal& val_)
{
	val = val_;
}

void Node::SetParent(Node* parent_)
{
	parent = parent_;
}

void Node::SetRule(Rule* rule_)
{
	rule = rule_;
}

void Node::SetAttr(Stack<char*>& coefficents)
{
	if (val.is_term)
	{
		switch (val.name)
		{
			case 'x':
			{
				attr_n.priority = 0;
				attr_n.val = new char[2];
				char tmp_n[] = "x";
				strcpy(attr_n.val, tmp_n);
				attr_d.priority = 0;
				attr_d.val = new char[2];
				char tmp_d[] = "1";
				strcpy(attr_d.val, tmp_d);
				break;
			}
			case 'a':
			{
				attr_n.priority = 0;
				attr_n.val = new char[strlen(coefficents.top()) + 1];
				strcpy(attr_n.val, coefficents.top());
				delete[] coefficents.top();
				coefficents.pop();
				attr_d.priority = 0;
				attr_d.val = new char[2];
				char tmp_d[] = "0";
				strcpy(attr_d.val, tmp_d);
				break;
			}
		}
		return;
	}
	int index = rule->Index();
	if (index == 3 || index == 6 || index == 8 || index == 10 || index == 25 || index == 26)
	{
		attr_n.priority = Child(0)->AttrN().priority;
		attr_d.priority = Child(0)->AttrD().priority;
		attr_n.val = new char[strlen(Child(0)->AttrN().val) + 10];
		attr_d.val = new char[strlen(Child(0)->AttrD().val) + 10];
		strcpy(attr_n.val, Child(0)->AttrN().val);
		strcpy(attr_d.val, Child(0)->AttrD().val);
	}
	else
	{
		if (index <= 24 && index >= 12)
		{
			attr_n.val = new char[10 + strlen(Child(2)->AttrN().val)];
		}
		switch (index)
		{
			case 13:
			{
				InFunction(attr_n, Child(2)->AttrN(), "cos");
				attr_d.priority = 1;
				attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
				FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "-sin(", ")");
				break;
			}
			case 12:
			{
				InFunction(attr_n, Child(2)->AttrN(), "sin");
				attr_d.priority = 0;
				attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
				FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "cos(", ")");
				break;
			}
			case 15:
            {
				InFunction(attr_n, Child(2)->AttrN(), "ctg");
                attr_d.priority = 1;
                attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
				FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "-1/sin(", ")^2");
                break;
            }
			case 14:
            {
                InFunction(attr_n, Child(2)->AttrN(), "ln");
                attr_d.priority = 0;
                attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
				if (Child(2)->AttrN().priority)
				{	
					FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "1/(", ")");
					break;
				}
				FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "1/", "");
                break;
            }
			case 16:
            {
                InFunction(attr_n, Child(2)->AttrN(), "arcsin");
                attr_d.priority = 0;
                attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
                FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "1/(1-(", ")^2)^0.5");
                break;
            }
			case 17:
            {
                InFunction(attr_n, Child(2)->AttrN(), "arccos");
                attr_d.priority = 1;
                attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
                FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "-1/(1-(", ")^2)^0.5");
                break;
            }
			case 18:
            {
                InFunction(attr_n, Child(2)->AttrN(), "arctg");
                attr_d.priority = 0;
                attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
                FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "1/(1+(", ")^2)");
                break;
            }
			case 19:
            {
                InFunction(attr_n, Child(2)->AttrN(), "arcctg");
                attr_d.priority = 1;
                attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
                FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "-1/(1+(", ")^2)");
                break;
            }
			case 20:
            {
                InFunction(attr_n, Child(2)->AttrN(), "sh");
                attr_d.priority = 0;
                attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
                FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "ch(", ")");
                break;
            }
			case 21:
            {
                InFunction(attr_n, Child(2)->AttrN(), "ch");
                attr_d.priority = 0;
                attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
                FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "sh(", ")");
                break;
            }
			case 22:
            {
                InFunction(attr_n, Child(2)->AttrN(), "exp");
                attr_d.priority = 0;
                attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
                FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "exp(", ")");
                break;
            }
			case 23:
            {
                InFunction(attr_n, Child(2)->AttrN(), "f");
                attr_d.priority = 0;
                attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
                FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "f'(", ")");
                break;
            }
			case 24:
            {
                InFunction(attr_n, Child(2)->AttrN(), "tg");
                attr_d.priority = 0;
                attr_d.val = new char[30 + strlen(Child(2)->AttrD().val) + strlen(Child(2)->AttrN().val)];
                FunctionCollision(attr_d, Child(2)->AttrN(), Child(2)->AttrD(), "1/cos(", ")^2");
                break;
            }
			case 1:
				attr_n.val = new char[strlen(Child(0)->AttrN().val) + strlen(Child(2)->AttrN().val) + 10];
				PlusCollision(attr_n, Child(0)->AttrN(), Child(2)->AttrN());
				attr_d.val = new char[strlen(Child(0)->AttrD().val) + strlen(Child(2)->AttrD().val) + 10];
				PlusCollision(attr_d, Child(0)->AttrD(), Child(2)->AttrD());
				break;
			case 2:
                attr_n.val = new char[strlen(Child(0)->AttrN().val) + strlen(Child(2)->AttrN().val) + 10];
                MinusCollision(attr_n, Child(0)->AttrN(), Child(2)->AttrN());
                attr_d.val = new char[strlen(Child(0)->AttrD().val) + strlen(Child(2)->AttrD().val) + 10];
                MinusCollision(attr_d, Child(0)->AttrD(), Child(2)->AttrD());
                break;
			case 4:
			{
				attr_n.val = new char[strlen(Child(0)->AttrN().val) + strlen(Child(2)->AttrN().val) + 10];
				MultiplyCollision(attr_n, Child(0)->AttrN(), Child(2)->AttrN());
				attr_d.val = new char[strlen(Child(0)->AttrN().val) + strlen(Child(2)->AttrD().val) + strlen(Child(0)->AttrD().val) + strlen(Child(2)->AttrN().val) + 10];
				char sterm1[10000], sterm2[10000];
				Attr term1 = {sterm1, 0};
				Attr term2 = {sterm2, 0};
				MultiplyCollision(term1, Child(0)->AttrN(), Child(2)->AttrD());
				MultiplyCollision(term2, Child(0)->AttrD(), Child(2)->AttrN());
				PlusCollision(attr_d, term1, term2);
				break;
			}
			case 5:
            {
                attr_n.val = new char[strlen(Child(0)->AttrN().val) + strlen(Child(2)->AttrN().val) + 10];
                DivisionCollision(attr_n, Child(0)->AttrN(), Child(2)->AttrN());
                attr_d.val = new char[strlen(Child(0)->AttrN().val) + 2*strlen(Child(2)->AttrD().val) + strlen(Child(0)->AttrD().val) + 2*strlen(Child(2)->AttrN().val) + 50];
				char sterm1[10000], sterm2[10000], sminus[10000], sdenominator[10000];
				char sdegree[] = "2";
                Attr term1 = {sterm1, 0};
                Attr term2 = {sterm2, 0};
				Attr minus = {sminus, 0};
				Attr degree = {sdegree, 0};
				Attr denominator = {sdenominator, 0};
                MultiplyCollision(term1, Child(0)->AttrN(), Child(2)->AttrD());
                MultiplyCollision(term2, Child(0)->AttrD(), Child(2)->AttrN());
                MinusCollision(minus, term2, term1);
				DegreeCollision(denominator, Child(2)->AttrN(), degree);
				DivisionCollision(attr_d, minus, denominator);
                break;
            }
			case 7:
            {
                attr_n.val = new char[strlen(Child(0)->AttrN().val) + strlen(Child(2)->AttrN().val) + 10];
                DegreeCollision(attr_n, Child(0)->AttrN(), Child(2)->AttrN());
                attr_d.val = new char[strlen(Child(0)->AttrN().val) + 2*strlen(Child(2)->AttrD().val) + strlen(Child(0)->AttrD().val) + strlen(Child(2)->AttrN().val) + 500];
				if (IsNumber(Child(0)->AttrN().val))
				{
					char slog[10000];
					Attr log = {slog, 0};
					DegreeCollision(log, Child(0)->AttrN(), Child(2)->AttrN());
					strcat(log.val, "*ln(");
					strcat(log.val, Child(0)->AttrN().val);
					strcat(log.val, ")");
					MultiplyCollision(attr_d, log, Child(2)->AttrD());
					break;
				}
				if (IsNumber(Child(2)->AttrN().val))
				{
					char sdeg[10000];
					Attr deg = {sdeg, 0};
					strcpy(attr_d.val, Child(2)->AttrN().val);
					attr_d.priority = Child(2)->AttrN().priority;
					DecNumber(Child(2)->AttrN().val);
					DegreeCollision(deg, Child(0)->AttrN(), Child(2)->AttrN());
					MultiplyCollision(attr_d, attr_d, deg);
					MultiplyCollision(attr_d, attr_d, Child(0)->AttrD());
					break;
				}
				char slog1[10000], slog2[10000], sexponent[10000], sdivision[10000], smul1[10000], smul2[10000], ssum[10000];
                Attr log1 = {slog1, 0};
				Attr log2 = {slog2, 0};
                Attr exponent = {sexponent, 0};
                Attr division = {sdivision, 0};
                Attr mul1 = {smul1, 0};
				Attr mul2 = {smul2, 0};
                Attr sum = {ssum, 0};
				strcpy(log1.val, Child(2)->AttrN().val);
				log1.priority = 2;
				strcat(log1.val, "*");
				strcpy(log2.val , "");
                InFunction(log1, Child(0)->AttrN(), "ln", false);
				InFunction(log2, Child(0)->AttrN(), "ln", false);
				DivisionCollision(division, Child(2)->AttrN(), Child(0)->AttrN());
				MultiplyCollision(mul1, division, Child(0)->AttrD());
				MultiplyCollision(mul2, Child(2)->AttrD(), log2);
				PlusCollision(sum, mul1, mul2);
                FunctionCollision(attr_d, log1, sum, "exp(", ")");
                break;
            }
			case 9:
			{
				attr_n.val = new char[10 + strlen(Child(1)->AttrN().val)];
				attr_d.val = new char[10 + strlen(Child(1)->AttrD().val)];
				UnoMinusCollision(attr_n, Child(1)->AttrN());
				UnoMinusCollision(attr_d, Child(1)->AttrD());
				break;
			}
			case 11:
			{
				attr_n.priority = Child(1)->AttrN().priority;
				attr_d.priority = Child(1)->AttrD().priority;
				attr_n.val = new char[10 + strlen(Child(1)->AttrN().val)];
				strcpy(attr_n.val, Child(1)->AttrN().val);
				attr_d.val = new char[10 + strlen(Child(1)->AttrD().val)];
				strcpy(attr_d.val, Child(1)->AttrD().val);
				break;
			}
		}
	}
}

Literal& Node::Val()
{
	return val;
}

Attr& Node::AttrN()
{
	return attr_n;
}

Attr& Node::AttrD()
{
	return attr_d;
}

void Node::AddChild(Node* child)
{
	childs->push(child);
}

int Node::Deep()
{
	return deep;
}

void Node::SetDeep(int d)
{
	deep = d;
}

int Node::ChildsNumber()
{
	return childs->size();
}

bool Node::IsParent()
{
	if (childs->empty())
	{
		return false;
	}
	return true;
}

Node* Node::Child(int index)
{
	return childs->get(index);
}

Stack<Node*>* Node::Childs()
{
	return childs;
}
