#ifndef ANALYZER_H
#define ANALYZER_H

#define Ptr *

#include <vector>
#include <regex>
#include <stack>
#include <string>

class pyExpression;
using namespace std;

void removeSpace(string&);

int regexBreak(const string&, vector<string>&);

void multiVary(const string&, vector<string>&);

void string2stack(const string&, stack<string>&);

void postfix(stack<string>&, stack<string>&);

int bracketMatch(const string& s, char target, int pos);

vector<string> commaCut(const string& s);

pyExpression * str2exp(const string & s);

pyExpression * str2exp_multi(const string & s);



#endif // !ANALYZER_H
