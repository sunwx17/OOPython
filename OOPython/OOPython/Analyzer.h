#ifndef ANALYZER_H
#define ANALYZER_H

#include <vector>
#include <regex>
#include <stack>
using namespace std;

void removeSpace(string&);

int regexBreak(const string&, vector<string>&);

void multiVary(const string&, vector<string>&);

void string2stack(const string&, stack<string>&);


#endif // !ANALYZER_H
