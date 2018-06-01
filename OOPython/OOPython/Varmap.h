#ifndef VARMAP_H
#define VARMAP_H
#include "Data.h"
#include <map>

class Varmap {
	map<string, pyObjectPtr> table;
public:
	void assign(const string&, pyObjectPtr);
	pyObjectPtr getValue(const string&);
	void clear();
	~Varmap() {}
};

#endif // !VARMAP_H
