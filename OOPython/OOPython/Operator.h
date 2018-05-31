#ifndef OPERATOR_H
#define OPERATOR_H
#include "Data.h"

class pyBinaryOperator : public pyObject {
	pyObject* elemFront;
	pyObject* elemBack;
public:
	pyBinaryOperator(pyObject* front, pyObject* back) : elemFront(front), elemBack(back) {};
	virtual pyObject* work() = 0;
};


#endif // !OPERATOR_H
