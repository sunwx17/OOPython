#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <memory>
using namespace std;
//Mark:To Do完成list、scan 

class pyObject;
class pyObjectData;
class pyObjectBool;
class pyObjectInt;
class pyObjectFloat;
typedef shared_ptr<const pyObject> pyObjectPtr;
typedef shared_ptr<const pyObjectData> pyObjectDataPtr;
//以下基础函数：operateInt、operateBool、operateFloat 
bool operateBool(const float& one, const float& other, const char* ope, bool& answer);
bool operateInt(const int& one, const int& other, const char* ope, int& answer);
bool operateFloat(const float& one, const float& other, const char* ope, float& answer);

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
	virtual pyObjectDataPtr operatorFather(const pyObjectData &other, const char* ope) const;
	pyObjectDataPtr operatorFatherBool(const pyObjectData &other, const char* ope) const;
	virtual float getDataFloat() const = 0;
	virtual int getDataInt() const = 0;
public://Mark:To Do增加&&、||、!、string 
	pyObjectData();
	virtual ~pyObjectData() = 0;
	virtual string getType() const = 0;
	pyObjectDataPtr operator+(const pyObjectData &other) const;
	pyObjectDataPtr operator-(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator-() const = 0;
	pyObjectDataPtr operator*(const pyObjectData &other) const;
	pyObjectDataPtr operator/(const pyObjectData &other) const;
	pyObjectDataPtr operator==(const pyObjectData &other) const;
	pyObjectDataPtr operator<(const pyObjectData &other) const;
	pyObjectDataPtr operator>(const pyObjectData &other) const;
	pyObjectDataPtr operator<<(const pyObjectData &other) const;
	pyObjectDataPtr operator>>(const pyObjectData &other) const;
	virtual operator bool() const = 0; 
};
//class pyObjectFunc : public pyObject {
//	map<string, pyObjectDataPtr> dataFunc;
//	pyBlock * place;
//public:
//	pyObjectFunc(pyBlock *);
//	pyObjectDataPtr work();
//};

class pyObjectInt : public pyObjectData {
	int data;
	float getDataFloat() const;
	int getDataInt() const;
public:
	pyObjectInt(int _data);
	string getType() const;
	pyObjectDataPtr operator-() const;
	operator bool() const;
	void print();
};

class pyObjectBool : public pyObjectData {
	bool data;
	float getDataFloat() const;
	int getDataInt() const;
public:
	pyObjectBool(bool _data);
	string getType() const;
	pyObjectDataPtr operator-() const;
	operator bool() const;
	void print();
};

class pyObjectFloat : public pyObjectData {
	float data;
	float getDataFloat() const;
	int getDataInt() const;
public:
	pyObjectFloat(float _data);
	string getType() const;
	pyObjectDataPtr operator-() const;
	operator bool() const;
	void print();
};

#endif
