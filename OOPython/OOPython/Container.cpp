//Container.cpp
#include "Container.h"
#include "Function.h"
//初始化函数及静态成员
map<string, pyObjectPtr> pyObjectList::member = {};
bool pyObjectList::notInit = true;
void initListMember() {
	pyObjectList::member["append"] = (pyObjectPtr)(pyObject*)new pyFuncObject(pyListAppend);
	pyObjectList::member["insert"] = (pyObjectPtr)(pyObject*)new pyFuncObject(pyListInsert);
	pyObjectList::member["pop"] = (pyObjectPtr)(pyObject*)new pyFuncObject(pyListPop);
	pyObjectList::member["count"] = (pyObjectPtr)(pyObject*)new pyFuncObject(pyListCount);
	pyObjectList::member["index"] = (pyObjectPtr)(pyObject*)new pyFuncObject(pyListIndex);
	pyObjectList::member["extend"] = (pyObjectPtr)(pyObject*)new pyFuncObject(pyListExtend);
	pyObjectList::member["sort"] = (pyObjectPtr)(pyObject*)new pyFuncObject(pyListSort);
	pyObjectList::member["reverse"] = (pyObjectPtr)(pyObject*)new pyFuncObject(pyListReverse);
}
//构造析构函数
pyObjectContainer::pyObjectContainer() {}
pyObjectList::pyObjectList() {
	if (notInit) {
		initListMember();
		notInit = false;
	}
}
pyObjectList::pyObjectList(vector<pyObjectPtr> _dataList) : dataList(_dataList) {
	if (notInit) {
		initListMember();
		notInit = false;
	}
}
pyObjectIterator::pyObjectIterator() {}
pyIteratorList::pyIteratorList() {}
pyIteratorList::pyIteratorList(vector<pyObjectPtr>::iterator _it) : it(_it) {}
//以下pyObjectList的函数
string pyObjectList::getType() const {
	return "list";
}
void pyObjectList::print() const {
	int num = size();
	cout << "[";
	for (int i = 0; i < num; i++) {
		dataList[i]->print();
		if (i == num - 1) {
			cout << "]";
		}
		else {
			cout << ", ";
		}
	}
}
pyObjectPtr pyObjectList::opePT(string memName) const {
	if (member.count(memName) == 0) {
		return nullptr;
	}
	else {
		return member[memName];
	}
}
pyObjectIteratorPtr pyObjectList::begin() {
	vector<pyObjectPtr>::iterator tmpIt = dataList.begin();
	return (pyObjectIteratorPtr)new pyIteratorList(tmpIt);
}
pyObjectIteratorPtr pyObjectList::end() {
	vector<pyObjectPtr>::iterator tmpIt = dataList.end();
	return (pyObjectIteratorPtr)new pyIteratorList(tmpIt);
}
void pyObjectList::pushBack(pyObjectPtr data) {
	dataList.push_back(data);
}
//void pyObjectList::insert(pyObjectPtr num, pyObjectPtr data);
//pyObjectDataPtr pyObjectList::pop();
//pyObjectDataPtr pyObjectList::pop(pyObjectPtr num);
int pyObjectList::size() const {
	return (int)dataList.size();
}
pyObjectPtr pyObjectList::operator[](const pyObjectPtr pos) const {
	const pyObjectInt* tmp1 = dynamic_cast<const pyObjectInt*>(&(*pos));
	if (tmp1 != nullptr) {
		return dataList[tmp1->operator int()];
	}
	const pyObjectBool* tmp2 = dynamic_cast<const pyObjectBool*>(&(*pos));
	if (tmp2 != nullptr) {
		return dataList[tmp2->operator int()];
	}
	return nullptr;
}
pyObjectList::operator bool() const {
	return !(dataList.empty());
}
//以下pyIteratorList类的函数
string pyIteratorList::getType() const {
	return "iteratorList";
}
void pyIteratorList::print() const {
	(*it)->print();
}
pyObjectIteratorPtr pyIteratorList::operator+(int num) const {
	return (pyObjectIteratorPtr)new pyIteratorList(it + num);
}
pyObjectIteratorPtr pyIteratorList::operator-(int num) const {
	return (pyObjectIteratorPtr)new pyIteratorList(it - num);
}
pyObjectIteratorPtr pyIteratorList::operator++(int) {
	pyObjectIteratorPtr tmp = (pyObjectIteratorPtr)new pyIteratorList(it);
	it++;
	return tmp;
}
pyObjectIteratorPtr pyIteratorList::operator++() {
	it++;
	return shared_from_this();
}
pyObjectIteratorPtr pyIteratorList::operator--(int) {
	pyObjectIteratorPtr tmp = (pyObjectIteratorPtr)new pyIteratorList(it);
	it--;
	return tmp;
}
pyObjectIteratorPtr pyIteratorList::operator--() {
	it--;
	return shared_from_this();
}
pyObjectPtr pyIteratorList::operator*() const {
	return *it;
}
bool pyIteratorList::operator==(const pyObjectIterator &other) const {
	const pyIteratorList* tmp = dynamic_cast<const pyIteratorList*>(&(other));
	if (tmp != nullptr) {
		return (tmp->it == this->it);
	}
	return false;
}
bool pyIteratorList::operator!=(const pyObjectIterator &other) const {
	const pyIteratorList* tmp = dynamic_cast<const pyIteratorList*>(&(other));
	if (tmp != nullptr) {
		return (tmp->it != this->it);
	}
	return false;
}
pyIteratorList::operator bool() const {
	pyObject * tmp1 = &(*(*it));
	pyObjectData * tmp2 = dynamic_cast<pyObjectData*>(tmp1);
	if (tmp2 == nullptr) {
		return true;
	}
	else {
		return tmp2->operator bool();
	}
}