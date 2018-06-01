#ifndef EXPREESION_H
#define EXPREESION_H
#include "Data.h"
#include "Function.h"

class pyExpression {
public:
	virtual pyObjectPtr work(Varmap&) const = 0;
};
//变量
class pyVariable : public pyExpression{
//protected:
	const string name;
public:
	pyVariable(const string s) :name(s) {};
	virtual pyObjectPtr work(Varmap&) const = 0;
	const string& getName() const;
};

class pyDataVariable : public pyVariable{
public:
	pyDataVariable(const string s) :pyVariable(s) {};
	pyObjectPtr work(Varmap&) const;
};

class pyFuncVariable : public pyVariable {
	vector<pyVariable*> elems;
public:
	pyFuncVariable(const string s, vector<pyVariable*> v) :pyVariable(s), elems(v) {};
	pyObjectPtr work(Varmap&) const;
};

//单目操作符
class pyUnaryOperator : public pyExpression {
	const pyVariable* const elem;
public:
	pyUnaryOperator(const pyVariable* const ele) : elem(ele) {}
	virtual pyObjectPtr work(Varmap&) const = 0;
};

class pyNotOperator : public pyUnaryOperator {
public:
	pyNotOperator(const pyVariable* const ele) : pyUnaryOperator(ele) {}
	pyObjectPtr work(Varmap&) const;
};

class pyNegativeOperator : public pyUnaryOperator {
public:
	pyNegativeOperator(const pyVariable* const ele) : pyUnaryOperator(ele) {}
	pyObjectPtr work(Varmap&) const;
};
//双目操作符
class pyBinaryOperator : public pyExpression {
protected:
	const pyVariable* const elemFront;
	const pyVariable* const elemBack;
public:
	pyBinaryOperator(const pyVariable* const front, const pyVariable* const back) : elemFront(front), elemBack(back) {}
	virtual pyObjectPtr work(Varmap&) const = 0;
};

class pyPlusOperator : public pyBinaryOperator {
public:
	pyPlusOperator(const pyVariable* const front, const pyVariable* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyMinusOperator : public pyBinaryOperator {
public:
	pyMinusOperator(const pyVariable* const front, const pyVariable* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyTimesOperator : public pyBinaryOperator {
public:
	pyTimesOperator(const pyVariable* const front, const pyVariable* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyDivideOperator : public pyBinaryOperator {
public:
	pyDivideOperator(const pyVariable* const front, const pyVariable* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

#endif // !EXPREESION_H
