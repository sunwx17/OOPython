#ifndef EXPREESION_H
#define EXPREESION_H
#include "Data.h"
#include "Function.h"
#include "Varmap.h"
#include "Container.h"

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
protected:
	const string name;
	pyObjectPtr tmpOp;
	pyVariable* tmpV;
public:
	pyVariable() {};
	pyVariable(const string s) : name(s) {};
	pyVariable(pyObjectPtr op) : tmpOp(op) {};
	pyVariable(pyVariable* op) : tmpV(op) {};
	pyObjectPtr work(Varmap&) const;
	const string& getName() const;
	static pyVariable* factory(const string&);
	~pyVariable(){
		if (tmpV != nullptr) delete tmpV;
	}
};

class pyFuncVariable : public pyVariable {
	vector<pyExpression*> elems;
public:
	pyFuncVariable(const string s, vector<pyExpression*> v) :pyVariable(s), elems(v) {};
	pyFuncVariable(pyObjectPtr op, vector<pyExpression*> v) :pyVariable(op), elems(v) {};
	pyFuncVariable(pyVariable* pv, vector<pyExpression*> v) :pyVariable(pv), elems(v) {};
	pyObjectPtr work(Varmap&) const;
	~pyFuncVariable(){
		for (auto i : elems) delete i;
	}
};

class pySqrVariable : public pyVariable {
	pyExpression* posi;
public:
	pySqrVariable(const string s, pyExpression* v) :pyVariable(s), posi(v) {};
	pySqrVariable(pyObjectPtr op, pyExpression* v) :pyVariable(op), posi(v) {};
	pySqrVariable(pyVariable* pv, pyExpression* v) :pyVariable(pv), posi(v) {};
	pyObjectPtr work(Varmap&) const;
	pyObjectPtr& assign(Varmap&) const;
	~pySqrVariable(){
		delete posi;
	}
};

class pyPtVariable : public pyVariable {
	string member;
public:
	pyPtVariable(const string s, string v) :pyVariable(s), member(v) {};
	pyPtVariable(pyObjectPtr op, string v) :pyVariable(op), member(v) {};
	pyPtVariable(pyVariable* pv, string v) :pyVariable(pv), member(v) {};
	pyObjectPtr work(Varmap&) const;
	pyVariable* getPv() const;
	~pyPtVariable() {};
};

class pyContainerVariable : public pyVariable {
protected:
	vector<pyExpression*> contain;
public:
	pyContainerVariable(vector<pyExpression*> v) :contain(v) {};
	pyObjectPtr work(Varmap&) const = 0;
	~pyContainerVariable(){
		for (auto i : contain) delete i;
	}
};

class pyListVariable : public pyContainerVariable {
public:
	pyListVariable(vector<pyExpression*> v) :pyContainerVariable(v) {};
	pyObjectPtr work(Varmap&) const;
	~pyListVariable() {};
};

//单目操作符
class pyUnaryOperator : public pyExpression {
	const pyExpression* const elem;
public:
	pyUnaryOperator(const pyExpression* const ele) : elem(ele) {}
	virtual pyObjectPtr work(Varmap&) const = 0;
	~pyUnaryOperator(){
		delete elem;
	}
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
	~pyBinaryOperator(){
		delete elemFront;
		delete elemBack;
	}
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

class pyModOperator : public pyBinaryOperator {
public:
	pyModOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
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

class pyBitandOperator : public pyBinaryOperator {
public:
	pyBitandOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyBitorOperator : public pyBinaryOperator {
public:
	pyBitorOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyLeftMoveOperator : public pyBinaryOperator {
public:
	pyLeftMoveOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};

class pyRightMoveOperator : public pyBinaryOperator {
public:
	pyRightMoveOperator(const pyExpression* const front, const pyExpression* const back) : pyBinaryOperator(front, back) {}
	pyObjectPtr work(Varmap&) const;
};



#endif // !EXPREESION_H
