#ifndef DATA_H
#define DATA_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

map<string, pyObject*> dataGlobal;

class pyObject{
	string name;
public:
	pyObject(string _name = "");
	virtual ~pyObject() = 0;
	virtual string getType() const = 0;
	virtual pyObject* operator+(const pyObject *other) const = 0;
	virtual pyObject* operator-(const pyObject *other) const = 0;
	virtual pyObject* operator-() const = 0;
	virtual pyObject* operator*(const pyObject *other) const = 0;
	virtual pyObject* operator/(const pyObject *other) const = 0;
	virtual pyObject* operator==(const pyObject *other) const = 0;
	virtual pyObject* operator<<(const pyObject *other) const = 0;
	virtual pyObject* operator>>(const pyObject *other) const = 0;
	virtual pyObject* work() = 0;
};

class pyObjectFunc : public pyObject {
	map<string, pyObject*> dataFunc;
	pyBlock * place;
public:
	pyObjectFunc(pyBlock *);
	pyObject* work();
};

class pyObjectInt : public pyObject {
	int data;
public:
	pyObjectInt(int _data, string _name = "");
	string getType() const;
	pyObject* operator+(const pyObject *other) const;
	pyObject* operator-(const pyObject *other) const;
	pyObject* operator-() const;
	pyObject* operator*(const pyObject *other) const;
	pyObject* operator/(const pyObject *other) const;
	pyObject* operator==(const pyObject *other) const;
	pyObject* operator<<(const pyObject *other) const;
	pyObject* operator>>(const pyObject *other) const;
	pyObject* work();
};
#endif