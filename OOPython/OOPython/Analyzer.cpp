#include "Analyzer.h"
#include "Expression.h"

const regex blockRegex[] = {
	 (regex)"^for\\s+([a-zA-Z_][0-9a-zA-Z_]*?)\\s+in\\s+([^:]+?)\\s*:\\s*$",
	 (regex)"^if\\s+([^:]+?)\\s*:\\s*$",
	 (regex)"^else\\s*:\\s*$",
	 (regex)"^while\\s+([^:]+?)\\s*:\\s*$",
	 (regex)"^def\\s+([a-zA-Z_][0-9a-zA-Z_]*?)\\s*\\((.*)\\)\\s*:\\s*$", 
	 (regex)"^print\\s+(.+?)\\s*(?:%\\s+\\(?\\s*(.+?)\\s*\\)?\\s*)?$",//%����Ҫ��һ���ո�
	 (regex)"^return\\s+(.+?)\\s*$",
	 (regex)"^continue\\s*$",
	 (regex)"^break\\s*$",
	 (regex)"^([^!=><]+?)\\s*=\\s*([^=].*)? *$"
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
	string ss = s;
	spaceHeadTail(ss);
	contain.push_back(ss);
	return -1;
}



//aandb
const vector<vector<string>> operators = {
	{ " or " },
	{ " and " },
	{ "not " },
	{ "==", "!=", ">=", "<=", ">", "<" },
	{ "|" },
	{ "^" },
	{ "&" },
	{ "<<", ">>" },
	{ "+", "-" },
	{ "*", "/" , "%"}
};

int isOper(const string& s, int pos) {
	int l = (int)s.size();
	for (int k = 5; k > 0; k--) {
		if (k + pos > l) {
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

int isOper(const string& s) {
	size_t l = operators.size();
	for (size_t i = 0; i < l; i++) {
		auto ii = operators[i];
		for (auto j : ii) {
			if (s.compare(j) == 0) {
				return (int)i;
			}
		}
	}
	return -1;
}

void spaceHeadTail(string & s) {
	int l = (int)s.size();
	for (int i = 0; i < l; i++) {
		if (s[i] != ' ') {
			s = s.substr(i, l - i);
			break;
		}
	}
	int ll = (int)s.size();
	for (int i = ll - 1; i >= 0; i--) {
		if (s[i] != ' ') {
			s = s.substr(0, i + 1);
			break;
		}
	}
}

string xiaochudanmufuhao(const string& ss) {
	string s = ss;
	size_t k = s.find('-');
	while (k != string::npos) {
		if (k == 0) {
			s.insert(0, 1, '0');
			k = s.find('-', 2);
			continue;
		}
		for (size_t i = k - 1; i >= 0; i--) {
			if (s[i] == ' ')
				continue;
			else if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9') || s[i] == '_' || s[i] == ')')) {
				s.insert(k, 1, '0');
				k = s.find('-', k + 2);
				break;
			}
			else {
				k = s.find('-', k + 1);
				break;
			}
		}
	}
	return s;
}

int getNumOfElem(const string& s) {
	const string bin[] = { "+", "-", "*", "/", "%", " and ", " or ", "&", "|", "^", ">", "<", ">=", "<=", "==", "!=", "<<", ">>" };
	const string una[] = { "not " };
	for (auto i : bin) {
		if (i == s) {
			return 2;
		}
	}
	for (auto i : una) {
		if (i == s) {
			return 1;
		}
	}
	return 0;
}

void string2stack(const string& s, stack<string>& res) {
	stack<string> container;
	int l = (int)s.size();
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
					//spaceHeadTail(op);
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

	while (!container.empty()) {
		res.push(container.top());
		container.pop();
	}
}

//����׺���ʽת��Ϊ��׺���ʽ
void mid2back(stack<string>& exp, stack<string>& OPND)
{
	int i = 0;
	stack<string> OPTR;   //�����ջ
						  //stack<string> OPND;   //����ջ


	while (!exp.empty())
	{
		if (isOper(exp.top()) == -1 && exp.top() != "(" && exp.top() != ")") // ������ֱ��д���׺���ʽ
		{
			OPND.push(exp.top());
		}
		else if (exp.top() == "(")    // �������������ñȽ�ֱ����ջ
			OPTR.push(exp.top());
		else if (exp.top() == ")")  // ���������Ž����Ӧ�����ź�Ĳ�������������ջ�еģ�ȫ��д���׺���ʽ
		{
			while (OPTR.top() != "(")
			{
				OPND.push(OPTR.top());
				OPTR.pop();
			}
			OPTR.pop(); // ����������ջ����׺���ʽ�в���С����
		}
		else if (isOper(exp.top()) != -1)
		{
			while (!OPTR.empty() && isOper(exp.top()) <= isOper(OPTR.top()))
			{
				// ��ǰ�Ĳ�����С�ڵ���ջ�������������ȼ�ʱ����ջ��������д�뵽��׺���ʽ���ظ��˹���
				OPND.push(OPTR.top());
				OPTR.pop();
			}
			OPTR.push(exp.top());    // ��ǰ������ջΪ�ջ��ߵ�ǰ���������ȼ�����ջ�������������ȼ������ò�������ջ
		}

		exp.pop();
	}

	while (!OPTR.empty()) // �����еĲ����������׺���ʽ
	{
		OPND.push(OPTR.top());
		OPTR.pop();
	}


	//���ò�����ջ���򼴿ɵõ���׺���ʽ
	/*while (!OPND.empty())
	{
	OPTR.push(OPND.top());
	OPND.pop();
	}*/
}

int bracketMatch(const string & s, char right, char left, int pos){
	int l = (int)s.size();
	int count = 1;
	for (int i = pos + 1; i < l; i++) {
		if (s[i] == right)
			count++;
		else if (s[i] == left)
			count--;
		if (count == 0) {
			return i;
		}
	}
	return -1;
}

int rbracketMatch(const string & s, char right, char left, int pos) {
	int l = (int)s.size();
	int count = 1;
	for (int i = pos - 1; i >= 0; i--) {
		if (s[i] == right)
			count++;
		else if (s[i] == left)
			count--;
		if (count == 0) {
			return i;
		}
	}
	return -1;
}

vector<string> commaCut(const string & s){
	vector<string> res;
	int l = (int)s.size();
	int start = 0;
	while (start < l) {
		for (int i = start; i < l; i++) {
			if (s[i] == ',') {
				string ss = s.substr(start, i - start);
				spaceHeadTail(ss);
				res.push_back(ss);
				start = i + 1;
				break;
			}
			else if (s[i] == '(') {
				int left = bracketMatch(s, '(', ')', i);
				i = left;
			}
			else if (s[i] == '[') {
				int left = bracketMatch(s, '[', ']', i);
				i = left;
			}
			if (i == l - 1) {
				string ss = s.substr(start);
				spaceHeadTail(ss);
				res.push_back(ss);
				start = i + 1;
			}
		}
	}
	return res;
}

pyExpression * back2exp(stack<string>& back) {
	string name = back.top();
	back.pop();
	int numOfElem = getNumOfElem(name);
	vector<pyExpression *> pe((size_t)numOfElem);
	for (int i = 0; i < numOfElem; i++) {
		pe[i] = back2exp(back);
	}
	return pyExpression::factory(name, pe);
}

pyExpression * str2exp(const string & s){
	const string ss = xiaochudanmufuhao(s);
	stack<string> middle;
	string2stack(ss, middle);
	stack<string> back;
	mid2back(middle, back);
	return back2exp(back);
}

vector<pyExpression*> str2exp_multi(const string & s){
	vector<pyExpression*> res;
	vector<string> cut = commaCut(s);
	for (auto i : cut) {
		res.push_back(str2exp(i));
	}
	return res;
}
