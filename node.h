#pragma once
#include "stack.h"
#include "table.h"

struct Attr
{
	char* val;
	int priority;
};

class Node
{
public:
    Node();
	Node(Rule* rule_);
	~Node();
	void Initialize(Literal& val_, Node* parent_, Rule* rule_ = nullptr);
	void SetChilds(Rule* rule_);
    void SetVal(Literal& val_);
    void SetParent(Node* parent_);
	void SetRule(Rule* rule_);
    void SetDeep(int deep_);
	void SetAttr(Stack<char*>& coeff);
    Literal& Val();
	Node* Child(int index);
	Attr& AttrN();
	Attr& AttrD();
    int Deep();
    void AddChild(Node* child);
	Stack<Node*>* Childs();
	int ChildsNumber();
	bool IsParent();
private:
	Attr attr_n;
	Attr attr_d;
    Literal val;
	Rule* rule;
    int deep;
    Node* parent;
    Stack<Node*>* childs;
};
