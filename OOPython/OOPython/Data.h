#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <memory>
#include <assert.h>
using namespace std;
//Mark:To Do完成list、scan 

class pyObject;
class pyObjectData;
class pyObjectBool;
class pyObjectInt;
class pyObjectFloat;
class pyObjectContainer;
class pyObjectIterator;
typedef shared_ptr<pyObject> pyObjectPtr;
typedef shared_ptr<const pyObjectData> pyObjectDataPtr;
typedef shared_ptr<pyObjectContainer> pyObjectContainerPtr;
typedef shared_ptr<pyObjectIterator> pyObjectIteratorPtr;
//以下基础函数：operateInt、operateBool、operateFloat 
bool operateBool(const float& one, const float& other, const char* ope, bool& answer);
bool operateInt(const int& one, const int& other, const char* ope, int& answer);
bool operateFloat(const float& one, const float& other, const char* ope, float& answer);

//以下pyObject类及其子类
class pyObject{
public:
	pyObject();
	virtual ~pyObject() = 0;
	virtual string getType() const = 0;
	virtual void print() const = 0;
};

class pyObjectData :public pyObject {
	pyObjectDataPtr operatorFather(const pyObjectData &other, const char* ope) const;//string单独处理
	pyObjectDataPtr operatorFatherBool(const pyObjectData &other, const char* ope) const;
	virtual float getDataFloat() const = 0;
	virtual int getDataInt() const = 0;
public: 
	pyObjectData();
	virtual ~pyObjectData() = 0;
	virtual string getType() const = 0;
	virtual pyObjectDataPtr operator+(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator-(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator-() const = 0;
	virtual pyObjectDataPtr operator*(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator/(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator==(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator<(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator>(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator<=(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator>=(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator<<(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator>>(const pyObjectData &other) const;
	pyObjectDataPtr operator&&(const pyObjectData &other) const;
	pyObjectDataPtr operator||(const pyObjectData &other) const;
	pyObjectDataPtr operator!() const;
	virtual pyObjectDataPtr operator&(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator|(const pyObjectData &other) const;
	virtual operator bool() const = 0;
	virtual void print() const = 0;
};

class pyObjectInt : public pyObjectData {
	const int data;
	float getDataFloat() const;
	int getDataInt() const;
public:
	pyObjectInt(int _data);
	string getType() const;
	pyObjectDataPtr operator-() const;
	operator bool() const;
	void print() const;
};

class pyObjectBool : public pyObjectData {
	const bool data;
	float getDataFloat() const;
	int getDataInt() const;
public:
	pyObjectBool(bool _data);
	string getType() const;
	pyObjectDataPtr operator-() const;
	operator bool() const;
	void print() const;
};

class pyObjectFloat : public pyObjectData {
	const float data;
	float getDataFloat() const;
	int getDataInt() const;
public:
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
	pyObjectDataPtr operator<(const pyObjectData &other) const;
	pyObjectDataPtr operator>(const pyObjectData &other) const;
	pyObjectDataPtr operator<=(const pyObjectData &other) const;
	pyObjectDataPtr operator>=(const pyObjectData &other) const;
	operator bool() const;
	void print() const;
};

class pyObjectContainer : public pyObject {
public:
	pyObjectContainer();
	virtual ~pyObjectContainer() = 0;
	virtual string getType() const = 0;
	virtual void print() const = 0;
	virtual pyObjectIteratorPtr begin() = 0;
	virtual pyObjectIteratorPtr end() = 0;
	virtual void pushBack(pyObjectPtr data) = 0;
	//virtual void insert(pyObjectPtr num, pyObjectPtr data) = 0;
	//virtual pyObjectDataPtr pop() = 0;
	//virtual pyObjectDataPtr pop(pyObjectPtr num) = 0;
	virtual int size() = 0;
	virtual pyObjectDataPtr operator[](pyObjectPtr pos) = 0;
};

class pyObjectList : public pyObjectContainer {
	vector<pyObjectPtr> dataList;
public:
	virtual string getType() const;
	virtual void print() const;
	virtual pyObjectIteratorPtr begin();
	virtual pyObjectIteratorPtr end();
	virtual void pushBack(pyObjectPtr data);
	//virtual void insert(pyObjectPtr num, pyObjectPtr data);
	//virtual pyObjectDataPtr pop();
	//virtual pyObjectDataPtr pop(pyObjectPtr num);
	virtual int size();
	virtual pyObjectDataPtr operator[](pyObjectPtr pos);
};

class pyObjectIterator : public pyObject {
public:
	pyObjectIterator();
	virtual ~pyObjectIterator() = 0;
	virtual string getType() const = 0;
	virtual void print() = 0;
	virtual pyObjectIteratorPtr operator+(int num) const = 0;
	virtual pyObjectIteratorPtr operator-(int num) const = 0;
	virtual pyObjectIteratorPtr operator++(int) = 0;
	virtual pyObjectIteratorPtr operator++() = 0;
	virtual pyObjectIteratorPtr operator--(int) = 0;
	virtual pyObjectIteratorPtr operator--() = 0;
	virtual pyObjectIteratorPtr operator*() const= 0;
	virtual bool operator==(const pyObjectIterator &other) const = 0;
	virtual bool operator!=(const pyObjectIterator &other) const = 0;
};
#endif