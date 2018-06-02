#include "Block.h"
#include "Expression.h"
#include "Analyzer.h"

pyExpression * pyExpression::factory(const string &name){
	int right = name.find('(');
	if (right == string::npos) {
		if (name == "False") {
			pyObjectPtr op((pyObject*)new pyObjectBool(false));
			return new pyDataVariable(op);
		}
		else if (name == "True") {
			pyObjectPtr op((pyObject*)new pyObjectBool(true));
			return new pyDataVariable(op);
		}
		bool isInt = true;
		bool isFloat = true;
		for (auto i : name) {
			if (!(i >= '0' && i <= '9')) {
				isInt = false;
				if (i != '.')
					isFloat = false;
			}
		}
		if (isInt) {
			pyObjectPtr op((pyObject*)new pyObjectInt(stoi(name.c_str())));
			return new pyDataVariable(op);
		}
		else if (isFloat) {
			pyObjectPtr op((pyObject*)new pyObjectFloat(stof(name)));
			return new pyDataVariable(op);
		}
		return new pyDataVariable(name);
	}
	else {
		int left = bracketMatch(name, ')', right);
		string funcName = name.substr(0, right);
		string elems = name.substr(right + 1, left - right - 1);
	}
}

const string & pyVariable::getName() const {
	return name;
}

pyObjectPtr pyDataVariable::work(Varmap& varmap) const {
	if (tmpOp == nullptr)
		return varmap.getValue(getName());
	else
		return tmpOp;
}

pyObjectPtr pyFuncVariable::work(Varmap& varmap) const {
	const pyFuncObjectPtr fop = (pyFuncObjectPtr)dynamic_cast<pyFuncObject*> ((varmap.getValue(getName())).get());
	vector<pyObjectPtr> elem_o;
	for (auto i : elems) {
		elem_o.push_back(i->work(varmap));
	}
	return fop->call(elem_o);
}


inline pyObjectPtr pyUnaryOperator::work(Varmap& varmap) const {
	return elem->work(varmap);
}

pyObjectPtr pyNotOperator::work(Varmap& varmap) const {
	return (pyObjectPtr)(pyObject*)(((dynamic_cast<pyObjectData*> (pyUnaryOperator::work(varmap).get()))->operator!()).get());
}

pyObjectPtr pyNegativeOperator::work(Varmap& varmap) const {
	return (pyObjectPtr)(pyObject*)(((dynamic_cast<pyObjectData*> (pyUnaryOperator::work(varmap).get()))->operator-()).get());
}

pyObjectPtr pyBinaryOperator::delegateWork(Varmap & varmap, const string & s) const{
	pyObjectDataPtr odpf = (pyObjectDataPtr)dynamic_cast<pyObjectData*>(elemFront->work(varmap).get());
	pyObjectDataPtr odpb = (pyObjectDataPtr)dynamic_cast<pyObjectData*>(elemBack->work(varmap).get());
	if(s.compare("+") == 0) return (pyObjectPtr)(pyObject*)(*odpf + *odpb).get();
	else if (s.compare("-") == 0) return (pyObjectPtr)(pyObject*)(*odpf + *odpb).get();
	else if (s.compare("*") == 0) return (pyObjectPtr)(pyObject*)(*odpf * *odpb).get();
	else if (s.compare("/") == 0) return (pyObjectPtr)(pyObject*)(*odpf / *odpb).get();
}

pyObjectPtr pyPlusOperator::work(Varmap & varmap) const{
	return delegateWork(varmap, "+");
}

pyObjectPtr pyMinusOperator::work(Varmap & varmap) const {
	return delegateWork(varmap, "-");
}

pyObjectPtr pyTimesOperator::work(Varmap & varmap) const {
	return delegateWork(varmap, "*");
}

pyObjectPtr pyDivideOperator::work(Varmap & varmap) const {
	return delegateWork(varmap, "/");
}
