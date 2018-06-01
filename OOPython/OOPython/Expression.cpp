#include "Block.h"
#include "Expression.h"

const string & pyVariable::getName() const {
	return name;
}

pyObjectPtr pyDataVariable::work(Varmap& varmap) const {
	return varmap.getValue(getName());
}

pyObjectPtr pyFuncVariable::work(Varmap& varmap) const {
	const pyFuncObjectPtr fop = (pyFuncObjectPtr)dynamic_cast<const pyFuncObject*> (&(*(varmap.getValue(getName()))));
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

}

pyObjectPtr pyNegativeOperator::work(Varmap& varmap) const {
	const pyObjectPtr p = pyUnaryOperator::work(varmap);
	return (pyObjectPtr)(&(*((dynamic_cast<const pyObjectData*> (&(*p)))->operator-())));
}

