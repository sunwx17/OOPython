#ifndef BUILDIN_H
#define BUILDIN_H

#include "Data.h"
#include <algorithm>
#include <map>
void initListMember();
pyObjectPtr pyListAppend(vector<pyObjectPtr>);//L.append(var)  #追加元素，返回空
pyObjectPtr pyListInsert(vector<pyObjectPtr>);//L.insert(index, var)  #在位置index前插入新元素var，返回空
pyObjectPtr pyListPop(vector<pyObjectPtr>);//L.pop(var)   #返回位置var的元素（默认最后一个元素），并从list中删除之
pyObjectPtr pyListCount(vector<pyObjectPtr>);//L.count(var)  #该元素在列表中出现的个数
pyObjectPtr pyListIndex(vector<pyObjectPtr>);//L.index(var)  #该元素的位置（int对象）, 无则抛异常
pyObjectPtr pyListExtend(vector<pyObjectPtr>);//L.extend(list) #合并list到L上，返回空
pyObjectPtr pyListSort(vector<pyObjectPtr>);//L.sort()    #排序，返回空
pyObjectPtr pyListReverse(vector<pyObjectPtr>);//L.reverse()   #倒序，返回空
pyObjectPtr range(vector<pyObjectPtr>);
pyObjectPtr type(vector<pyObjectPtr>);
map<string, pyObjectPtr> getBuildInMap();

#endif // !BUILDIN_H
