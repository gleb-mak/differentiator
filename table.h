#pragma once

enum ActionType {SHIFT, REDUCE, ACCEPT};

struct Literal
{
	char name;
	bool is_term;
	bool is_begin;
	int index;
};

class Rule
{
public:
	Rule(Literal left_, Literal right_[], int size_, int index_);
	Literal Left();
	Literal* Right();
	int Size();
	int Index();
private:
	Literal left;
	Literal* right;
	int size;
	int index;
};

class Action
{
public:
	Action();
	Action(ActionType type_, int state_, Rule* rule_);
	ActionType Type();
	int State();
	Rule* getRule();
private:
	ActionType type;
	int state;
	Rule* rule;
};

template <class T>
class Table
{
public:
	Table(int num_of_state_, int num_of_term_);
	~Table();
	T* Get(int state, Literal term);
	void Set(int state, Literal& term, T* value);
private:
	int num_of_state;
	int num_of_term;
	T*** table;
};
