//Data.cpp
#include "Data.h"

pyObject::pyObject(string _name) :name(_name) {}

pyObjectInt::pyObjectInt(int _data, string _name) : pyObject(_name), data(_data) {}

string pyObjectInt::getType() const {
	return "int";
}
pyObject* pyObjectInt::operator+(const pyObject *other) const {
	string otherType = other->getType();
	if (otherType == "int") {
		const pyObjectInt * otherInt = dynamic_cast<const pyObjectInt*>(other);
		int num = this->data + otherInt->data;

	}
}
pyObject* pyObjectInt::operator-(const pyObject *other) const {

}
pyObject* pyObjectInt::operator-() const {

}
pyObject* pyObjectInt::operator*(const pyObject *other) const {

}
pyObject* pyObjectInt::operator/(const pyObject *other) const {

}
//mark2:16:27
pyObject* pyObjectInt::operator==(const pyObject *other) const {

}
pyObject* pyObjectInt::operator<<(const pyObject *other) const {

}
pyObject* pyObjectInt::operator>>(const pyObject *other) const {

}
pyObject* pyObjectInt::work() {
	return this;
}