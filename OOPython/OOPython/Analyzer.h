#ifndef ANALYZER_H
#define ANALYZER_H
#include "Data.h"
#include <vector>
#include <regex>
using namespace std;

int regexBreak(const string&, vector<string>&);

void multiVary(const string&, vector<string>&);

class pyBlock {
protected:
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
//	string name;
//	vector<pyObject*> parameter;
};

class pyPrintBlock : public pyBlock {

};

class pyReturnBlock : public pyBlock{

};

class pyContinueBlock : public pyBlock {
public:
	pyContinueBlock() {}
	int work(int);
};

#endif // !ANALYZER_H
