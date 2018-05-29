#ifndef Client_H
#define Client_H

//#include "Data.h"
//#include "Analyzer.h"
#include "Grammar.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
//目前的想法：Data负责数据存储map<string,*Object>，Analyzer负责语法树，Keyword负责初始化保留字（相当于Grammar文件夹）
class Client
{
protected:
    istream &in;

public:
    Client(istream& _in = cin);
    bool getLine(string &s);
    void work();
	static bool scan(unsigned int &num, string &line);
};



#endif
