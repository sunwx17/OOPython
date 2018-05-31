#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <memory>
using namespace std;

class pyObject;
typedef shared_ptr<const pyObject> pyObjectPtr;

class pyObjectBool;
class pyObjectInt;
class pyObject;
class pyObjectData;
map<string, pyObjectData*> dataGlobal;
//以下基础函数：operateInt、operateBool、operateFloat 
bool operateBool(const float& one, const float& other, const char* ope);
int operateInt(const int& one, const int& other, const char* ope);
float operateFloat(const float& one, const float& other, const char* ope);

//以下pyObject类
class pyObject{
public:
	pyObject();
	virtual ~pyObject() = 0;
	virtual string getType() const = 0;
	virtual pyObjectData* work() = 0;
};

class pyObjectData :public pyObject {
	virtual pyObjectData* operatorFather(const pyObject *other, const char* ope) const = 0;
	virtual pyObjectData* operatorFatherBool(const pyObject *other, const char* ope) const = 0;
public:
	friend class pyObjectBool;
	friend class pyObjectInt;
	pyObjectData();
	virtual ~pyObjectData() = 0;
	virtual string getType() const = 0;
	pyObjectData* operator+(const pyObjectData *other) const;
	pyObjectData* operator-(const pyObjectData *other) const;
	virtual pyObjectData* operator-() const = 0;//Mark: To Do: 实现基类operator
	pyObjectData* operator*(const pyObjectData *other) const;
	pyObjectData* operator/(const pyObjectData *other) const;
	pyObjectData* operator==(const pyObjectData *other) const;
	pyObjectData* operator<(const pyObjectData *other) const;
	pyObjectData* operator>(const pyObjectData *other) const;
	pyObjectData* operator<<(const pyObjectData *other) const;
	pyObjectData* operator>>(const pyObjectData *other) const;
	virtual pyObjectData* work() = 0;

};
//class pyObjectFunc : public pyObject {
//	map<string, pyObjectData*> dataFunc;
//	pyBlock * place;
//public:
//	pyObjectFunc(pyBlock *);
//	pyObjectData* work();
//};
class pyObjectBool : public pyObjectData {
	bool data;
	pyObjectBool(bool _data);
	pyObjectBool(const pyObjectBool &) = delete;
	void operator=(const pyObjectBool &) = delete;
	~pyObjectBool() {}
	pyObjectData* operatorFather(const pyObject *other, const char* ope) const;
	pyObjectData* operatorFatherBool(const pyObject *other, const char* ope) const;
public:
	static pyObjectBool trueBool;
	static pyObjectBool falseBool;
	string getType() const;
	pyObjectData* operator-() const;
	pyObjectData* work();
};

class pyObjectInt : public pyObject {
	int data;
	pyObjectData* operatorFather(const pyObject *other, const char* ope) const;
	pyObjectData* operatorFatherBool(const pyObject *other, const char* ope) const;
public:
	pyObjectInt(int _data);
	string getType() const;
	pyObjectData* operator-() const;
	pyObjectData* work();
};

class pyObjectFloat : public pyObject {
	float data;
	pyObjectData* operatorFather(const pyObject *other, const char* ope) const;
	pyObjectData* operatorFatherBool(const pyObject *other, const char* ope) const;
public:
	pyObjectFloat(float _data);
	string getType() const;
	pyObjectData* operator-() const;
	pyObjectData* work();
};

#endif