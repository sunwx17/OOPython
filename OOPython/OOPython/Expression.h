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
/*class pyVariable : public pyExpression {
	//protected:
public:
	pyVariable() {};
	virtual pyObjectPtr work(Varmap&) const = 0;
	virtual const string& getName() const = 0;

};*/

class pyVariable : public pyExpression {
	const string name;
	pyObjectPtr tmpOp;
	pyVariable* tmpV;
public:
	pyVariable(const string s) : name(s) {};
	pyVariable(pyObjectPtr op) : tmpOp(op) {};
	pyVariable(pyVariable* op) : tmpV(op) {};
	pyObjectPtr work(Varmap&) const;
	const string& getName() const;
	static pyVariable* factory(const string&);
};

class pyFuncVariable : public pyVariable {
	vector<pyExpression*> elems;
public:
	pyFuncVariable(const string s, vector<pyExpression*> v) :pyVariable(s), elems(v) {};
	pyFuncVariable(pyObjectPtr op, vector<pyExpression*> v) :pyVariable(op), elems(v) {};
	pyFuncVariable(pyVariable* pv, vector<pyExpression*> v) :pyVariable(pv), elems(v) {};
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

class pyBiggerOperator : public pyBinaryOperator {
public:
	pyBiggerOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyBiggerEqualOperator : public pyBinaryOperator {
public:
	pyBiggerEqualOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pySmallerOperator : public pyBinaryOperator {
public:
	pySmallerOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pySmallerEqualOperator : public pyBinaryOperator {
public:
	pySmallerEqualOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyEqualOperator : public pyBinaryOperator {
public:
	pyEqualOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyNotEqualOperator : public pyBinaryOperator {
public:
	pyNotEqualOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyAndOperator : public pyBinaryOperator {
public:
	pyAndOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyOrOperator : public pyBinaryOperator {
public:
	pyOrOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

#endif // !EXPREESION_H
