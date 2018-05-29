#ifndef Client_H
#define Client_H

//#include "Data.h"
//#include "Analyzer.h"
#include "Grammar.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
//Ŀǰ���뷨��Data�������ݴ洢map<string,*Object>��Analyzer�����﷨����Keyword�����ʼ�������֣��൱��Grammar�ļ��У�
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
