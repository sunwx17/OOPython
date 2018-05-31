#include "Expression.h"

inline const pyObjectDataPtr pyUnaryOperator::work() const {
	return elem->work();
}

const pyObjectDataPtr pyNotOperator::work() const {

}

const pyObjectDataPtr pyNegativeOperator::work() const {
	const pyObjectDataPtr p = pyUnaryOperator::work();
	
}