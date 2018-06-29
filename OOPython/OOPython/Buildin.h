#ifndef BUILDIN_H
#define BUILDIN_H

#include "Data.h"
#include <map>









pyObjectPtr pyListAppend(vector<pyObjectPtr>);//L.append(var)  #׷��Ԫ�أ����ؿ�
pyObjectPtr pyListInsert(vector<pyObjectPtr>);//L.insert(index, var)  #��λ��indexǰ������Ԫ��var�����ؿ�
pyObjectPtr pyListPop(vector<pyObjectPtr>);//L.pop(var)   #����λ��var��Ԫ�أ�Ĭ�����һ��Ԫ�أ�������list��ɾ��֮
pyObjectPtr pyListRemove(vector<pyObjectPtr>);//L.remove(var)  #ɾ����һ�γ��ֵĸ�Ԫ�أ����ؿ�
pyObjectPtr pyListCount(vector<pyObjectPtr>);//L.count(var)  #��Ԫ�����б��г��ֵĸ���
pyObjectPtr pyListIndex(vector<pyObjectPtr>);//L.index(var)  #��Ԫ�ص�λ�ã�int����, �������쳣
pyObjectPtr pyListExtend(vector<pyObjectPtr>);//L.extend(list) #�ϲ�list��L�ϣ����ؿ�
pyObjectPtr pyListSort(vector<pyObjectPtr>);//L.sort()    #���򣬷��ؿ�
pyObjectPtr pyListReverse(vector<pyObjectPtr>);//L.reverse()   #���򣬷��ؿ�
pyObjectPtr range(vector<pyObjectPtr>);
pyObjectPtr type(vector<pyObjectPtr>);
map<string, pyObjectPtr> getBuildInMap();

#endif // !BUILDIN_H
