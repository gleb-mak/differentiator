#pragma once
#include "stack.h"
#include "node.h"

class Tree
{
public:
    Tree();
	~Tree();
    Tree(Node* root_);
    Node* Root();
    int Deep();
    void SetRoot(Node* root_);
    void SetDeep(int deep_);
    void IncDeep();
	void FillTree(Node* node, Stack<Rule*>& rules, Stack<char*>& coefficents);
private:
    Node* root;
    int deep;
	void FreeNode(Node* node);
};

