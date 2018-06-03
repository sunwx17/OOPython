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
typedef shared_ptr<pyObjectData> pyObjectDataPtr;
typedef shared_ptr<pyObjectContainer> pyObjectContainerPtr;
typedef shared_ptr<pyObjectIterator> pyObjectIteratorPtr;
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
	virtual float getDataFloat() const = 0;
	virtual int getDataInt() const = 0;
public: 
	pyObjectData();
	virtual ~pyObjectData() {};
	virtual string getType() const = 0;
	virtual pyObjectDataPtr operator+(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator-(const pyObjectData &other) const;
	virtual pyObjectDataPtr operator-() const = 0;
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
	operator int() const;
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
	operator int() const;
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
	pyObjectDataPtr operator!=(const pyObjectData &other) const;
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
	virtual ~pyObjectContainer() {};
	virtual string getType() const = 0;
	virtual void print() const = 0;
	virtual pyObjectIteratorPtr begin()= 0;
	virtual pyObjectIteratorPtr end()= 0;
	virtual void pushBack(pyObjectPtr data) = 0;
	//virtual void insert(pyObjectPtr num, pyObjectPtr data) = 0;
	//virtual pyObjectDataPtr pop() = 0;
	//virtual pyObjectDataPtr pop(pyObjectPtr num) = 0;
	virtual int size() const = 0;
	virtual pyObjectPtr operator[](const pyObjectPtr pos) const = 0;
};

class pyObjectList : public pyObjectContainer {
	vector<pyObjectPtr> dataList;
public:
	pyObjectList();
	pyObjectList(vector<pyObjectPtr> _dataList);
	string getType() const;
	void print() const;
	pyObjectIteratorPtr begin();
	pyObjectIteratorPtr end();
	void pushBack(pyObjectPtr data);
	//void insert(pyObjectPtr num, pyObjectPtr data);
	//pyObjectPtr pop();
	//pyObjectPtr pop(pyObjectPtr num);
	int size() const;
	pyObjectPtr operator[](const pyObjectPtr pos) const;
};

class pyObjectIterator : public pyObject {
public:
	pyObjectIterator();
	virtual ~pyObjectIterator() {};
	virtual string getType() const = 0;
	virtual void print() const = 0;
	virtual pyObjectIteratorPtr operator+(int num) const = 0;
	virtual pyObjectIteratorPtr operator-(int num) const = 0;
	virtual pyObjectIteratorPtr operator++(int) = 0;
	virtual pyObjectIteratorPtr operator++() = 0;
	virtual pyObjectIteratorPtr operator--(int) = 0;
	virtual pyObjectIteratorPtr operator--() = 0;
	virtual pyObjectPtr operator*() const= 0;
	virtual bool operator==(const pyObjectIterator &other) const = 0;
	virtual bool operator!=(const pyObjectIterator &other) const = 0;
};

class pyIteratorList : public pyObjectIterator {
	vector<pyObjectPtr>::iterator it;
public:
	pyIteratorList();
	pyIteratorList(vector<pyObjectPtr>::iterator _it);
	string getType() const;
	void print() const;
	pyObjectIteratorPtr operator+(int num) const;
	pyObjectIteratorPtr operator-(int num) const;
	pyObjectIteratorPtr operator++(int);
	pyObjectIteratorPtr operator++();
	pyObjectIteratorPtr operator--(int);
	pyObjectIteratorPtr operator--();
	pyObjectPtr operator*() const;
	bool operator==(const pyObjectIterator &other) const;
	bool operator!=(const pyObjectIterator &other) const;
};
#endif