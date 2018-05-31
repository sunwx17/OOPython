#ifndef ANALYZER_H
#define ANALYZER_H

#include "Data.h"
#include "Varmap.h"
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
	pyObject* condition;
public:
	pyIfBlock(pyObject* con) : condition(con) {}
	int work(int);
};

class pyElseBlock : public pyBlock {
public:
	pyElseBlock() {};
	int work(int);
};

class pyWhileBlock : public pyBlock{
	pyObject* condition;
public:
	pyWhileBlock(pyObject* con) : condition(con) {}
	int work(int);
};

class pyDefBlock : public pyBlock {

};

class pyPrintBlock : public pyBlock {
	pyObject* bePrinted;
public:
	pyPrintBlock(pyObject* tobePrinted) : bePrinted(tobePrinted) {}
	int work(int);
};

class pyReturnBlock : public pyBlock{
	pyObject* beReturned;
public:
	pyReturnBlock(pyObject* tobeReturned) : beReturned(tobeReturned) {}
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
	pyObject* beAssigned;
	pyObject* assigner;
public:
	pyAssignBlock(pyObject* front, pyObject* back) : beAssigned(front),assigner(back) {}
	int work(int);
};

#endif // !ANALYZER_H
