#ifndef EXPREESION_H
#define EXPREESION_H
#include "Data.h"
#include "Function.h"
#include "Varmap.h"

class pyExpression {
public:
	virtual pyObjectPtr work(Varmap&) const = 0;
	static pyExpression* factory(const string&, vector<pyExpression*>);
};
//变量
class pyVariable : public pyExpression {
	//protected:
public:
	pyVariable() {};
	virtual pyObjectPtr work(Varmap&) const = 0;
	virtual const string& getName() const = 0;
	static pyVariable* factory(const string&);
};

class pyDataVariable : public pyVariable {
	const string name;
	pyObjectPtr tmpOp;
public:
	pyDataVariable(const string s) : name(s) {};
	pyDataVariable(pyObjectPtr op) : tmpOp(op) {};
	pyDataVariable(pyDataVariable* op) : pyDataVariable(*op){
		delete op;
	};
	pyObjectPtr work(Varmap&) const;
	const string& getName() const;
};

class pyFuncVariable : public pyDataVariable {
	vector<pyExpression*> elems;
public:
	pyFuncVariable(const string s, vector<pyExpression*> v) :pyDataVariable(s), elems(v) {};
	pyFuncVariable(pyObjectPtr op, vector<pyExpression*> v) :pyDataVariable(op), elems(v) {};
	pyFuncVariable(pyDataVariable* op, vector<pyExpression*> v) :pyDataVariable(op), elems(v) {};
	pyObjectPtr work(Varmap&) const;
};

//单目操作符
class pyUnaryOperator : public pyExpression {
	const pyExpression* const elem;
public:
	pyUnaryOperator(const pyExpression* const ele) : elem(ele) {}
	virtual pyObjectPtr work(Varmap&) const = 0;
};

class pyNotOperator : public pyUnaryOperator {
public:
	pyNotOperator(const pyExpression* const ele) : pyUnaryOperator(ele) {}
	pyObjectPtr work(Varmap&) const;
};

class pyNegativeOperator : public pyUnaryOperator {
public:
	pyNegativeOperator(const pyExpression* const ele) : pyUnaryOperator(ele) {}
	pyObjectPtr work(Varmap&) const;
};
//双目操作符
class pyBinaryOperator : public pyExpression {
protected:
	const pyExpression* const elemFront;
	const pyExpression* const elemBack;
	pyObjectPtr delegateWork(Varmap&, const string&) const;
public:
	pyBinaryOperator(const pyExpression* const front, const pyExpression* const back) : elemFront(front), elemBack(back) {}
	virtual pyObjectPtr work(Varmap&) const = 0;
};

class pyPlusOperator : public pyBinaryOperator {
public:
	pyPlusOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyMinusOperator : public pyBinaryOperator {
public:
	pyMinusOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyTimesOperator : public pyBinaryOperator {
public:
	pyTimesOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyDivideOperator : public pyBinaryOperator {
public:
	pyDivideOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

#endif // !EXPREESION_H
