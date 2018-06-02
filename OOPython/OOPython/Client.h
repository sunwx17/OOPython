#ifndef CLIENT_H
#define CLIENT_H

#include "Data.h"
#include "Varmap.h"
#include "Block.h"
#include <string>
#include <iostream>
using namespace std;
//Ŀǰ���뷨��Data�������ݴ洢map<string,*Object>��Analyzer�����﷨����Keyword�����ʼ�������֣��൱��Grammar�ļ��У�
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
