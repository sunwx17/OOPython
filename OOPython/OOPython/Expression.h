#ifndef EXPREESION_H
#define EXPREESION_H
#include "Data.h"

class pyExpression {
public:
	virtual const pyObjectDataPtr work() const = 0;
};

class pyVariable : public pyExpression{
private:
	const string name;
public:
	pyVariable(const string s) :name(s) {};
	const pyObjectDataPtr work() const;
};

class pyUnaryOperator : public pyExpression {
	const pyVariable* const elem;
public:
	pyUnaryOperator(const pyVariable* const ele) : elem(ele) {}
	virtual const pyObjectDataPtr work() const = 0;
};

class pyNotOperator : public pyUnaryOperator {
public:
	pyNotOperator(const pyVariable* const ele) : pyUnaryOperator(ele) {}
	const pyObjectDataPtr work() const;
};

class pyNegativeOperator : public pyUnaryOperator {
public:
	pyNegativeOperator(const pyVariable* const ele) : pyUnaryOperator(ele) {}
	const pyObjectDataPtr work() const;
};

class pyBinaryOperator : public pyExpression {
protected:
	const pyVariable* const elemFront;
	const pyVariable* const elemBack;
public:
	pyBinaryOperator(const pyVariable* const front, const pyVariable* const back) : elemFront(front), elemBack(back) {}
	virtual const pyObjectDataPtr work() const = 0;
};

class pyPlusOperator : public pyBinaryOperator {
public:
	pyPlusOperator(const pyVariable* const front, const pyVariable* const back) : pyBinaryOperator(front, back) {}
	const pyObjectDataPtr work() const;
};


#endif // !EXPREESION_H
