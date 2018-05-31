//Data.cpp
#include "Data.h"
//以下基础函数：operateInt、operateBool、operateFloat
bool operateBool(const float& one, const float& other, const char* ope) {
	bool answer = false;
	int length = (int)strlen(ope);
	switch (length)
	{
	case 1:
		switch (ope[0])
		{
		case '>':
			answer = (one > other);
			break;
		case '<':
			answer = (one < other);
			break;
		default:
			break;
		}
		break;
	case 2:
		if (ope == "==") {
			answer = (one == other);
			break;
		}
		break;
	default:
		break;
	}
	return answer;
}

int operateInt(const int& one, const int& other, const char* ope) {
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
			break;
		default:
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
		break;
	}
	return num;
}

float operateFloat(const float& one, const float& other, const char* ope) {
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
			break;
		default:
			break;
		}
		break;
	case 2:
		if (ope == ">>")
			break;
		if (ope == "<<")
			break;
		break;
	default:
		break;
	}
	return num;
}
//以下类的构造
pyObject::pyObject() {}
pyObjectData::pyObjectData() {}
pyObjectInt::pyObjectInt(int _data) : data(_data) {}
pyObjectBool::pyObjectBool(bool _data) : data(_data) {}

pyObjectBool pyObjectBool::trueBool = new pyObjectBool(true);
pyObjectBool pyObjectBool::falseBool = new pyObjectBool(false);


pyObject* pyObjectInt::operatorFatherBool(const pyObjectData *other, const char* ope) const {
	pyObject* tmp = new pyObjectFloat((float)data);
	pyObject* returnPtr = tmp->operatorFatherBool(other, ope);
	delete tmp;
	return returnPtr;
	return nullptr;
}

pyObject* pyObjectInt::operatorFather(const pyObjectData *other, const char* ope) const{
	pyObjectData * returnPtr = nullptr;
	string otherType = other->getType();
	int num = this->data;
	if (otherType == "int") {
		const pyObjectInt * otherInt = dynamic_cast<const pyObjectInt*>(other);
		num = operateInt(otherInt->data, ope);
		returnPtr = new pyObjectInt(num);
	}
	else if (otherType == "bool") {
		if (other == &pyObjectBool::trueBool) {
			num = operateInt(1, ope);
		}
		else {
			num = operateInt(0, ope);
		}
		returnPtr = new pyObjectInt(num);
	}
	//else if (otherType == "float") {
	//	pyObjectFloat tmp(this);
	//	returnPtr = tmp.pyObjectFloat(other, ope);
	//}
	return returnPtr;

}

pyObject* pyObjectData::operator+(const pyObjectData *other) const {
	return operatorFather(other, "+");
}
pyObject* pyObjectData::operator-(const pyObjectData *other) const {
	return operatorFather(other, "-");
}
pyObject* pyObjectData::operator*(const pyObjectData *other) const {
	return operatorFather(other, "/");
}
pyObject* pyObjectData::operator/(const pyObjectData *other) const {
	if (*other == &pyObjectBool::falseBool) {
		return nullptr;
	}
	else {
		return operatorFather(other, "/");
	}
}
pyObject* pyObjectData::operator==(const pyObjectData *other) const {
	return operatorFatherBool(other, "==");
}
pyObject* pyObjectData::operator<(const pyObjectData *other) const {
	return operatorFatherBool(other, "<");
}
pyObject* pyObjectData::operator>(const pyObjectData *other) const {
	return operatorFatherBool(other, ">");
}
pyObject* pyObjectData::operator<<(const pyObjectData *other) const {
	return operatorFather(other, "<<");
}
pyObject* pyObjectData::operator>>(const pyObjectData *other) const {
	return operatorFather(other, ">>");
}
pyObject* pyObjectInt::work() {
	return this;
}

string pyObjectInt::getType() const {
	return "int";
}

pyObject* pyObjectInt::operator-() const {
	pyObject* returnPtr = new pyObjectInt(-this->data);
	return returnPtr;
}


string pyObjectBool::getType() const {
	return "bool";
}


pyObject* pyObjectBool::operatorFather(const pyObjectData *other, const char* ope) const {
	pyObjectData * tmp;
	if (this == &pyObjectBool::trueBool) {
		tmp = new pyObjectInt(1);
	}
	else {
		tmp = new pyObjectInt(0);
	}
	pyObject* returnPtr = tmp->operatorFather(other, ope);
	delete tmp;
	return returnPtr;
}

pyObject* pyObjectBool::operatorFatherBool(const pyObjectData *other, const char* ope) const {
	pyObjectData * tmp;
	if (this == &pyObjectBool::trueBool) {
		tmp = new pyObjectInt(1);
	}
	else {
		tmp = new pyObjectInt(0);
	}
	pyObject* returnPtr = tmp->operatorFatherBool(other, ope);
	delete tmp;
	return returnPtr;
}

pyObject* pyObjectBool::operator+(const pyObjectData *other) const {
	return operatorFather(other, "+");
}
pyObject* pyObjectBool::operator-(const pyObjectData *other) const {
	return operatorFather(other, "+");
}
pyObject* pyObjectBool::operator-() const {
	pyObjectData * returnPtr;
	if (this->data)
		returnPtr = new pyObjectInt(-1);
	else
		returnPtr = new pyObjectInt(0);
	return returnPtr;
}
pyObject* pyObjectBool::work() {
	return this;
}

pyObjectFloat::pyObjectFloat(float _data) : data(_data) {}


pyObject* pyObjectFloat::operatorFatherBool(const pyObjectData *other, const char* ope) const {
	string otherType = other->getType();
	if (otherType == "bool") {

	}
}
//Mark
pyObject* pyObjectFloat::operatorFather(const pyObjectData *other, const char* ope) const {
	pyObjectData * returnPtr = nullptr;
	string otherType = other->getType();
	int num = this->data;
	if (otherType == "int") {
		const pyObjectFloat * otherInt = dynamic_cast<const pyObjectFloat*>(other);
		num = operateInt(otherInt->data, ope);
		returnPtr = new pyObjectFloat(num);
	}
	else if (otherType == "bool") {
		if (other == &pyObjectBool::trueBool) {
			num = operateInt(1, ope);
		}
		else {
			num = operateInt(0, ope);
		}
		returnPtr = new pyObjectFloat(num);
	}
	//else if (otherType == "float") {
	//	pyObjectFloat tmp(this);
	//	returnPtr = tmp.pyObjectFloat(other, ope);
	//}
	return returnPtr;

}
string pyObjectFloat::getType() const {
	return "int";
}

pyObject* pyObjectFloat::operator+(const pyObjectData *other) const {
	return operatorFather(other, "+");
}
pyObject* pyObjectFloat::operator-(const pyObjectData *other) const {
	return operatorFather(other, "-");
}
pyObject* pyObjectFloat::operator-() const {
	pyObject* returnPtr = new pyObjectFloat(-this->data);
	return returnPtr;
}
pyObject* pyObjectFloat::operator*(const pyObjectData *other) const {
	return operatorFather(other, "/");
}
pyObject* pyObjectFloat::operator/(const pyObjectData *other) const {
	if (*other == &pyObjectBool::falseBool) {
		return nullptr;
	}
	else {
		return operatorFather(other, "/");
	}
}
pyObject* pyObjectFloat::operator==(const pyObjectData *other) const {
	return operatorFatherBool(other, "==");
}
pyObject* pyObjectFloat::operator<(const pyObjectData *other) const {
	return operatorFatherBool(other, "<");
}
pyObject* pyObjectFloat::operator>(const pyObjectData *other) const {
	return operatorFatherBool(other, ">");
}
pyObject* pyObjectFloat::operator<<(const pyObjectData *other) const {
	return operatorFather(other, "<<");
}
pyObject* pyObjectFloat::operator>>(const pyObjectData *other) const {
	return operatorFather(other, ">>");
}
pyObject* pyObjectFloat::work() {
	return this;
}