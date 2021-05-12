#include <string.h>
#include <cctype>
#include "stack.h"
#include "table.h"
#include "tree.h"
#include "to_pdf.h"
#include "global.h"
#include "parser.h"
#include "fill_tables.h"
#include <iostream>

int main()
{
	Stack<char*> coefficents;
	char input[100000];
	std::cin >> input;
	Literal* word = new Literal[strlen(input) + 2];
	Parser(word, input, coefficents);
	bool accepted = false;
	Stack<int> stack;
	Table<Action> actionTable(148, 24);
	Table<int> goToTable(148, 29);
	FillTables(actionTable, goToTable);
	stack.push(0);
	int inp_pos = 0;
	Stack<Rule*> rules;
	while (!accepted)
	{
		int st = stack.top();
		Literal term = word[inp_pos];
		Action* action = actionTable.Get(st, term);
		switch (action->Type())
        {
        case ACCEPT:
            accepted = true;
            break;
        case SHIFT:
			{
            inp_pos++;
            stack.push(action->State());
            break;
			}
        case REDUCE:
            Rule* rule = action->getRule();
			rules.push(rule);
            stack.pop(rule->Size());
            int transferState = *goToTable.Get(stack.top(), rule->Left());
            stack.push(transferState);
            break;
        }
	}
	Node* root = new Node(&rule0);
    Tree tree(root);
    tree.FillTree(root, rules, coefficents);
    std::cout << root->Child(0)->AttrN().val << "\t" << root->Child(0)->AttrD().val << "\n";
	ToPDF(root->Child(0)->AttrD().val);
	delete[] word;
	return 0;
}
