#ifndef ANALYZER_H
#define ANALYZER_H
#include "Data.h"
#include <vector>

/* "^for\\s+([a-zA-Z_][0-9a-zA-Z_]*?)\\s+in\\s+([^:]+?)\\s*:\\s*$"
 * "^if\\s+([^:]+?)\\s*:\\s*$"
 * "^else\\s*:\\s*$"
 * "^while\\s+([^:]+?)\\s*:\\s*$"
 * "^print\\s+(.+?)\\s*(?:%\\s*(.+?)\\s*)?$"
 * "^def\\s+([a-zA-Z_][0-9a-zA-Z_]*?)\\s*(\\(.*\\))\\s*:\\s*$"
 * "^return\\s+.+? *$"
 * "^continue\\s*$"
 * "^break\\s*$"
 * "^([a-zA-Z_][0-9a-zA-Z_\\s,]*?\\s*=\\s*(.*)? *)"
 */

class pyBlock {
protected:
	vector<pyBlock*> process;
public:
	pyBlock() {};
	virtual void appendProcess(const string&, int) = 0;
	virtual void work() = 0;
	virtual ~pyBlock() = 0;
};

class pyRootBlock : public pyBlock{
public:
	pyRootBlock() {};
	void appendProcess(const string&, int);
	void work();
};

class pyWhileBlock : public pyBlock{
	pyObject* condition;
public:
	pyWhileBlock() {};
	void appendProcess(const string&, int);
	void work();
};


#endif // !ANALYZER_H
