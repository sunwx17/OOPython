#ifndef CLIENT_H
#define CLIENT_H

#include "Data.h"
#include "Varmap.h"
#include "Block.h"
#include <string>
#include <iostream>
using namespace std;
//目前的想法：Data负责数据存储map<string,*Object>，Analyzer负责语法树，Keyword负责初始化保留字（相当于Grammar文件夹）
class Client {
    istream &in;
	bool isCMD;
public:
    Client(istream& _in, bool _isCMD);
    bool getLine(string &s);
    void work();
	static bool scan(unsigned int &num, string &line);
	static bool deleteNote(string &line);
};
#endif
