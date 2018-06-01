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



#endif // !ANALYZER_H
