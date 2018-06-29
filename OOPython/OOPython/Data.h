#ifndef DATA_H
#define DATA_H

#include <vector>
#include <map>
#include <string>
#include <string.h>
#include <iostream>
#include <memory>
#include <assert.h>
using namespace std;

class pyObject;
class pyObjectData;
class pyObjectBool;
class pyObjectInt;
class pyObjectFloat;
typedef shared_ptr<pyObject> pyObjectPtr;
typedef shared_ptr<pyObjectData> pyObjectDataPtr;
//以下基础函数：operateInt、operateBool、operateFloat 
bool operateBool(const float& one, const float& other, const char* ope, bool& answer);
bool operateInt(const int& one, const int& other, const char* ope, int& answer);
bool operateFloat(const float& one, const float& other, const char* ope, float& answer);
bool pyMod(const int& left, const int& right, int& answer);
bool pyMod(const float& left, const float& right, float& answer);
//以下pyObject类及其子类
class pyObject{
public:
	pyObject();
	virtual ~pyObject() {};
	virtual string getType() const = 0;
	virtual void print() const = 0;
};

class pyObjectData :public pyObject {
	pyObjectDataPtr operatorFather(const pyObjectData &other, const char* ope) const;//string单独处理
	pyObjectDataPtr operatorFatherBool(const pyObjectData &other, const char* ope) const;
public:
	virtual float getDataFloat() const;
	virtual int getDataInt() const;
	pyObjectData();
	virtual ~pyObjectData() {};
	virtual string getType() const = 0;
	virtual operator bool() const = 0;
	virtual pyObjectPtr opePT(string memName) const;
	virtual pyObjectDataPtr operator+(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator-(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator-() const;
	virtual pyObjectDataPtr operator*(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator/(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator==(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator!=(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator<(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator>(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator<=(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator>=(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator%(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator<<(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator>>(const pyObjectData &other) const;
	pyObjectDataPtr operator&&(const pyObjectData &other) const;
	pyObjectDataPtr operator||(const pyObjectData &other) const;
	pyObjectDataPtr operator!() const;
	virtual pyObjectDataPtr operator&(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator|(const pyObjectData &other) const;
	virtual void print() const = 0;
};

class pyObjectInt : public pyObjectData {
	const int data;
public:
	virtual float getDataFloat() const;
	virtual int getDataInt() const;
	pyObjectInt(int _data);
	string getType() const;
	pyObjectDataPtr operator-() const;
	operator bool() const;
	operator int() const;
	void print() const;
};

class pyObjectBool : public pyObjectData {
	const bool data;
public:
	virtual float getDataFloat() const;
	virtual int getDataInt() const;
	pyObjectBool(bool _data);
	string getType() const;
	pyObjectDataPtr operator-() const;
	operator bool() const;
	operator int() const;
	void print() const;
};

class pyObjectFloat : public pyObjectData {
	const float data;
public:
	virtual float getDataFloat() const;
	virtual int getDataInt() const;
	pyObjectFloat(float _data);
	string getType() const;
	pyObjectDataPtr operator-() const;
	operator bool() const;
	void print() const;
};

class pyObjectString : public pyObjectData {
	const string data;
	float getDataFloat() const;
	int getDataInt() const;
	pyObjectDataPtr operatorFatherString(const pyObjectData &other, const char* ope) const;
public:
	pyObjectString(string _data);
	string getType() const;
	pyObjectDataPtr operator+(const pyObjectData &other) const;
	pyObjectDataPtr operator-() const;
	pyObjectDataPtr operator==(const pyObjectData &other) const;
	pyObjectDataPtr operator!=(const pyObjectData &other) const;
	pyObjectDataPtr operator<(const pyObjectData &other) const;
	pyObjectDataPtr operator>(const pyObjectData &other) const;
	pyObjectDataPtr operator<=(const pyObjectData &other) const;
	pyObjectDataPtr operator>=(const pyObjectData &other) const;
	operator bool() const;
	void print() const;
};
#endif