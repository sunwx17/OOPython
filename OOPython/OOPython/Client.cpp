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
		bool tabCorrect = scan(numOfTab, line);//先默认correct
		if (!tabCorrect) {
			cout << "缩进错误" << endl;
			continue;
		}
		//do something with "numOfTab" and "line"（前者为缩进数，后者为不带缩进的行）
		int type = rootBlock->appendProcess(line, numOfTab);
		//这里返回创建的块类型(见Analyzer.cpp中正则表达式的顺序)，配合numOdTab,判断用 >>> 还是 ...
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
