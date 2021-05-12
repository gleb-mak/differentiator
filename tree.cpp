#include "tree.h"

Tree::Tree()
{
	deep = 0;
}

Tree::~Tree()
{
	FreeNode(root);
}

void Tree::FreeNode(Node* node)
{
	if (node->IsParent())
	{
		for (int i = 0; i < node->ChildsNumber(); ++i)
		{
			FreeNode(node->Child(i));
		}
	}
	delete node;
}

Tree::Tree(Node* root_):
	root(root_)
{
	deep = 1;
}

Node* Tree::Root()
{
	return root;
}

void Tree::SetRoot(Node* root_)
{
	root = root_;
}

void Tree::SetDeep(int d)
{
	deep = d;
}

void Tree::IncDeep()
{
	deep++;
}

int Tree::Deep()
{
	return deep;
}

void Tree::FillTree(Node* node, Stack<Rule*>& rules, Stack<char*>& coefficents)
{
    for (int j = node->Childs()->size() - 1; j >= 0; j--)
    {
        if (node->Child(j)->Val().is_term)
        {
			node->Child(j)->SetAttr(coefficents);
            continue;
        }
        node->Child(j)->SetRule(rules.top());
        node->Child(j)->SetChilds(rules.pop());
        FillTree(node->Child(j), rules, coefficents);
    }
	node->SetAttr(coefficents);
}
