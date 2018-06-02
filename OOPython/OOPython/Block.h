#ifndef BLOCK_H
#define BLOCK_H

#include "Data.h"
#include "Varmap.h"
#include "Expression.h"
#include "Analyzer.h"
#include <vector>

class pyBlock {
protected:
	vector<pyBlock*> process;
public:
	pyBlock() {};
	static pyBlock* factory(int, vector<string>&);
	int appendProcess(const string&, int);
	virtual int work(int, Varmap&) = 0;
};

class pyRootBlock : public pyBlock {
public:
	//static const pyObjectPtr findVar(const string&);
	pyRootBlock() {};
	int work(int, Varmap&);
	int lastWork(int, Varmap&);
};

class pyForBlock : public pyBlock {
	pyExpression* cycleVariable;
	pyExpression* cycleContain;
public:
	pyForBlock(pyExpression* cv, pyExpression* cc) : cycleVariable(cv), cycleContain(cv) {}
	int work(int, Varmap&);
};

class pyIfBlock : public pyBlock {
	pyExpression* condition;
public:
	pyIfBlock(pyExpression* con) : condition(con) {}
	int work(int, Varmap&);
};

class pyElseBlock : public pyBlock {
public:
	pyElseBlock() {};
	int work(int, Varmap&);
};

class pyWhileBlock : public pyBlock {
	pyExpression* condition;
public:
	pyWhileBlock(pyExpression* con) : condition(con) {}
	int work(int, Varmap&);
};

class pyDefBlock : public pyBlock {
	string name;
	int numOfElem;
	vector<string> elems;
	Varmap funcVarmap;
public:
	pyDefBlock(const string s, vector<string> v) :name(s), elems(v), numOfElem((int)(v.size())) {}
	int work(int, Varmap&);
	pyObjectPtr call(Varmap&, vector<pyObjectPtr>&);
};

class pyPrintBlock : public pyBlock {
	pyExpression* bePrinted;
public:
	pyPrintBlock(pyExpression* tobePrinted) : bePrinted(tobePrinted) {}
	int work(int, Varmap&);
};

class pyReturnBlock : public pyBlock {
	pyExpression* beReturned;
public:
	pyReturnBlock(pyExpression* tobeReturned) : beReturned(tobeReturned) {}
	int work(int, Varmap&);
};

class pyContinueBlock : public pyBlock {
public:
	pyContinueBlock() {}
	int work(int, Varmap&);
};

class pyBreakBlock : public pyBlock {
public:
	pyBreakBlock() {}
	int work(int, Varmap&);
};

class pyAssignBlock : public pyBlock {
	pyExpression* beAssigned;
	pyExpression* assigner;
public:
	pyAssignBlock(pyExpression* front, pyExpression* back) : beAssigned(front), assigner(back) {}
	int work(int, Varmap&);
};


#endif // !BLOCK_H
