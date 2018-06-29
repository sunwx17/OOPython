#include "Block.h"
#include "Expression.h"
#include "Analyzer.h"

pyExpression * pyExpression::factory(const string& name, vector<pyExpression*> pe) {
	if (name == "+") return new pyPlusOperator(pe[1], pe[0]);
	else if (name == "-") return new pyMinusOperator(pe[1], pe[0]);
	else if (name == "*") return new pyTimesOperator(pe[1], pe[0]);
	else if (name == "/") return new pyDivideOperator(pe[1], pe[0]);
	else if (name == "%") return new pyModOperator(pe[1], pe[0]);
	else if (name == ">") return new pyBiggerOperator(pe[1], pe[0]);
	else if (name == "<") return new pySmallerOperator(pe[1], pe[0]);
	else if (name == ">=") return new pyBiggerEqualOperator(pe[1], pe[0]);
	else if (name == "<=") return new pySmallerEqualOperator(pe[1], pe[0]);
	else if (name == "==") return new pyEqualOperator(pe[1], pe[0]);
	else if (name == "!=") return new pyNotEqualOperator(pe[1], pe[0]);
	else if (name == " and ") return new pyAndOperator(pe[1], pe[0]);
	else if (name == " or ") return new pyOrOperator(pe[1], pe[0]);
	else if (name == "&") return new pyBitandOperator(pe[1], pe[0]);
	else if (name == "|") return new pyBitorOperator(pe[1], pe[0]);
	else if (name == "<<") return new pyLeftMoveOperator(pe[1], pe[0]);
	else if (name == ">>") return new pyRightMoveOperator(pe[1], pe[0]);
	//other
	else return pyVariable::factory(name);
}

pyVariable * pyVariable::factory(const string &name){
	size_t left = name.rfind(')');
	size_t sqleft = name.rfind(']');
	if (left == string::npos && sqleft == string::npos) {

		if (name == "False") {
			pyObjectPtr op((pyObject*)new pyObjectBool(false));
			return new pyVariable(op);
		}
		else if (name == "True") {
			pyObjectPtr op((pyObject*)new pyObjectBool(true));
			return new pyVariable(op);
		}
		bool isInt = true;
		bool isFloat = true;
		for (auto i : name) {
			if (!(i >= '0' && i <= '9')) {
				isInt = false;
				if (i != '.') {
					isFloat = false;
					break;
				}
			}
		}
		if (isInt) {
			pyObjectPtr op((pyObject*)new pyObjectInt(stoi(name.c_str())));
			return new pyVariable(op);
		}
		else if (isFloat) {
			pyObjectPtr op((pyObject*)new pyObjectFloat(stof(name)));
			return new pyVariable(op);
		}
		if ((name[0] == '\'' && name.back() == '\'') || (name[0] == '"' && name.back() == '"')) {
			string ss = name.substr(1, name.size() - 2);
			pyObjectPtr op((pyObject*)new pyObjectString(ss));
			return new pyVariable(op);
		}
		size_t pt = name.rfind('.');
		if (pt != string::npos) {
			string cla_n = name.substr(0, pt);
			string fun_n = name.substr(pt + 1);
			pyVariable* cla = pyVariable::factory(cla_n);
			
			return new pyPtVariable(cla, fun_n);
		}
		return new pyVariable(name);
	}
	else {
		if (left != string::npos && (sqleft == string::npos || sqleft < left)) {
			size_t right = rbracketMatch(name, ')', '(', (int)left);
			string funcName = name.substr(0, right);
			pyVariable* pfv = pyVariable::factory(funcName);
			string elems = name.substr(right + 1, left - right - 1);
			vector<string> elem_s = commaCut(elems);
			size_t pt = name.rfind('.', right);
			string cla = name.substr(0, pt);
			vector<pyExpression*> elem_v;
			elem_v.push_back(str2exp(cla));
			for (auto i : elem_s) {
				elem_v.push_back(str2exp(i));
			}
			return new pyFuncVariable(pfv, elem_v);
		}
		else if (sqleft != string::npos && (left == string::npos || left < sqleft)) {
			size_t sqright = rbracketMatch(name, ']', '[', (int)sqleft);
			string contName = name.substr(0, sqright);
			string sqelems = name.substr(sqright + 1, sqleft - sqright - 1);
			if (sqright != 0) {
				pyVariable* cont = pyVariable::factory(contName);
				pyVariable* posi = pyVariable::factory(sqelems);
				return new pySqrVariable(cont, posi);
			}
			vector<string> sqelem_s = commaCut(sqelems);
			vector<pyExpression*> sqelem_v;
			for (auto i : sqelem_s) {
				sqelem_v.push_back(str2exp(i));
			}
			return (pyVariable*)(new pyListVariable(sqelem_v));
		}
		/*size_t left, sqleft;
		string funcName, contName;
		pyVariable* pfv;
		if (right != string::npos) {
			left = bracketMatch(name, '(', ')', (int)right);
			funcName = name.substr(0, right);
			pfv = new pyVariable(funcName);
		}
		else if (sqright != string::npos) {
			sqleft = bracketMatch(name, '[', ']', (int)sqright);
			contName = name.substr(0, sqright);
		}
		do {

			if (sqright < right) {
				string sqelems = name.substr(sqright + 1, sqleft - sqright - 1);
				if (sqright != 0) {
					pyVariable* cont = pyVariable::factory(contName);
					pyVariable* posi = pyVariable::factory(sqelems);
					return new pySqrVariable(cont, posi);
				}
				vector<string> sqelem_s = commaCut(sqelems);
				vector<pyExpression*> sqelem_v;
				for (auto i : sqelem_s) {
					sqelem_v.push_back(str2exp(i));
				}
				return (pyVariable*)(new pyListVariable(sqelem_v));
			}
			else if (sqleft < left) {
				string elems = name.substr(right + 1, left - right - 1);
				vector<string> elem_s = commaCut(elems);
				vector<pyExpression*> elem_v;
				for (auto i : elem_s) {
					elem_v.push_back(str2exp(i));
				}
				pfv = new pyFuncVariable(pfv, elem_v);
				right = name.find('(', left + 1);
				left = name.find(')', left + 2);
			}
		} while (left != string::npos);
		return pfv;*/
		return nullptr;
	}
}

const string & pyVariable::getName() const {
	return name;
}

pyObjectPtr pyVariable::work(Varmap& varmap) const {
	if (tmpOp != nullptr)
		return tmpOp;
	else if (tmpV != nullptr)
		return tmpV->work(varmap);
	else
		return varmap.getValue(getName());
}

pyObjectPtr pyFuncVariable::work(Varmap& varmap) const {
	pyFuncObjectPtr fop = dynamic_pointer_cast<pyFuncObject> ((pyVariable::work(varmap)));
	vector<pyObjectPtr> elem_o;
	
	//tmpV->tmpV->work(varmap);
	//pyObjectPtr fopp = dynamic_pointer_cast<pyObject> ((pyVariable::work(varmap)));
	//elem_o.push_back(fopp);

	for (auto i : elems) {
		elem_o.push_back(i->work(varmap));
	}
	Varmap funcVarmap;
	return fop->call(funcVarmap, elem_o);
}

pyObjectPtr pySqrVariable::work(Varmap &varmap) const{
	pyObjectContainerPtr fop = dynamic_pointer_cast<pyObjectContainer> ((pyVariable::work(varmap)));
	pyObjectPtr op = posi->work(varmap);
	return fop->operator[](op);
}

pyObjectPtr pyPtVariable::work(Varmap & varmap) const{
	pyObjectDataPtr fop = dynamic_pointer_cast<pyObjectData> ((pyVariable::work(varmap)));
	return fop->opePT(member);
}

pyObjectPtr pyListVariable::work(Varmap & varmap) const{
	vector<pyObjectPtr> con;
	for (auto i : contain) {
		con.push_back(i->work(varmap));
	}
	return (pyObjectPtr)(pyObject*)(new pyObjectList(con));
}

inline pyObjectPtr pyUnaryOperator::work(Varmap& varmap) const {
	return elem->work(varmap);
}

pyObjectPtr pyNotOperator::work(Varmap& varmap) const {
	pyObjectDataPtr odp = dynamic_pointer_cast<pyObjectData> (pyUnaryOperator::work(varmap));
	pyObjectDataPtr odp2 = odp->operator!();
	pyObjectPtr op = dynamic_pointer_cast<pyObject>(odp2);
	return op;
}

pyObjectPtr pyNegativeOperator::work(Varmap& varmap) const {
	return dynamic_pointer_cast<pyObject>((dynamic_pointer_cast<pyObjectData> (pyUnaryOperator::work(varmap)))->operator-());
}

pyObjectPtr pyBinaryOperator::delegateWork(Varmap & varmap, const string & s) const{
	pyObjectDataPtr odpf = dynamic_pointer_cast<pyObjectData>(elemFront->work(varmap));
	pyObjectDataPtr odpb = dynamic_pointer_cast<pyObjectData>(elemBack->work(varmap));
	if(s.compare("+") == 0) return dynamic_pointer_cast<pyObject>((*odpf + *odpb));
	else if (s.compare("-") == 0) return dynamic_pointer_cast<pyObject>(*odpf - *odpb);
	else if (s.compare("*") == 0) return dynamic_pointer_cast<pyObject>(*odpf * *odpb);
	else if (s.compare("/") == 0) return dynamic_pointer_cast<pyObject>(*odpf / *odpb);
	else if (s.compare("%") == 0) return dynamic_pointer_cast<pyObject>(*odpf % *odpb);
	else if (s.compare(">") == 0) return dynamic_pointer_cast<pyObject>(*odpf > *odpb);
	else if (s.compare("<") == 0) return dynamic_pointer_cast<pyObject>(*odpf < *odpb);
	else if (s.compare(">=") == 0) return dynamic_pointer_cast<pyObject>(*odpf >= *odpb);
	else if (s.compare("<=") == 0) return dynamic_pointer_cast<pyObject>(*odpf <= *odpb);
	else if (s.compare("==") == 0) return dynamic_pointer_cast<pyObject>(*odpf == *odpb);
	else if (s.compare("!=") == 0) return dynamic_pointer_cast<pyObject>(*odpf != *odpb);
	else if (s.compare("and") == 0) return dynamic_pointer_cast<pyObject>(*odpf && *odpb);
	else if (s.compare("or") == 0) return dynamic_pointer_cast<pyObject>(*odpf || *odpb);
	else if (s.compare("&") == 0) return dynamic_pointer_cast<pyObject>(*odpf & *odpb);
	else if (s.compare("|") == 0) return dynamic_pointer_cast<pyObject>(*odpf | *odpb);
	else if (s.compare("<<") == 0) return dynamic_pointer_cast<pyObject>(*odpf << *odpb);
	else if (s.compare(">>") == 0) return dynamic_pointer_cast<pyObject>(*odpf >> *odpb);
	//other;
	else return nullptr;
}

pyObjectPtr pyPlusOperator::work(Varmap & varmap) const{
	return delegateWork(varmap, "+");
}

pyObjectPtr pyMinusOperator::work(Varmap & varmap) const {
	return delegateWork(varmap, "-");
}

pyObjectPtr pyTimesOperator::work(Varmap & varmap) const {
	return delegateWork(varmap, "*");
}

pyObjectPtr pyDivideOperator::work(Varmap & varmap) const {
	return delegateWork(varmap, "/");
}

pyObjectPtr pyModOperator::work(Varmap & varmap) const{
	return delegateWork(varmap, "%");
}

pyObjectPtr pyBiggerOperator::work(Varmap & varmap) const{
	return delegateWork(varmap, ">");
}

pyObjectPtr pyBiggerEqualOperator::work(Varmap & varmap) const{
	return delegateWork(varmap, ">=");
}

pyObjectPtr pySmallerOperator::work(Varmap & varmap) const{
	return delegateWork(varmap, "<");
}

pyObjectPtr pySmallerEqualOperator::work(Varmap & varmap) const{
	return delegateWork(varmap, "<=");
}

pyObjectPtr pyEqualOperator::work(Varmap & varmap) const{
	return delegateWork(varmap, "==");
}

pyObjectPtr pyNotEqualOperator::work(Varmap & varmap) const{
	return delegateWork(varmap, "!=");
}

pyObjectPtr pyAndOperator::work(Varmap & varmap) const{
	return delegateWork(varmap, "and");
}

pyObjectPtr pyOrOperator::work(Varmap & varmap) const{
	return delegateWork(varmap, "or");
}

pyObjectPtr pyBitandOperator::work(Varmap & varmap) const {
	return delegateWork(varmap, "&");
}

pyObjectPtr pyBitorOperator::work(Varmap & varmap) const {
	return delegateWork(varmap, "|");
}

pyObjectPtr pyLeftMoveOperator::work(Varmap & varmap) const {
	return delegateWork(varmap, "<<");
}

pyObjectPtr pyRightMoveOperator::work(Varmap & varmap) const {
	return delegateWork(varmap, ">>");
}