#include "Analyzer.h"
#include "Expression.h"

inline const pyObjectDataPtr pyUnaryOperator::work() const {
	return elem->work();
}

const pyObjectDataPtr pyNotOperator::work() const {

}

const pyObjectDataPtr pyNegativeOperator::work() const {
	const pyObjectDataPtr p = pyUnaryOperator::work();
	return -(*p);
}

const pyObjectDataPtr pySingleVariable::work() const{
	return (pyObjectDataPtr)dynamic_cast<const pyObjectData*> (&(*(pyBlock::findVar(name))));
}

const pyObjectDataPtr pyFuncVariable::work() const{
	pyFuncObjectPtr fop = (pyFuncObjectPtr)dynamic_cast<const pyObjectData*> (&(*(pyBlock::findVar(name))));
}
