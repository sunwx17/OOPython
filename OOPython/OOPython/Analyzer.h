#ifndef ANALYZER_H
#define ANALYZER_H

#include <vector>
#include <regex>
#include <stack>
#include <string>

class pyExpression;
using namespace std;

void removeSpace(string&);

int regexBreak(const string&, vector<string>&);

int isOper(const string& s, int pos);

int isOper(const string& s);

void spaceHeadTail(string & s);

string xiaochudanmufuhao(const string& ss);

int getNumOfElem(const string& s);

void string2stack(const string&, stack<string>&);

void mid2back(stack<string>& exp, stack<string>& OPND);

int bracketMatch(const string& s, char right, char left, int pos);

vector<string> commaCut(const string& s);

pyExpression * back2exp(stack<string>& back);

pyExpression * str2exp(const string & s);

vector<pyExpression *> str2exp_multi(const string & s);



#endif // !ANALYZER_H
