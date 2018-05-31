#ifndef VARMAP_H
#define VARMAP_H
#include "Data.h"
#include <map>

class Varmap {
	map<string, pyObjectPtr> table;
public:
	void assign(const string&, pyObjectPtr);
	pyObjectPtr getValue(const string&);
	~Varmap() {}
};

#endif // !VARMAP_H
