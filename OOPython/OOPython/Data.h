#ifndef DATA_H
#define DATA_H

#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
using namespace std;
class pyObjectBool;
class pyObject{
	virtual pyObject* operatorFather(const pyObject *other, const char* ope) const = 0;
	virtual pyObject* operatorFatherBool(const pyObject *other, const char* ope) const = 0;
public:
	friend class pyObjectBool;
	pyObject();
	virtual ~pyObject() = 0;
	virtual string getType() const = 0;
	virtual pyObject* operator+(const pyObject *other) const = 0;
	virtual pyObject* operator-(const pyObject *other) const = 0;
	virtual pyObject* operator-() const = 0;
	virtual pyObject* operator*(const pyObject *other) const = 0;
	virtual pyObject* operator/(const pyObject *other) const = 0;
	virtual pyObject* operator==(const pyObject *other) const = 0;
	virtual pyObject* operator<(const pyObject *other) const = 0;
	virtual pyObject* operator>(const pyObject *other) const = 0;
	virtual pyObject* operator<<(const pyObject *other) const = 0;
	virtual pyObject* operator>>(const pyObject *other) const = 0;
	virtual pyObject* work() = 0;
};

map<string, pyObject*> dataGlobal;

//class pyObjectFunc : public pyObject {
//	map<string, pyObject*> dataFunc;
//	pyBlock * place;
//public:
//	pyObjectFunc(pyBlock *);
//	pyObject* work();
//};
class pyObjectBool : public pyObject {
	bool data;
	pyObjectBool(bool _data);
	pyObjectBool(const pyObjectBool &) = delete;
	void operator=(const pyObjectBool &) = delete;
	~pyObjectBool() {}
	pyObject* operatorFather(const pyObject *other, const char* ope) const;
	pyObject* operatorFatherBool(const pyObject *other, const char* ope) const;
public:
	static pyObjectBool trueBool;
	static pyObjectBool falseBool;
	string getType() const;
	pyObject* operator+(const pyObject *other) const;
	pyObject* operator-(const pyObject *other) const;
	pyObject* operator-() const;
	pyObject* operator*(const pyObject *other) const;
	pyObject* operator/(const pyObject *other) const;
	pyObject* operator==(const pyObject *other) const;
	pyObject* operator<(const pyObject *other) const;
	pyObject* operator>(const pyObject *other) const;
	pyObject* operator<<(const pyObject *other) const;
	pyObject* operator>>(const pyObject *other) const;
	pyObject* work();
};

class pyObjectInt : public pyObject {
	int data;
	int operateInt(int other, const char* ope) const;
	pyObject* operatorFather(const pyObject *other, const char* ope) const;
	pyObject* operatorFatherBool(const pyObject *other, const char* ope) const;
public:
	pyObjectInt(int _data);
	string getType() const;
	pyObject* operator+(const pyObject *other) const;
	pyObject* operator-(const pyObject *other) const;
	pyObject* operator-() const;
	pyObject* operator*(const pyObject *other) const;
	pyObject* operator/(const pyObject *other) const;
	pyObject* operator==(const pyObject *other) const;
	pyObject* operator<(const pyObject *other) const;
	pyObject* operator>(const pyObject *other) const;
	pyObject* operator<<(const pyObject *other) const;
	pyObject* operator>>(const pyObject *other) const;
	pyObject* work();
};

#endif