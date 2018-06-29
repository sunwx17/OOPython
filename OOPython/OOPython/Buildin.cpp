#include "Data.h"
#include "Buildin.h"
#include "Function.h"
#include "Container.h"
pyObjectPtr range(vector<pyObjectPtr> elems) {
	pyObjectContainerPtr ocp = (pyObjectContainerPtr)(pyObjectContainer*)new pyObjectList;
	int start = 0, end, len = 1;
	if (elems.size() >= 2) {
		start = dynamic_cast<pyObjectInt*>(elems[0].get())->operator int();
		end = dynamic_cast<pyObjectInt*>(elems[1].get())->operator int();
		if (elems.size() == 3) {
			len = dynamic_cast<pyObjectInt*>(elems[2].get())->operator int();
		}
	}
	else if (elems.size() == 1){
		end = dynamic_cast<pyObjectInt*>(elems[0].get())->operator int();
	}
	for (int i = start; i < end; i += len) {
		pyObjectPtr odp = (pyObjectPtr)(pyObject*)new pyObjectInt(i);
		ocp->pushBack(odp);
	}
	return ocp;
}

pyObjectPtr type(vector<pyObjectPtr> elems) {
	pyObjectPtr op = (pyObjectPtr)(pyObject*)new pyObjectString(elems[0]->getType());
	return op;
}

map<string, pyObjectPtr> getBuildInMap(){
	map<string, pyObjectPtr> bim;
	bim["range"] = (pyObjectPtr)(pyObject*)new pyFuncObject(range);
	bim["type"] = (pyObjectPtr)(pyObject*)new pyFuncObject(type);
	initListMember();
	return bim;
}

pyObjectPtr pyListAppend(vector<pyObjectPtr> elems) {
	assert(elems.size() == 2);
	assert((elems[0])->getType() == "list");
	pyObjectListPtr _self = dynamic_pointer_cast<pyObjectList>(elems[0]);
	_self->dataList.push_back(elems[1]);
	return nullptr;
}
pyObjectPtr pyListInsert(vector<pyObjectPtr> elems) {
	assert(elems.size() == 3);
	assert((elems[0])->getType() == "list");
	assert((elems[1])->getType() == "int");
	pyObjectListPtr _self = dynamic_pointer_cast<pyObjectList>(elems[0]);
	pyObjectDataPtr _index = dynamic_pointer_cast<pyObjectData>(elems[1]);
	int intIndex = _index->getDataInt();
	_self->dataList.insert(_self->dataList.begin()+intIndex, elems[2]);
	return nullptr;
}
pyObjectPtr pyListPop(vector<pyObjectPtr> elems) {
	assert((elems[0])->getType() == "list");
	pyObjectListPtr _self = dynamic_pointer_cast<pyObjectList>(elems[0]);
	switch (elems.size())
	{
	case 1: {
		pyObjectPtr returnPtr = *(_self->dataList.rbegin());
		_self->dataList.pop_back();
		return returnPtr;
	}
	case 2: {
		assert((elems[1])->getType() == "int");
		pyObjectDataPtr _index = dynamic_pointer_cast<pyObjectData>(elems[1]);
		int intIndex = _index->getDataInt();
		pyObjectPtr returnPtr = *(_self->dataList.begin() + intIndex);
		_self->dataList.erase(_self->dataList.begin() + intIndex);
		return returnPtr;
	}
	default:
		assert(false);
		return nullptr;
	}
}
pyObjectPtr pyListRemove(vector<pyObjectPtr> elems) {
	assert(elems.size() == 2);
	assert((elems[0])->getType() == "list");
	vector<pyObjectPtr> _list = dynamic_pointer_cast<pyObjectList>(elems[0])->dataList;
	for (auto i = _list.begin(); i != _list.end(); i++) {
		if (*i == elems[1]) {
			_list.erase(i);
			break;
		}
	}
	return nullptr;
}
pyObjectPtr pyListCount(vector<pyObjectPtr> elems) {
	assert(elems.size() == 2);
	assert((elems[0])->getType() == "list");
	vector<pyObjectPtr> _list = dynamic_pointer_cast<pyObjectList>(elems[0])->dataList;
	int num = 0;
	for (auto i = _list.begin(); i != _list.end(); i++) {
		if (*i == elems[1]) {
			num++;
		}
	}
	return (pyObjectPtr)new pyObjectInt(num);
}
pyObjectPtr pyListIndex(vector<pyObjectPtr> elems) {
	assert(elems.size() == 2);
	assert((elems[0])->getType() == "list");
	vector<pyObjectPtr> _list = dynamic_pointer_cast<pyObjectList>(elems[0])->dataList;
	int num = 0;
	for (auto i = _list.begin(); i != _list.end(); i++) {
		if (*i == elems[1]) {
			break;
		}
		num++;
	}
	return (pyObjectPtr)new pyObjectInt(num);
}
pyObjectPtr pyListExtend(vector<pyObjectPtr> elems) {
	assert(elems.size() == 2);
	assert((elems[0])->getType() == "list");
	assert((elems[1])->getType() == "list");
	vector<pyObjectPtr> _list = dynamic_pointer_cast<pyObjectList>(elems[0])->dataList;
	vector<pyObjectPtr> _other = dynamic_pointer_cast<pyObjectList>(elems[1])->dataList;
	_list.insert(_list.end(), _other.begin(), _other.end());
	return nullptr;
}
pyObjectPtr pyListSort(vector<pyObjectPtr> elems) {
	assert(elems.size() == 1);
	assert((elems[0])->getType() == "list");
	vector<pyObjectPtr> _list = dynamic_pointer_cast<pyObjectList>(elems[0])->dataList;
	sort(_list.begin(), _list.end());
	return nullptr;
}
pyObjectPtr pyListReverse(vector<pyObjectPtr> elems) {
	assert(elems.size() == 1);
	assert((elems[0])->getType() == "list");
	vector<pyObjectPtr> _list = dynamic_pointer_cast<pyObjectList>(elems[0])->dataList;
	reverse(_list.begin(), _list.end());
	return nullptr;
}