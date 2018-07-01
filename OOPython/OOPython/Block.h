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
	pyBlock() = default;
	static pyBlock* factory(int, vector<string>&);
	int appendProcess(const string&, int);
	virtual int work(int, Varmap&) = 0;
	virtual ~pyBlock(){
		for (auto i : process) delete i;
	}
};

class pyRootBlock : public pyBlock {
public:
	//static const pyObjectPtr findVar(const string&);
	pyRootBlock() = default;
	int work(int, Varmap&);
	int lastWork(int, Varmap&);
};

class pyForBlock : public pyBlock {
	pyExpression* cycleVariable;
	pyExpression* cycleContain;
public:
	pyForBlock(pyExpression* cv, pyExpression* cc);
	int work(int, Varmap&);
	~pyForBlock();
};

class pyIfBlock : public pyBlock {
	pyExpression* condition;
public:
	pyIfBlock(pyExpression* con);
	int work(int, Varmap&);
	~pyIfBlock();
};

class pyElseBlock : public pyBlock {
public:
	pyElseBlock() = default;
	int work(int, Varmap&);
};

class pyWhileBlock : public pyBlock {
	pyExpression* condition;
public:
	pyWhileBlock(pyExpression* con);
	int work(int, Varmap&);
	~pyWhileBlock();
};

class pyDefBlock : public pyBlock {
	string name;
	int numOfElem;
	vector<string> elems;
	Varmap initVarmap;
public:
	pyDefBlock(const string s, vector<string> v);
	int work(int, Varmap&);
	pyObjectPtr call(Varmap&, vector<pyObjectPtr>&);
};

class pyPrintBlock : public pyBlock {
	pyExpression* bePrinted = nullptr;
	string formatString;
	vector<pyExpression*> formatPrinted;
public:
	pyPrintBlock(pyExpression* tobePrinted);
	pyPrintBlock(const string &s, vector<pyExpression*> fp);
	int work(int, Varmap&);
	~pyPrintBlock();
};

class pyReturnBlock : public pyBlock {
	pyExpression* beReturned;
public:
	pyReturnBlock(pyExpression* tobeReturned);
	int work(int, Varmap&);
	~pyReturnBlock();
};

class pyContinueBlock : public pyBlock {
public:
	pyContinueBlock() = default;
	int work(int, Varmap&);
};

class pyBreakBlock : public pyBlock {
public:
	pyBreakBlock() = default;
	int work(int, Varmap&);
};

class pyAssignBlock : public pyBlock {
	vector<pyExpression*> beAssigned;
	vector<pyExpression*> assigner;
public:
	pyAssignBlock(vector<pyExpression*> front, vector<pyExpression*> back);
	int work(int, Varmap&);
	~pyAssignBlock();
};

class pyExpBlock : public pyBlock {
	pyExpression * body;
public:
	pyExpBlock(pyExpression * pe);
	int work(int, Varmap&);
	~pyExpBlock();
};


#endif // !BLOCK_H
