#pragma once

#include <string>
#include <iostream>
#include <vector>
#define stringify( name ) # name	//for changing enum to string type

using namespace std;

class Tnode
{
public:
	enum Type {
		PROGRAM,
		PROCEDURE,
		STMTLST,

		STMT_CALL,
		STMT_WHILE,
		STMT_IF,
		STMT_ASSIGN,

		VARIABLE,
		CONSTANT,

		EXPR_PLUS,
		EXPR_MINUS,
		EXPR_TIMES,

		NOTYPE
	};

	enum Link_Type {
		PARENT,
		CHILD,
		RIGHTSIB
	};

	Tnode();
	~Tnode();

	static Tnode *createNode(Type t, string n);

	static Tnode *createNode(int v);
	static bool createLink(Link_Type link, Tnode &fromNode, Tnode &toNode);
	Tnode getParent();
	Tnode getChild();
	Tnode getLeftSib();
	Tnode getRightSib();
	Type getType();
	string getName();
	int getValue();

	void printNode(); //for debugging

	

private:
	Tnode *parentNode;
	Tnode *childNode;
	Tnode *leftSibNode;
	Tnode *rightSibNode;
	Type type;
	string name;
	int value;

};

