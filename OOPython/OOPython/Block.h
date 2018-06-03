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
	~pyBlock(){
		for (auto i : process) delete i;
	}
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
	pyForBlock(pyExpression* cv, pyExpression* cc) : cycleVariable(cv), cycleContain(cc) {}
	int work(int, Varmap&);
	~pyForBlock(){
		delete cycleVariable;
		delete cycleContain;
	}
};

class pyIfBlock : public pyBlock {
	pyExpression* condition;
public:
	pyIfBlock(pyExpression* con) : condition(con) {}
	int work(int, Varmap&);
	~pyIfBlock(){
		delete condition;
	}
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
	~pyWhileBlock(){
		delete condition;
	}
};

class pyDefBlock : public pyBlock {
	string name;
	int numOfElem;
	vector<string> elems;
	Varmap initVarmap;
public:
	pyDefBlock(const string s, vector<string> v) :name(s), elems(v), numOfElem((int)(v.size())) {}
	int work(int, Varmap&);
	pyObjectPtr call(Varmap&, vector<pyObjectPtr>&);
};

class pyPrintBlock : public pyBlock {
	pyExpression* bePrinted;
	string formatString;
	vector<pyExpression*> formatPrinted;
public:
	pyPrintBlock(pyExpression* tobePrinted) : bePrinted(tobePrinted) {}
	pyPrintBlock(const string &s, vector<pyExpression*> fp) : formatString(s), formatPrinted(fp) {}
	int work(int, Varmap&);
	~pyPrintBlock(){
		delete bePrinted;
		for (auto i : formatPrinted) delete i;
	}
};

class pyReturnBlock : public pyBlock {
	pyExpression* beReturned;
public:
	pyReturnBlock(pyExpression* tobeReturned) : beReturned(tobeReturned) {}
	int work(int, Varmap&);
	~pyReturnBlock(){
		delete beReturned;
	}
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
	vector<pyExpression*> beAssigned;
	vector<pyExpression*> assigner;
public:
	pyAssignBlock(vector<pyExpression*> front, vector<pyExpression*> back) : beAssigned(front), assigner(back) {}
	int work(int, Varmap&);
	~pyAssignBlock(){
		for (auto i : beAssigned)delete i;
		for (auto i : assigner) delete i;
	}
};

class pyExpBlock : public pyBlock {
	pyExpression * body;
public:
	pyExpBlock(pyExpression * pe) : body(pe) {}
	int work(int, Varmap&);
	~pyExpBlock(){
		delete body;
	}
};


#endif // !BLOCK_H
