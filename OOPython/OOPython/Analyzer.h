#ifndef ANALYZER_H
#define ANALYZER_H

#include <vector>
#include <regex>
#include <stack>
#include <string>
using namespace std;

void removeSpace(string&);

int regexBreak(const string&, vector<string>&);

void multiVary(const string&, vector<string>&);

void string2stack(const string&, stack<string>&);

void postfix(stack<string>&, stack<string>&);

int bracketMatch(const string& s, char target, int pos);

#endif // !ANALYZER_H
