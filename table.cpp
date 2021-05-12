#include "table.h"

Rule::Rule(Literal left_, Literal right_[], int size_, int index_) :
	left(left_), right(right_), size(size_), index(index_) {}

Literal Rule::Left()
{
	return left;
}

Literal* Rule::Right()
{
	return right;
}

int Rule::Size()
{
	return size;
}

int Rule::Index()
{
	return index;
}

Action::Action()
{
	state = 0;
}

Action::Action(ActionType type_, int state_, Rule* rule_) :
	type(type_), state(state_), rule(rule_) {}

ActionType Action::Type()
{
	return type;
}

int Action::State()
{
	return state;
}

Rule* Action::getRule()
{
	return rule;
}

template <class T>
Table<T>::Table(int num_of_state_, int num_of_term_) :
	num_of_state(num_of_state_), num_of_term(num_of_term_)
{
	table = new T** [num_of_state];
	for (int i = 0; i < num_of_state; ++i)
	{
		table[i] = new T* [num_of_term];
		for (int j = 0; j < num_of_term; ++j)
		{
			table[i][j] = nullptr;
		}
	}
}

template <class T>
Table<T>::~Table()
{
	for (int i = 0; i < num_of_state; ++i)
	{
		for (int j = 0; j < num_of_term; ++j)
		{
			delete table[i][j];
		}
		delete[] table[i];
	}
	delete[] table;
}

template <class T>
T* Table<T>::Get(int state, Literal term)
{
	return table[state][term.index];
}

template <class T>
void Table<T>::Set(int state, Literal& term, T* value)
{
	table[state][term.index] = value;
}

template class Table<Action>;
template class Table<int>;
