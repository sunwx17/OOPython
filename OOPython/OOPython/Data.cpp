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

//以下pyObjectData类的函数


pyObjectData* pyObjectInt::operatorFatherBool(const pyObjectData *other, const char* ope) const {
	pyObjectData* tmp = new pyObjectFloat((float)data);
	pyObjectData* returnPtr = tmp->operatorFatherBool(other, ope);
	delete tmp;
	return returnPtr;
	return nullptr;
}
pyObjectData* pyObjectData::operator+(const pyObjectData *other) const {
	return operatorFather(other, "+");
}
pyObjectData* pyObjectData::operator-(const pyObjectData *other) const {
	return operatorFather(other, "-");
}
pyObjectData* pyObjectData::operator*(const pyObjectData *other) const {
	return operatorFather(other, "*");
}
pyObjectData* pyObjectData::operator/(const pyObjectData *other) const {
	if (*other == &pyObjectBool::falseBool) {
		return nullptr;
	}
	else {
		return operatorFather(other, "/");
	}
}
pyObjectData* pyObjectData::operator==(const pyObjectData *other) const {
	return operatorFatherBool(other, "==");
}
pyObjectData* pyObjectData::operator<(const pyObjectData *other) const {
	return operatorFatherBool(other, "<");
}
pyObjectData* pyObjectData::operator>(const pyObjectData *other) const {
	return operatorFatherBool(other, ">");
}
pyObjectData* pyObjectData::operator<<(const pyObjectData *other) const {
	return operatorFather(other, "<<");
}
pyObjectData* pyObjectData::operator>>(const pyObjectData *other) const {
	return operatorFather(other, ">>");
}




string pyObjectInt::getType() const {
	return "int";
}
pyObjectData* pyObjectInt::operator-() const {
	pyObjectData* returnPtr = new pyObjectInt(-this->data);
	return returnPtr;
}
void pyObjectInt::print() {
	cout << data << endl;
}
float pyObjectInt::getDataFloat() {
	return (float)data;
}
pyObjectData* pyObjectInt::operatorFather(const pyObjectData *other, const char* ope) const{
	pyObjectData * returnPtr = nullptr;
	string otherType = other->getType();
	int num = this->data;
	if (otherType == "int") {
		const pyObjectInt * otherInt = dynamic_cast<const pyObjectInt*>(other);
		num = operateInt(num, otherInt->data, ope);
		returnPtr = new pyObjectInt(num);
	}
	else if (otherType == "bool") {
		if (other == &pyObjectBool::trueBool) {
			num = operateInt(num, 1, ope);
		}
		else {
			num = operateInt(num, 0, ope);
		}
		returnPtr = new pyObjectInt(num);
	}
	else if (otherType == "float") {
		pyObjectFloat tmp(num);
		returnPtr = tmp.pyObjectFloat(other, ope);
	}
	return returnPtr;

}

string pyObjectBool::getType() const {
	return "bool";
}


pyObjectData* pyObjectBool::operatorFather(const pyObjectData *other, const char* ope) const {
	pyObjectData * tmp;
	if (this == &pyObjectBool::trueBool) {
		tmp = new pyObjectInt(1);
	}
	else {
		tmp = new pyObjectInt(0);
	}
	pyObjectData* returnPtr = tmp->operatorFather(other, ope);
	delete tmp;
	return returnPtr;
}

pyObjectData* pyObjectBool::operatorFatherBool(const pyObjectData *other, const char* ope) const {
	pyObjectData * tmp;
	if (this == &pyObjectBool::trueBool) {
		tmp = new pyObjectInt(1);
	}
	else {
		tmp = new pyObjectInt(0);
	}
	pyObjectData* returnPtr = tmp->operatorFatherBool(other, ope);
	delete tmp;
	return returnPtr;
}

pyObjectData* pyObjectBool::operator+(const pyObjectData *other) const {
	return operatorFather(other, "+");
}
pyObjectData* pyObjectBool::operator-(const pyObjectData *other) const {
	return operatorFather(other, "+");
}
pyObjectData* pyObjectBool::operator-() const {
	pyObjectData * returnPtr;
	if (this->data)
		returnPtr = new pyObjectInt(-1);
	else
		returnPtr = new pyObjectInt(0);
	return returnPtr;
}
void pyObjectBool::print() {
	cout << data << endl;
}
float pyObjectBool::getDataFloat() {
	return (float)data;
}

pyObjectFloat::pyObjectFloat(float _data) : data(_data) {}


pyObjectData* pyObjectFloat::operatorFatherBool(const pyObjectData *other, const char* ope) const {
	string otherType = other->getType();
	if (otherType == "bool") {

	}
}
//Mark
pyObjectData* pyObjectFloat::operatorFather(const pyObjectData *other, const char* ope) const {
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

void pyObjectFloat::print() {
	cout << data << endl;
}
float pyObjectFloat::getDataFloat() {
	return (float)data;
}