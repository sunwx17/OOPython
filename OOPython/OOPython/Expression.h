#ifndef EXPREESION_H
#define EXPREESION_H
#include "Data.h"
#include "Function.h"

class pyExpression {
public:
	virtual const pyObjectPtr work() const = 0;
};
//变量
class pyVariable : public pyExpression{
protected:
	const string name;
public:
	pyVariable(const string s) :name(s) {};
	virtual const pyObjectPtr work() const = 0;
};

class pySingleVariable : public pyVariable{
public:
	pySingleVariable(const string s) :pyVariable(s) {};
	const pyObjectPtr work() const;
};

class pyFuncVariable : public pyVariable {
	vector<pyVariable*> elems;
public:
	pyFuncVariable(const string s, vector<pyVariable*> v) :pyVariable(s), elems(v) {};
	const pyObjectPtr work() const;
};

//单目操作符
class pyUnaryOperator : public pyExpression {
	const pyVariable* const elem;
public:
	pyUnaryOperator(const pyVariable* const ele) : elem(ele) {}
	virtual const pyObjectPtr work() const = 0;
};

class pyNotOperator : public pyUnaryOperator {
public:
	pyNotOperator(const pyVariable* const ele) : pyUnaryOperator(ele) {}
	const pyObjectPtr work() const;
};

class pyNegativeOperator : public pyUnaryOperator {
public:
	pyNegativeOperator(const pyVariable* const ele) : pyUnaryOperator(ele) {}
	const pyObjectPtr work() const;
};
//双目操作符
class pyBinaryOperator : public pyExpression {
protected:
	const pyVariable* const elemFront;
	const pyVariable* const elemBack;
public:
	pyBinaryOperator(const pyVariable* const front, const pyVariable* const back) : elemFront(front), elemBack(back) {}
	virtual const pyObjectPtr work() const = 0;
};

class pyPlusOperator : public pyBinaryOperator {
public:
	pyPlusOperator(const pyVariable* const front, const pyVariable* const back) : pyBinaryOperator(front, back) {}
	const pyObjectPtr work() const;
};

class pyMinusOperator : public pyBinaryOperator {
public:
	pyMinusOperator(const pyVariable* const front, const pyVariable* const back) : pyBinaryOperator(front, back) {}
	const pyObjectPtr work() const;
};

class pyTimesOperator : public pyBinaryOperator {
public:
	pyTimesOperator(const pyVariable* const front, const pyVariable* const back) : pyBinaryOperator(front, back) {}
	const pyObjectPtr work() const;
};

class pyDivideOperator : public pyBinaryOperator {
public:
	pyDivideOperator(const pyVariable* const front, const pyVariable* const back) : pyBinaryOperator(front, back) {}
	const pyObjectPtr work() const;
};

#endif // !EXPREESION_H
