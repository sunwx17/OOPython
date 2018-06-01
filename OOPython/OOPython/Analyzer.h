#ifndef ANALYZER_H
#define ANALYZER_H

#include <vector>
#include <regex>
using namespace std;

void removeSpace(string&);

int regexBreak(const string&, vector<string>&);

void multiVary(const string&, vector<string>&);



#endif // !ANALYZER_H
