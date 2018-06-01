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

/*const pyObjectPtr pyBlock::findVar(const string &s){
	return varmap.getValue(s);
}*/

pyBlock* pyBlock::factory(int type, vector<string>& contain) {
	switch (type)
	{
	case(0)://for

	case(1)://if

	case(2)://else

	case(3)://while

	case(4)://def

	case(5)://print

	case(6)://return

	case(7)://continue

	case(8)://break

	case(9)://=

	case(-1)://expression

	default:
		break;
	}
}

int pyBlock::appendProcess(const string& s, int numOfTab) {
	if (numOfTab > 0) {
		pyBlock* lastProcess = process.back();
		return lastProcess->appendProcess(s, numOfTab - 1);
	}
	else {
		vector<string> contain;
		int type = regexBreak(s, contain);
		pyBlock* nextProcess = pyBlock::factory(type, contain);
		process.push_back(nextProcess);
		return type;
	}
}

/*
 * workStatus表:
 * 1 : 正常工作
 * 2 : continue
 * 3 : break
 * 4 : return
 * 5 : exit
 * 6 : if为真，接下来else不执行
 */

int pyRootBlock::work(int workStatus, Varmap& varmap) {
	for (auto i : process) {
		workStatus = i->work(workStatus, varmap);
		if (workStatus == 6)
			return 6;
	}
	return 1;
}

//int pyForBlock::work(int workStatus, Varmap& varmap) {
//}

int pyIfBlock::work(int workStatus, Varmap& varmap) {
	pyObjectPtr cond = condition->work(varmap);
	if ((bool)cond) {
		for (auto i : process) {
			workStatus = i->work(workStatus, varmap);
			if (workStatus >= 2 && workStatus <= 5)
				return workStatus;
		}
		return 6;
	}
	return 1;
}

int pyElseBlock::work(int workStatus, Varmap& varmap) {
	if (workStatus == 6)
		return 1;
	else {
		for (auto i : process) {
			workStatus = i->work(workStatus, varmap);
			if (workStatus >= 2 && workStatus <= 5)
				return workStatus;
		}
		return 1;
	}		
}

int pyWhileBlock::work(int workStatus, Varmap& varmap) {
	int workStatus;
	pyObjectPtr cond = condition->work(varmap);
	while ((bool)cond) {
		for (auto i : process) {
			workStatus = i->work(workStatus, varmap);
			if (workStatus == 2) 
				break;
			else if (workStatus == 3) 
				return 1;
			else if (workStatus == 4 || workStatus == 5) 
				return workStatus;
		}
	}
	return 1;
}

int pyDefBlock::work(int workStatus, Varmap& varmap) {
	pyFuncObjectPtr fop(new pyFuncObject(this));
	varmap.assign(name, fop);
	return 1;
}

pyObjectPtr pyDefBlock::call(vector<pyObjectPtr>& elems_in){
	for (int i = 0; i < numOfElem; i++) {
		funcVarmap.assign(elems[i], elems_in[i]);
	}
	int workStatus = 1;
	for (auto i : process) {
		workStatus = i->work(workStatus, funcVarmap);
		if (workStatus == 4) 
			return funcVarmap.getValue("__return__");
		//else if (workStatus == 5)
	}
	return nullptr;
}



int pyPrintBlock::work(int workStatus, Varmap& varmap) {
	bePrinted->work(varmap)->print();
	return 1;
}

int pyReturnBlock::work(int workStatus, Varmap& varmap) {
	pyObjectPtr retop = beReturned->work(varmap);
	varmap.assign("__return__", retop);
	return 1;
}

int pyContinueBlock::work(int workStatus, Varmap& varmap) {
	return 2;
}

int pyBreakBlock::work(int workStatus, Varmap& varmap) {
	return 3;
}

int pyAssignBlock::work(int workStatus, Varmap& varmap) {
	const string& s = (dynamic_cast<pyVariable*> (beAssigned))->getName();
	pyObjectPtr back = assigner->work(varmap);
	varmap.assign(s, back);
	return 1;
}