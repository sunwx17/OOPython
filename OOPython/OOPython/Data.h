#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <memory>
using namespace std;


class pyObjectBool;
class pyObjectInt;
class pyObject;
class pyObjectData;
typedef shared_ptr<const pyObject> pyObjectPtr;
typedef shared_ptr<const pyObjectData> pyObjectDataPtr;
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
	virtual void print() = 0;
};

//以下pyObjectData类
class pyObjectData :public pyObject {
	virtual pyObjectData* operatorFather(const pyObjectData *other, const char* ope) const = 0;
	pyObjectData* operatorFatherBool(const pyObjectData *other, const char* ope) const;
	virtual float getDataFloat() = 0;
public:
	friend class pyObjectBool;
	friend class pyObjectInt;//Mark:把它去掉
	pyObjectData();
	virtual ~pyObjectData() = 0;
	virtual string getType() const = 0;
	pyObjectData* operator+(const pyObjectData *other) const;
	pyObjectData* operator-(const pyObjectData *other) const;
	virtual pyObjectData* operator-() const = 0;
	pyObjectData* operator*(const pyObjectData *other) const;
	pyObjectData* operator/(const pyObjectData *other) const;
	pyObjectData* operator==(const pyObjectData *other) const;
	pyObjectData* operator<(const pyObjectData *other) const;
	pyObjectData* operator>(const pyObjectData *other) const;
	pyObjectData* operator<<(const pyObjectData *other) const;
	pyObjectData* operator>>(const pyObjectData *other) const;
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
	pyObjectData* operatorFather(const pyObjectData *other, const char* ope) const;
	pyObjectData* operatorFatherBool(const pyObjectData *other, const char* ope) const;
	float getDataFloat();
public:
	static pyObjectBool trueBool;
	static pyObjectBool falseBool;
	string getType() const;
	pyObjectData* operator-() const;
	void print();
};

class pyObjectInt : public pyObjectData {
	int data;
	pyObjectData* operatorFather(const pyObjectData *other, const char* ope) const;
	pyObjectData* operatorFatherBool(const pyObjectData *other, const char* ope) const;
	float getDataFloat();
public:
	pyObjectInt(int _data);
	string getType() const;
	pyObjectData* operator-() const;
	void print();
};

class pyObjectFloat : public pyObjectData {
	float data;
	pyObjectData* operatorFather(const pyObjectData *other, const char* ope) const;
	pyObjectData* operatorFatherBool(const pyObjectData *other, const char* ope) const;
	float getDataFloat();
public:
	pyObjectFloat(float _data);
	string getType() const;
	pyObjectData* operator-() const;
	void print();
};

#endif