//Client.cpp
#include "Client.h"

Client::Client(istream& _in) : in(_in) {}

bool Client::getLine(string &s)
{
	bool notEOF = !(getline(in, s).eof());
    return notEOF;
}

void Client::work()
{
	pyBlock* rootBlock = new pyRootBlock;
	bool flagExit = false;
    while (!flagExit)
    {
        string line;
		bool endOfFile = !(getLine(line));
		if (endOfFile) {
			break;
		}
		unsigned int numOfTab = 0;
		bool tabCorrect = scan(numOfTab, line);//��Ĭ��correct
		if (!tabCorrect) {
			cout << "��������" << endl;
			continue;
		}
		//do something with "numOfTab" and "line"��ǰ��Ϊ������������Ϊ�����������У�
		int type = rootBlock->appendProcess(line, numOfTab);
		//���ﷵ�ش����Ŀ�����(��Analyzer.cpp��������ʽ��˳��)�����numOdTab,�ж��� >>> ���� ...
    }
    return;
}

bool Client::scan(unsigned int &num, string &line) {
	bool tabCorrect = true;
	num = 0;
	while ((line.begin() != line.end()) && tabCorrect) {
		if (line[0] == '\t') {
			num++;
			line.erase(line.begin());
		}
		else if (line[0] == ' ') {
			for (int i = 1; i < 4; i++) {
				if (line[i] != ' ') {
					tabCorrect = false;
					break;
				}
			}
			if (tabCorrect) {
				num++;
				for (int i = 0; i < 4; i++) {
					line.erase(line.begin());
				}
			}
		}
		else {
			break;
		}
	}
	cout << line << endl << num << endl;
	return tabCorrect;
}
