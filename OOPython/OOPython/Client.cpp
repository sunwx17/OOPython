//Client.cpp
#include "Client.h"

Client::Client(istream& _in, bool _isCMD) : in(_in), isCMD(_isCMD) {}

bool Client::getLine(string &s)
{
	bool notEOF = !(getline(in, s).eof());
    return notEOF;
}

void Client::work()
{
	pyRootBlock* rootBlock = new pyRootBlock;
	Varmap varmap;
	bool flagExit = false;
	bool outState = true;//���״̬��1���">>> "��0���"... "
    while (!flagExit)
    {
		if (isCMD) {
			if (outState)
				cout << ">>> ";
			else
				cout << "... ";
		}
        string line;
		bool endOfFile = !(getLine(line));
		if (endOfFile) {
			break;
		}
		if (line == "") {
			outState = true;
			continue;
		}
		unsigned int numOfTab = 0;
		bool isEmpty = deleteNote(line);
		bool tabCorrect = scan(numOfTab, line);//��Ĭ��correct
		if (!tabCorrect) {
			cout << "��������!" << endl;
			continue;
		}
		//do something with "numOfTab" and "line"��ǰ��Ϊ������������Ϊ�����������У�
		int type = rootBlock->appendProcess(line, numOfTab);
		//���ﷵ�ش����Ŀ�����(��Analyzer.cpp��������ʽ��˳��)�����numOdTab,�ж��� >>> ���� ...
		if ((type >= 0) && (type <= 4)) {
			outState = false;
		}
		if (outState) {
			int workStatus = rootBlock->lastWork(1, varmap);
			if (workStatus == 5) {
				flagExit = true;
			}
		}
    }
	delete rootBlock;
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
	//cout << line << endl << num << endl;
	return tabCorrect;
}

bool Client::deleteNote(string &line) {
	bool isEmpty = true;
	int size = (int)line.size();
	for (int i = 0; i < size; i++) {
		if (line[i] == '#') {
			line.erase(i);
			break;
		}
		if ((line[i] != '\t') && (line[i] != ' ')) {
			isEmpty = false;
		}
	}
	return isEmpty;
}