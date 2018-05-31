#include "Varmap.h"

void Varmap::assign(const string& s, pyObjectPtr p) {
	table[s] = p;
}

pyObjectPtr Varmap::getValue(const string& s) {
	if (table.find(s) != table.end())
		return table[s];
	return nullptr;
}