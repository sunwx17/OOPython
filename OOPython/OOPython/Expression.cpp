#include "Block.h"
#include "Expression.h"

const string & pyVariable::getName() const {
	return name;
}

pyObjectPtr pyDataVariable::work(Varmap& varmap) const {
	return varmap.getValue(getName());
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
