#include "Block.h"
#include "Container.h"
/*const pyObjectPtr pyBlock::findVar(const string &s){
return varmap.getValue(s);
}*/

pyBlock* pyBlock::factory(int type, vector<string>& contain) {
	switch (type)
	{
	case(0)://for
		return new pyForBlock(str2exp(contain[0]), str2exp(contain[1]));
	case(1)://if
		return new pyIfBlock(str2exp(contain[0]));
	case(2)://else
		return new pyElseBlock();
	case(3)://while
		return new pyWhileBlock(str2exp(contain[0]));
	case(4)://def
		return new pyDefBlock(contain[0], commaCut(contain[1]));
	case(5)://print
		if (contain[1] == "")
			return new pyPrintBlock(str2exp(contain[0]));
		else
			return new pyPrintBlock(contain[0].substr(1, contain[0].size() - 2), str2exp_multi(contain[1]));
	case(6)://return
		return new pyReturnBlock(str2exp(contain[0]));
	case(7)://continue
		return new pyContinueBlock();
	case(8)://break
		return new pyBreakBlock();
	case(9)://=
		return new pyAssignBlock(str2exp_multi(contain[0]), str2exp_multi(contain[1]));
	case(-1)://expression
		return new pyExpBlock(str2exp(contain[0]));
	default:
		break;
	}
	return nullptr;
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

int pyRootBlock::lastWork(int workStatus, Varmap& varmap) {
	return process.back()->work(workStatus, varmap);
}

int pyForBlock::work(int workStatus, Varmap & varmap){
	const string& cvn = (dynamic_cast<pyVariable*>(cycleVariable))->getName();
	pyObjectContainerPtr ocp = dynamic_pointer_cast<pyObjectContainer>(cycleContain->work(varmap));
	for (pyObjectIteratorPtr i = ocp->begin(); *i != *ocp->end(); (*i)++) {
		varmap.assign(cvn, **i);
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


int pyIfBlock::work(int workStatus, Varmap& varmap) {
	pyObjectDataPtr cond = dynamic_pointer_cast<pyObjectData>(condition->work(varmap));
	if (cond->operator bool()) {
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
	pyObjectDataPtr cond = dynamic_pointer_cast<pyObjectData>(condition->work(varmap));
	while (cond->operator bool()) {
		for (auto i : process) {
			workStatus = i->work(workStatus, varmap);
			if (workStatus == 2)
				break;
			else if (workStatus == 3)
				return 1;
			else if (workStatus == 4 || workStatus == 5)
				return workStatus;
		}
		cond = dynamic_pointer_cast<pyObjectData>(condition->work(varmap));
	}
	return 1;
}

int pyDefBlock::work(int workStatus, Varmap& varmap) {
	pyFuncObjectPtr fop(new pyFuncObject(this));
	varmap.assign(name, fop);
	initVarmap.copy(varmap);
	return 1;
}

pyObjectPtr pyDefBlock::call(Varmap& varmap, vector<pyObjectPtr>& elems_in) {
	varmap.copy(initVarmap);
	for (int i = 0; i < numOfElem; i++) {
		varmap.assign(elems[i], elems_in[i]);
	}
	int workStatus = 1;
	for (auto i : process) {
		workStatus = i->work(workStatus, varmap);
		if (workStatus == 4) {
			pyObjectPtr ret = varmap.getValue("__return__");
			varmap.clear();
			return ret;
		}
		//else if (workStatus == 5)
	}
	varmap.clear();
	return nullptr;
}



int pyPrintBlock::work(int workStatus, Varmap& varmap) {
	if (bePrinted != nullptr) {
		((bePrinted->work(varmap)))->print();
	}
	else {
		auto it = formatPrinted.begin();
		size_t l = formatString.size();
		for (size_t i = 0; i < l; i++){
			if (formatString[i] == '%') {
				(*it)->work(varmap)->print();
				i++;
				it++;
			}
			else {
				cout << formatString[i];
			}
		}
	}
	cout << endl;
	return 1;
}

int pyReturnBlock::work(int workStatus, Varmap& varmap) {
	pyObjectPtr retop = beReturned->work(varmap);
	varmap.assign("__return__", retop);
	return 4;
}

int pyContinueBlock::work(int workStatus, Varmap& varmap) {
	return 2;
}

int pyBreakBlock::work(int workStatus, Varmap& varmap) {
	return 3;
}

int pyAssignBlock::work(int workStatus, Varmap& varmap) {
	int l = (int)beAssigned.size();
	for (int i = 0; i < l; i++) {
		const string& s = (dynamic_cast<pyVariable*> (beAssigned[i]))->getName();
		if (!s.empty()) {
			pyObjectPtr back = assigner[i]->work(varmap);
			varmap.assign(s, back);
		}
		else {
			dynamic_cast<pySqrVariable *>(beAssigned[i])->assign(varmap) = assigner[i]->work(varmap);
		}
	}
	return 1;
}

int pyExpBlock::work(int workStatus, Varmap &varmap){
	body->work(varmap);
	return 1;
}
