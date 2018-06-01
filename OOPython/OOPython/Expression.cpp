#include "Analyzer.h"
#include "Expression.h"

const string & pyVariable::getName() const {
	return name;
}

const pyObjectPtr pyDataVariable::work(Varmap& varmap) const {
	return varmap.getValue(getName());
}

const pyObjectPtr pyFuncVariable::work(Varmap& varmap) const {
	pyFuncObjectPtr fop = (pyFuncObjectPtr)dynamic_cast<const pyFuncObject*> (&(*(varmap.getValue(getName()))));
	vector<pyObjectPtr> elem_o;
	for (auto i : elems) {
		elem_o.push_back(i->work(varmap));
	}
	return fop->call(elem_o);
}


inline const pyObjectPtr pyUnaryOperator::work(Varmap& varmap) const {
	return elem->work(varmap);
}

const pyObjectPtr pyNotOperator::work(Varmap& varmap) const {

}

const pyObjectPtr pyNegativeOperator::work(Varmap& varmap) const {
	const pyObjectPtr p = pyUnaryOperator::work(varmap);
	return (pyObjectPtr)(&(*((dynamic_cast<const pyObjectData*> (&(*p)))->operator-())));
}

