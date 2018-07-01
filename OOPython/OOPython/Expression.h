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
	virtual ~pyExpression() {}
};
//变量
class pyVariable : public pyExpression {
protected:
	const string name;
	pyObjectPtr tmpOp = nullptr;
	pyVariable* tmpV = nullptr;
public:
	pyVariable() {};
	pyVariable(const string s);
	pyVariable(pyObjectPtr op);
	pyVariable(pyVariable* op);
	pyObjectPtr work(Varmap&) const;
	const string& getName() const;
	static pyVariable* factory(const string&);
	~pyVariable();
};

class pyFuncVariable : public pyVariable {
	vector<pyExpression*> elems;
public:
	pyFuncVariable(const string s, vector<pyExpression*> v);
	pyFuncVariable(pyObjectPtr op, vector<pyExpression*> v);
	pyFuncVariable(pyVariable* pv, vector<pyExpression*> v);
	pyObjectPtr work(Varmap&) const;
	~pyFuncVariable();
};

class pySqrVariable : public pyVariable {
	pyExpression* posi;
public:
	pySqrVariable(const string s, pyExpression* v);
	pySqrVariable(pyObjectPtr op, pyExpression* v);
	pySqrVariable(pyVariable* pv, pyExpression* v);
	pyObjectPtr work(Varmap&) const;
	pyObjectPtr& assign(Varmap&) const;
	~pySqrVariable();
};

class pyPtVariable : public pyVariable {
	string member;
public:
	pyPtVariable(const string s, string v);
	pyPtVariable(pyObjectPtr op, string v);
	pyPtVariable(pyVariable* pv, string v);
	pyObjectPtr work(Varmap&) const;
};

class pyContainerVariable : public pyVariable {
protected:
	vector<pyExpression*> contain;
public:
	pyContainerVariable(vector<pyExpression*> v);
	pyObjectPtr work(Varmap&) const = 0;
	~pyContainerVariable();
};

class pyListVariable : public pyContainerVariable {
public:
	pyListVariable(vector<pyExpression*> v);
	pyObjectPtr work(Varmap&) const;
};

//单目操作符
class pyUnaryOperator : public pyExpression {
	const pyExpression* const elem;
public:
	pyUnaryOperator(const pyExpression* const ele);
	virtual pyObjectPtr work(Varmap&) const = 0;
	~pyUnaryOperator();
};

class pyNotOperator : public pyUnaryOperator {
public:
	pyNotOperator(const pyExpression* const ele);
	pyObjectPtr work(Varmap&) const;
};

class pyNegativeOperator : public pyUnaryOperator {
public:
	pyNegativeOperator(const pyExpression* const ele);
	pyObjectPtr work(Varmap&) const;
};
//双目操作符
class pyBinaryOperator : public pyExpression {
protected:
	const pyExpression* const elemFront;
	const pyExpression* const elemBack;
	pyObjectPtr delegateWork(Varmap&, const string&) const;
public:
	pyBinaryOperator(const pyExpression* const front, const pyExpression* const back);
	virtual pyObjectPtr work(Varmap&) const = 0;
	~pyBinaryOperator();
};

class pyPlusOperator : public pyBinaryOperator {
public:
	pyPlusOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyMinusOperator : public pyBinaryOperator {
public:
	pyMinusOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyTimesOperator : public pyBinaryOperator {
public:
	pyTimesOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyDivideOperator : public pyBinaryOperator {
public:
	pyDivideOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyModOperator : public pyBinaryOperator {
public:
	pyModOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyBiggerOperator : public pyBinaryOperator {
public:
	pyBiggerOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyBiggerEqualOperator : public pyBinaryOperator {
public:
	pyBiggerEqualOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pySmallerOperator : public pyBinaryOperator {
public:
	pySmallerOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pySmallerEqualOperator : public pyBinaryOperator {
public:
	pySmallerEqualOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyEqualOperator : public pyBinaryOperator {
public:
	pyEqualOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyNotEqualOperator : public pyBinaryOperator {
public:
	pyNotEqualOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyAndOperator : public pyBinaryOperator {
public:
	pyAndOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyOrOperator : public pyBinaryOperator {
public:
	pyOrOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyBitandOperator : public pyBinaryOperator {
public:
	pyBitandOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyBitorOperator : public pyBinaryOperator {
public:
	pyBitorOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyLeftMoveOperator : public pyBinaryOperator {
public:
	pyLeftMoveOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};

class pyRightMoveOperator : public pyBinaryOperator {
public:
	pyRightMoveOperator(const pyExpression* const front, const pyExpression* const back);
	pyObjectPtr work(Varmap&) const;
};



#endif // !EXPREESION_H
