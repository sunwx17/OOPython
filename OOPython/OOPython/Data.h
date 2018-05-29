#ifndef DATA_H
#define DATA_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class pyObject{
	string name;
public:
	pyObject(string _name = "") :name(_name) {}
	virtual ~pyObject() = 0;
	virtual string getType() = 0;
	virtual pyObject* operator+(const pyObject *other) = 0;
	virtual pyObject* operator-(const pyObject *other) = 0;
	virtual pyObject* operator*(const pyObject *other) = 0;
	virtual pyObject* operator/(const pyObject *other) = 0;
	virtual pyObject* operator=(const pyObject *other) = 0;
	virtual pyObject* operator==(const pyObject *other) = 0;
	virtual pyObject* operator<<(const pyObject *other) = 0;
	virtual pyObject* operator>>(const pyObject *other) = 0;
};

template <typename T>
class pyObjectData : public pyObject {
	T data;
public:

};
#endif