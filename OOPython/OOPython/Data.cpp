//Data.cpp
#include "Data.h"

pyObject::pyObject() {}

pyObjectInt::pyObjectInt(int _data) : data(_data) {}

int pyObjectInt::operateInt(int other, const char* ope) const{
	int num = this->data;
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
		if (ope==">>")
			num = num >> other;
		if (ope=="<<")
			num = num << other;
		break;
	default:
		break;
	}
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
	return num;
}

pyObject* pyObjectInt::operatorFather(const pyObject *other, const char* ope) const{
	pyObject * returnPtr = nullptr;
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
string pyObjectInt::getType() const {
	return "int";
}

pyObject* pyObjectInt::operator+(const pyObject *other) const {
	return operatorFather(other, "+");
}
pyObject* pyObjectInt::operator-(const pyObject *other) const {
	return operatorFather(other, "-");
}
pyObject* pyObjectInt::operator-() const {
	pyObject* returnPtr = new pyObjectInt(-this->data);
	return returnPtr;
}
pyObject* pyObjectInt::operator*(const pyObject *other) const {
	return operatorFather(other, "/");
}
pyObject* pyObjectInt::operator/(const pyObject *other) const {
	if (*other == &pyObjectBool::falseBool) {
		return nullptr;
	}
	else {
		return operatorFather(other, "/");
	}
}
pyObject* pyObjectInt::operator==(const pyObject *other) const {

}
pyObject* pyObjectInt::operator<<(const pyObject *other) const {

}
pyObject* pyObjectInt::operator>>(const pyObject *other) const {

}
pyObject* pyObjectInt::work() {
	return this;
}

pyObjectBool::pyObjectBool(bool _data) : data(_data) {}

pyObjectBool pyObjectBool::trueBool = new pyObjectBool(true); 
pyObjectBool pyObjectBool::falseBool = new pyObjectBool(false);