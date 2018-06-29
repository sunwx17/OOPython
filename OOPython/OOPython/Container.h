#ifndef CONTAINER_H
#define CONTAINER_H

#include "Data.h"

class pyObjectContainer;
class pyObjectList;
class pyObjectIterator;
typedef shared_ptr<pyObjectContainer> pyObjectContainerPtr;
typedef shared_ptr<pyObjectList> pyObjectListPtr;
typedef shared_ptr<pyObjectIterator> pyObjectIteratorPtr;
void initListMember();
class pyObjectContainer : public pyObjectData {
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
	virtual pyObjectPtr& operator[](const pyObjectPtr pos) = 0;
	virtual operator bool() const = 0;
};
class pyObjectList : public pyObjectContainer {
	vector<pyObjectPtr> dataList;
	static map<string, pyObjectPtr> member;
	void friend initListMember();
	pyObjectPtr friend pyListAppend(vector<pyObjectPtr>);//L.append(var)  #׷��Ԫ�أ����ؿ�
	pyObjectPtr friend pyListInsert(vector<pyObjectPtr>);//L.insert(index, var)  #��λ��indexǰ������Ԫ��var�����ؿ�
	pyObjectPtr friend pyListPop(vector<pyObjectPtr>);//L.pop(var)   #����λ��var��Ԫ�أ�Ĭ�����һ��Ԫ�أ�������list��ɾ��֮
	pyObjectPtr friend pyListRemove(vector<pyObjectPtr>);//L.remove(var)  #ɾ����һ�γ��ֵĸ�Ԫ�أ����ؿ�
	pyObjectPtr friend pyListCount(vector<pyObjectPtr>);//L.count(var)  #��Ԫ�����б��г��ֵĸ���
	pyObjectPtr friend pyListIndex(vector<pyObjectPtr>);//L.index(var)  #��Ԫ�ص�λ�ã�int����, �������쳣
	pyObjectPtr friend pyListExtend(vector<pyObjectPtr>);//L.extend(list) #�ϲ�list��L�ϣ����ؿ�
	pyObjectPtr friend pyListSort(vector<pyObjectPtr>);//L.sort()    #���򣬷��ؿ�
	pyObjectPtr friend pyListReverse(vector<pyObjectPtr>);//L.reverse()   #���򣬷��ؿ�
public:
	pyObjectList();
	pyObjectList(vector<pyObjectPtr> _dataList);
	string getType() const;
	void print() const;
	virtual pyObjectPtr opePT(string memName) const;
	pyObjectIteratorPtr begin();
	pyObjectIteratorPtr end();
	void pushBack(pyObjectPtr data);
	//void insert(pyObjectPtr num, pyObjectPtr data);
	//pyObjectPtr pop();
	//pyObjectPtr pop(pyObjectPtr num);
	int size() const;
	pyObjectPtr& operator[](const pyObjectPtr pos);
	virtual operator bool() const;
};

class pyObjectIterator : public pyObjectData, public enable_shared_from_this<pyObjectIterator> {
public:
	pyObjectIterator();
	virtual ~pyObjectIterator() {};
	virtual string getType() const = 0;
	virtual void print() const = 0;
	virtual operator bool() const = 0;
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
	virtual operator bool() const;
};
#endif