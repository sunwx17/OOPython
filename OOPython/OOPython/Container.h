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
	pyObjectPtr friend pyListAppend(vector<pyObjectPtr>);//L.append(var)  #追加元素，返回空
	pyObjectPtr friend pyListInsert(vector<pyObjectPtr>);//L.insert(index, var)  #在位置index前插入新元素var，返回空
	pyObjectPtr friend pyListPop(vector<pyObjectPtr>);//L.pop(var)   #返回位置var的元素（默认最后一个元素），并从list中删除之
	pyObjectPtr friend pyListRemove(vector<pyObjectPtr>);//L.remove(var)  #删除第一次出现的该元素，返回空
	pyObjectPtr friend pyListCount(vector<pyObjectPtr>);//L.count(var)  #该元素在列表中出现的个数
	pyObjectPtr friend pyListIndex(vector<pyObjectPtr>);//L.index(var)  #该元素的位置（int对象）, 无则抛异常
	pyObjectPtr friend pyListExtend(vector<pyObjectPtr>);//L.extend(list) #合并list到L上，返回空
	pyObjectPtr friend pyListSort(vector<pyObjectPtr>);//L.sort()    #排序，返回空
	pyObjectPtr friend pyListReverse(vector<pyObjectPtr>);//L.reverse()   #倒序，返回空
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