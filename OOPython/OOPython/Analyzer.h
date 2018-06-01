#ifndef ANALYZER_H
#define ANALYZER_H

#include "Data.h"
#include "Varmap.h"
#include "Expression.h"
#include <vector>
#include <regex>
using namespace std;

void removeSpace(string&);

int regexBreak(const string&, vector<string>&);

void multiVary(const string&, vector<string>&);

class pyBlock {
protected:
	static Varmap varmap;
	vector<pyBlock*> process;
public:
	pyBlock() {};
	static const pyObjectPtr findVar(const string&);
	static pyBlock* factory(int, vector<string>&);
	int appendProcess(const string&, int);
	virtual int work(int) = 0;
};

class pyRootBlock : public pyBlock{
public:
	pyRootBlock() {};
	int work(int);
};

class pyForBlock : public pyBlock {

};

class pyIfBlock : public pyBlock {
	pyExpression* condition;
public:
	pyIfBlock(pyExpression* con) : condition(con) {}
	int work(int);
};

class pyElseBlock : public pyBlock {
public:
	pyElseBlock() {};
	int work(int);
};

class pyWhileBlock : public pyBlock{
	pyExpression* condition;
public:
	pyWhileBlock(pyExpression* con) : condition(con) {}
	int work(int);
};

class pyDefBlock : public pyBlock {
	string name;
	int numOfElem;
	vector<string> elems;
	Varmap funcVarmap;
public:
	pyDefBlock(const string s, vector<string> v) :name(s), elems(v), numOfElem(v.size()) {
		for (auto i : v) {
			funcVarmap.assign(i, nullptr);
		}
	}
	int work(int);
	pyObjectPtr call(vector<pyObjectPtr>&);
};

class pyPrintBlock : public pyBlock {
	pyExpression* bePrinted;
public:
	pyPrintBlock(pyExpression* tobePrinted) : bePrinted(tobePrinted) {}
	int work(int);
};

class pyReturnBlock : public pyBlock{
	pyExpression* beReturned;
public:
	pyReturnBlock(pyExpression* tobeReturned) : beReturned(tobeReturned) {}
	int work(int);
};

class pyContinueBlock : public pyBlock {
public:
	pyContinueBlock() {}
	int work(int);
};

class pyBreakBlock : public pyBlock {
public:
	pyBreakBlock() {}
	int work(int);
};

class pyAssignBlock : public pyBlock {
	pyExpression* beAssigned;
	pyExpression* assigner;
public:
	pyAssignBlock(pyExpression* front, pyExpression* back) : beAssigned(front),assigner(back) {}
	int work(int);
};

#endif // !ANALYZER_H
