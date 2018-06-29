//Data.cpp
#include "Data.h"
#include "Function.h"
//以下基础函数：operateInt、operateBool、operateFloat
bool operateBool(const float& one, const float& other, const char* ope, bool& answer) {
	int length = (int)strlen(ope);
	switch (length)
	{
	case 1:
		switch (ope[0])
		{
		case '>':
			answer = (one > other);
			return true;
		case '<':
			answer = (one < other);
			return true;
		default:
			return false;
		}
		break;
	case 2:
		if (ope == "==") {
			answer = (one == other);
			return true;
		}
		if (ope == "!=") {
			answer = (one != other);
			return true;
		}
		if (ope == ">=") {
			answer = (one >= other);
			return true;
		}
		if (ope == "<=") {
			answer = (one <= other);
			return true;
		}
		else{
			return false;
		}
		break;
	default:
		return false;
	}
	return true;
}

bool operateInt(const int& one, const int& other, const char* ope, int& answer) {
	int num = one;
	int length = (int)strlen(ope);
	switch (length)
	{
	case 1:
		switch (ope[0])
		{
		case '+':
			num += other;
			break;
		case '-':
			num -= other;
			break;
		case '*':
			num *= other;
			break;
		case '/':
			if (other != 0) {
				num /= other;
			}
			else {
				return false;
			}
			break;
		case '%':
			if (other != 0) {
				pyMod(one, other, num);
			}
			else {
				return false;
			}
			break;
		case '&':
			num = num & other;
			break;
		case '|':
			num = num | other;
			break;
		default:
			return false;
			break;
		}
		break;
	case 2:
		if (ope == ">>")
			num = num >> other;
		if (ope == "<<")
			num = num << other;
		break;
	default:
		return false;
		break;
	}
	answer = num;
	return true;
}

bool operateFloat(const float& one, const float& other, const char* ope, float& answer) {
	float num = one;
	int length = (int)strlen(ope);
	switch (length)
	{
	case 1:
		switch (ope[0])
		{
		case '+':
			num += other;
			break;
		case '-':
			num -= other;
			break;
		case '*':
			num *= other;
			break;
		case '/':
			if (other != 0) {
				num /= other;
			}
			else {
				return false;
			}
			break;
		case '%':
			if (other != 0) {
				pyMod(one, other, num);
			}
			else {
				return false;
			}
			break;
		default:
			break;
		}
		break;
	case 2:
		if (ope == ">>") {
			return false;
			break;
		}
		else if (ope == "<<") {
			return false;
			break;
		}
		else{
			return false;
		}
		break;
	default:
		return false;
		break;
	}
	answer = num;
	return true;
}

bool pyMod(const int& left, const int& right, int& answer) {
	if (right != 0) {
		answer = left - (right * (int)floor(left / (right + 0.0)));
		return true;
	}
	else {
		return false;
	}
}
bool pyMod(const float& left, const float& right, float& answer) {
	if (right != 0) {
		answer = left - (right * (int)floor(left / right));
		return true;
	}
	else {
		return false;
	}
}

//以下类的构造
pyObject::pyObject() {}
pyObjectData::pyObjectData() {}
pyObjectInt::pyObjectInt(int _data) : data(_data) {}
pyObjectBool::pyObjectBool(bool _data) : data(_data) {}
pyObjectFloat::pyObjectFloat(float _data) : data(_data) {}
pyObjectString::pyObjectString(string _data) : data(_data) {}

//以下pyObjectData类的函数
pyObjectDataPtr pyObjectData::operatorFather(const pyObjectData &other, const char* ope) const{
	pyObjectDataPtr returnPtr = nullptr;
	string thisType = this->getType(), otherType = other.getType();
	if ((thisType != "string") && (otherType != "string")) {
		if ((thisType == "float") || (otherType == "float")) {
			float num = 0.0;
			bool flag = operateFloat(this->getDataFloat(), other.getDataFloat(), ope, num);
			if (flag) {
				returnPtr = (pyObjectDataPtr)new pyObjectFloat(num);
			}
		}
		else {
			int num = 0;
			bool flag = operateInt(this->getDataInt(), other.getDataInt(), ope, num);
			if (flag) {
				returnPtr = (pyObjectDataPtr)new pyObjectInt(num);
			}
		}
	}
	return returnPtr;
}
pyObjectDataPtr pyObjectData::operatorFatherBool(const pyObjectData &other, const char* ope) const {
	pyObjectDataPtr returnPtr = nullptr;
	string thisType = this->getType(), otherType = other.getType();
	if ((thisType != "string") && (otherType != "string")) {
		bool returnBool = false;
		bool flag = operateBool(this->getDataFloat(), other.getDataFloat(), ope, returnBool);
		if (flag) {
			returnPtr = (pyObjectDataPtr)new pyObjectBool(returnBool);
		}
	}
	return returnPtr;
}
float pyObjectData::getDataFloat() const {
	assert(false);
	return 0;
}
int pyObjectData::getDataInt() const {
	assert(false);
	return 0;
}
pyObjectDataPtr pyObjectData::operator-() const {
	assert(false);
	return nullptr;
}
pyObjectPtr pyObjectData::opePT(string memName) const {
	assert(false);
	return nullptr;
}
pyObjectDataPtr pyObjectData::operator+(const pyObjectData &other) const {
	return operatorFather(other, "+");
}
pyObjectDataPtr pyObjectData::operator-(const pyObjectData &other) const {
	return operatorFather(other, "-");
}
pyObjectDataPtr pyObjectData::operator*(const pyObjectData &other) const {
	return operatorFather(other, "*");
}
pyObjectDataPtr pyObjectData::operator/(const pyObjectData &other) const {
	if (!(bool)other) {
		return nullptr;
	}
	else {
		return operatorFather(other, "/");
	}
}
pyObjectDataPtr pyObjectData::operator==(const pyObjectData &other) const {
	return operatorFatherBool(other, "==");
}
pyObjectDataPtr pyObjectData::operator!=(const pyObjectData &other) const {
	return operatorFatherBool(other, "!=");
}
pyObjectDataPtr pyObjectData::operator<(const pyObjectData &other) const {
	return operatorFatherBool(other, "<");
}
pyObjectDataPtr pyObjectData::operator>(const pyObjectData &other) const {
	return operatorFatherBool(other, ">");
}
pyObjectDataPtr pyObjectData::operator<=(const pyObjectData &other) const {
	return operatorFatherBool(other, "<=");
}
pyObjectDataPtr pyObjectData::operator>=(const pyObjectData &other) const {
	return operatorFatherBool(other, ">=");
}
pyObjectDataPtr pyObjectData::operator%(const pyObjectData &other) const {
	if (!(bool)other) {
		return nullptr;
	}
	else {
		return operatorFather(other, "%");
	}
}
pyObjectDataPtr pyObjectData::operator<<(const pyObjectData &other) const {
	return operatorFather(other, "<<");
}
pyObjectDataPtr pyObjectData::operator>>(const pyObjectData &other) const {
	return operatorFather(other, ">>");
}
pyObjectDataPtr pyObjectData::operator&&(const pyObjectData &other) const {
	bool returnBool = (this->operator bool() && other.operator bool());
	return (pyObjectDataPtr)new pyObjectBool(returnBool);
}
pyObjectDataPtr pyObjectData::operator||(const pyObjectData &other) const {
	bool returnBool = (this->operator bool() || other.operator bool());
	return (pyObjectDataPtr)new pyObjectBool(returnBool);
}
pyObjectDataPtr pyObjectData::operator!() const {
	bool answer = !(this->operator bool());
	return (pyObjectDataPtr)new pyObjectBool(answer);
}
pyObjectDataPtr pyObjectData::operator&(const pyObjectData &other) const {
	return operatorFather(other, "&");
}
pyObjectDataPtr pyObjectData::operator|(const pyObjectData &other) const {
	return operatorFather(other, "|");
}

//以下pyObjectInt类的函数
float pyObjectInt::getDataFloat() const {
	return (float)data;
}
int pyObjectInt::getDataInt() const {
	return data;
}
string pyObjectInt::getType() const {
	return "int";
}
pyObjectDataPtr pyObjectInt::operator-() const {
	pyObjectDataPtr returnPtr = (pyObjectDataPtr)new pyObjectInt(-(this->data));
	return returnPtr;
}
pyObjectInt::operator bool() const {
	return (this->data != 0);
}
pyObjectInt::operator int() const {
	return (this->data);
}
void pyObjectInt::print() const {
	cout << data;
}

//以下pyObjectBool类的函数
float pyObjectBool::getDataFloat() const {
	if (data) { return 1.0; }
	else { return 0.0; }
}
int pyObjectBool::getDataInt() const {
	if (data) { return 1; }
	else { return 0; }
}
string pyObjectBool::getType() const {
	return "bool";
}
pyObjectDataPtr pyObjectBool::operator-() const {
	int num = this->getDataInt();
	pyObjectDataPtr returnPtr = (pyObjectDataPtr)new pyObjectInt(-num);
	return returnPtr;
}
pyObjectBool::operator bool() const {
	return this->data;
}
pyObjectBool::operator int() const {
	if (this->data) {
		return 1;
	}
	else {
		return 0;
	}
}
void pyObjectBool::print() const {
	if (this->data) {
		cout << "True";
	}
	else {
		cout << "False";
	}
}

//以下pyObjectFloat类的函数
float pyObjectFloat::getDataFloat() const {
	return this->data;
}
int pyObjectFloat::getDataInt() const {
	return (int)this->data;
}
string pyObjectFloat::getType() const {
	return "float";
}
pyObjectDataPtr pyObjectFloat::operator-() const {
	pyObjectDataPtr returnPtr = (pyObjectDataPtr)new pyObjectFloat(-(this->data));
	return returnPtr;
}
pyObjectFloat::operator bool() const {
	return (this->data != 0);
}
void pyObjectFloat::print() const {
	cout << data;
}

//以下pyObjectString类的函数
float pyObjectString::getDataFloat() const {
	assert(false);
	return 0.0;
}
int pyObjectString::getDataInt() const {
	assert(false);
	return 0;
}
pyObjectDataPtr pyObjectString::operatorFatherString(const pyObjectData &other, const char* ope) const {
	const pyObjectString* tmp = dynamic_cast<const pyObjectString*>(&other);
	if (tmp == nullptr) {
		return nullptr;
	}
	if (tmp != nullptr) {
	}
	int length = (int)strlen(ope);
	switch (length)
	{
	case 1:
		switch (ope[0])
		{
		case '+': {
			string returnStr = this->data + tmp->data;
			return (pyObjectDataPtr)new pyObjectString(returnStr);
		}
		case '>':
			return (pyObjectDataPtr)new pyObjectBool(this->data > tmp->data);
		case '<':
			return (pyObjectDataPtr)new pyObjectBool(this->data < tmp->data);
		default:
			return nullptr;
		}
	case 2:
		if (ope == "==") {
			return (pyObjectDataPtr)new pyObjectBool(this->data == tmp->data);
		}
		if (ope == "!=") {
			return (pyObjectDataPtr)new pyObjectBool(this->data != tmp->data);
		}
		else if (ope == ">=") {
			return (pyObjectDataPtr)new pyObjectBool(this->data >= tmp->data);
		}
		else if (ope == "<=") {
			return (pyObjectDataPtr)new pyObjectBool(this->data <= tmp->data);
		}
		return nullptr;
	default:
		return nullptr;
	}
}
string pyObjectString::getType() const {
	return "string";
}
pyObjectDataPtr pyObjectString::operator+(const pyObjectData &other) const {
	return operatorFatherString(other, "+");
}
pyObjectDataPtr pyObjectString::operator-() const {
	return nullptr;
}
pyObjectDataPtr pyObjectString::operator==(const pyObjectData &other) const {
	return operatorFatherString(other, "==");
}
pyObjectDataPtr pyObjectString::operator!=(const pyObjectData &other) const {
	return operatorFatherString(other, "!=");
}
pyObjectDataPtr pyObjectString::operator<(const pyObjectData &other) const {
	return operatorFatherString(other, "<");
}
pyObjectDataPtr pyObjectString::operator>(const pyObjectData &other) const {
	return operatorFatherString(other, ">");
}
pyObjectDataPtr pyObjectString::operator<=(const pyObjectData &other) const {
	return operatorFatherString(other, "<=");
}
pyObjectDataPtr pyObjectString::operator>=(const pyObjectData &other) const {
	return operatorFatherString(other, ">=");
}
pyObjectString::operator bool() const {
	return (this->data == "");
}
void pyObjectString::print() const {
	cout << this->data;
}