#include "Analyzer.h"


const regex blockRegex[] = {
	 (regex)"^for\\s+([a-zA-Z_][0-9a-zA-Z_]*?)\\s+in\\s+([^:]+?)\\s*:\\s*$",
	 (regex)"^if\\s+([^:]+?)\\s*:\\s*$",
	 (regex)"^else\\s*:\\s*$",
	 (regex)"^while\\s+([^:]+?)\\s*:\\s*$",
	 (regex)"^def\\s+([a-zA-Z_][0-9a-zA-Z_]*?)\\s*(\\(.*\\))\\s*:\\s*$",
	 (regex)"^print\\s+(.+?)\\s*(?:%\\s*\\(?\\s*(.+?)\\s*\\)?\\s*)?$",
	 (regex)"^return\\s+(.+?)\\s*$",
	 (regex)"^continue\\s*$",
	 (regex)"^break\\s*$",
	 (regex)"^([a-zA-Z_][0-9a-zA-Z_\\s,]*?)\\s*=\\s*(.*)? *$"
};

void removeSpace(string& s) {
	int index = 0;
	if (!s.empty())
		while ((index = (int)s.find(' ', index)) != string::npos)
			s.erase(index, 1);
}

int regexBreak(const string& s, vector<string>& contain) {
	for (int i = 0; i < 10; i++) {
		smatch sm;
		if (regex_match(s, sm, blockRegex[i])) {
			for (unsigned k = 1; k < sm.size(); k++) {
				contain.push_back(sm.str(k));
			}
			return i;
		}
	}
	return -1;
}

void multiVary(const string& s, vector<string>& contain) {
	string ss = s;
	removeSpace(ss);
	ss.push_back(',');
	regex e("[,]*(.+?)[,]+");
	smatch sm;
	while (regex_search(ss, sm, e)) {
		contain.push_back(sm.str(1));
		ss = sm.suffix().str();
	}
}

const vector<vector<string>> operators = {
	{ "or" },
	{ "and" },
	{ "not" },
	{ "==", "!=", ">=", "<=", ">", "<" },
	{ "|" },
	{ "^" },
	{ "&" },
	{ "<<", ">>" },
	{ "+", "-" },
	{ "*", "/" }
};

string oper_s{ "\\+|-|\\*|/|<<|>>|&|\\^|\\||==|!=|>=|<=|>|<|\\bnot\\b|\\band\\b|\\bor\\b" };

int isOper(const string& s, int pos) {
	int l = s.size();
	for (int k = 5; k >= 0; k--) {
		if (k + pos >= l) {
			continue;
		}
		string ss = s.substr(pos, k);
		for (auto i : operators) {
			for (auto j : i) {
				if (ss.compare(j) == 0) {
					return k;
				}
			}
		}
	}
	return -1;
}

void spaceHeadTail(string & s) {
	int l = s.size();
	for (int i = 0; i < l; i++) {
		if (s[i] != ' ') {
			s = s.substr(i, l - i);
			break;
		}
	}
	int ll = s.size();
	for (int i = ll - 1; i >= 0; i--) {
		if (s[i] != ' ') {
			s = s.substr(0, i + 1);
			break;
		}
	}
}

void string2stack(const string& s, stack<string>& container) {
	int l = s.size();
	int start = 0;
	while (start < l) {
		if (s[start] == ' ') {
			start++;
		}
		else if (s[start] == '(' || s[start] == ')') {
			container.push(s.substr(start, 1));
			start++;
		}
		else {
			int i = start;
			for (; i < l; i++) {
				bool flag = false;
				int opLen = isOper(s, i);
				if (opLen == -1) {
					if (s[i] == '(') {
						int count = 1;
						for (int j = i + 1; j < l; j++) {
							if (s[j] == '(')
								count++;
							else if (s[j] == ')')
								count--;
							if (count == 0) {
								i = j;
								break;
							}
						}
						if (flag)
							break;
					}
					else if (s[i] == ')') {
						string ss = s.substr(start, i - start);
						spaceHeadTail(ss);
						string left = s.substr(i, 1);
						spaceHeadTail(left);
						container.push(ss);
						container.push(left);
						start = i + 1;
						break;
					}
				}
				else {
					if (i > start) {
						string var = s.substr(start, i - start);
						spaceHeadTail(var);
						container.push(var);
					}
					string op = s.substr(i, opLen);
					spaceHeadTail(op);
					container.push(op);
					start = i + opLen;
					break;
				}
			}
			if (i >= l) {
				string ss = s.substr(start);
				spaceHeadTail(ss);
				container.push(ss);
				start = i;
				break;
			}
		}
	}
}