#include "Analyzer.h"


regex blockRegex[] = {
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

