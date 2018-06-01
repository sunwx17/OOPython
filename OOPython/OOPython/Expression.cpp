#include "Analyzer.h"
#include "Expression.h"


const pyObjectPtr pySingleVariable::work() const {
	return pyBlock::findVar(name);
}

const pyObjectPtr pyFuncVariable::work() const {
	pyFuncObjectPtr fop = (pyFuncObjectPtr)dynamic_cast<const pyFuncObject*> (&(*(pyBlock::findVar(name))));
	vector<pyObjectPtr> elem_o;
	for (auto i : elems) {
		elem_o.push_back(i->work());
	}
	return fop->call(elem_o);
}


inline const pyObjectPtr pyUnaryOperator::work() const {
	return elem->work();
}

const pyObjectPtr pyNotOperator::work() const {

}

const pyObjectPtr pyNegativeOperator::work() const {
	const pyObjectPtr p = pyUnaryOperator::work();
	return (pyObjectPtr)(&(*((dynamic_cast<const pyObjectData*> (&(*p)))->operator-())));
}
