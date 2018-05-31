//Data.cpp
#include "Data.h"
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
			else{
				return false;
			}
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
			else{
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
//以下类的构造
pyObject::pyObject() {}
pyObjectData::pyObjectData() {}
pyObjectInt::pyObjectInt(int _data) : data(_data) {}
pyObjectBool::pyObjectBool(bool _data) : data(_data) {}
pyObjectFloat::pyObjectFloat(float _data) : data(_data) {}

//以下pyObjectData类的函数
pyObjectDataPtr pyObjectData::operatorFather(const pyObjectData &other, const char* ope) const{
	pyObjectDataPtr returnPtr = nullptr;
	string thisType = this->getType(), otherType = other.getType();
	if ((thisType == "float") || (otherType == "float")) {
		float num = 0.0;
		bool flag = operateFloat(this->getDataFloat(), other.getDataFloat(), ope, num);
		if(flag) {
			returnPtr = new pyObjectFloat(num);
		}
	}
	else if (((otherType == "int") || (otherType == "bool")) &&
			((thisType == "int") || (thisType == "bool"))) {
		int num = 0;
		bool flag = operateInt(this->getDataInt(), other.getDataInt(), ope, num);
		if(flag) {
			returnPtr = new pyObjectInt(num);
		}
	}
	return returnPtr;
}
pyObjectDataPtr pyObjectData::operatorFatherBool(const pyObjectData &other, const char* ope) const {
	bool returnBool = false;
	bool flag = operateBool(this->getDataFloat(), other.getDataFloat(), ope, returnBool);
	pyObjectDataPtr returnPtr = nullptr;
	if(flag) {
		returnPtr = new pyObjectBool(returnBool);
	}
	return returnPtr;
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
	if (!other) {
		return nullptr;
	}
	else {
		return operatorFather(other, "/");
	}
}
pyObjectDataPtr pyObjectData::operator==(const pyObjectData &other) const {
	return operatorFatherBool(other, "==");
}
pyObjectDataPtr pyObjectData::operator<(const pyObjectData &other) const {
	return operatorFatherBool(other, "<");
}
pyObjectDataPtr pyObjectData::operator>(const pyObjectData &other) const {
	return operatorFatherBool(other, ">");
}
pyObjectDataPtr pyObjectData::operator<<(const pyObjectData &other) const {
	return operatorFather(other, "<<");
}
pyObjectDataPtr pyObjectData::operator>>(const pyObjectData &other) const {
	return operatorFather(other, ">>");
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
	pyObjectDataPtr returnPtr = new pyObjectInt(-(this->data));
	return returnPtr;
}
pyObjectInt::operator bool() const {
	return (this->data == 0);
}
void pyObjectInt::print() {
	cout << data << endl;
}

//Mark:To Do完成bool、float 
string pyObjectBool::getType() const {
	return "bool";
}


pyObjectDataPtr pyObjectBool::operatorFather(const pyObjectData &other, const char* ope) const {
	pyObjectDataPtr tmp;
	if (this == &pyObjectBool::trueBool) {
		tmp = new pyObjectInt(1);
	}
	else {
		tmp = new pyObjectInt(0);
	}
	pyObjectDataPtr returnPtr = tmp->operatorFather(other, ope);
	delete tmp;
	return returnPtr;
}

pyObjectDataPtr pyObjectBool::operatorFatherBool(const pyObjectData &other, const char* ope) const {
	pyObjectDataPtr tmp;
	if (this == &pyObjectBool::trueBool) {
		tmp = new pyObjectInt(1);
	}
	else {
		tmp = new pyObjectInt(0);
	}
	pyObjectDataPtr returnPtr = tmp->operatorFatherBool(other, ope);
	delete tmp;
	return returnPtr;
}

void pyObjectBool::print() {
	cout << data << endl;
}
float pyObjectBool::getDataFloat() const {
	if (data) {
		return 1.0;
	}
	else {
		return 0.0;
	}
}
int pyObjectBool::getDataInt() const {
	if (data) {
		return 1;
	}
	else {
		return 0;
	}
}

pyObjectDataPtr pyObjectFloat::operatorFatherBool(const pyObjectData &other, const char* ope) const {
	string otherType = other.getType();
	if (otherType == "bool") {
		//Mark:To Do
	} 
}
//Mark:To Do
pyObjectDataPtr pyObjectFloat::operatorFather(const pyObjectData &other, const char* ope) const {
	pyObjectDataPtr returnPtr = nullptr;
	string otherType = other.getType();
	int num = this->data;
	if (otherType == "int") {//Mark:To Do
		const pyObjectFloat * otherInt = dynamic_cast<const pyObjectInt*>(other);
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
float pyObjectFloat::getDataFloat() const {
	return (float)data;
}
int pyObjectFloat::getDataInt() const {
	return (int)data;
}
