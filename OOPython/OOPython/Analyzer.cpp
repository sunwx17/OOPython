#include "Analyzer.h"

void pyBlock::appendProcess(const string& s, int numOfTab) {
	pyBlock* lastProcess = process.back();
	lastProcess->appendProcess(s, numOfTab - 1);
}

void pyBlock::work() {
	for (auto i : process) {
		i->work();
	}
}

void pyRootBlock::appendProcess(const string& s, int numOfTab) {
	
}

void pyRootBlock::work() {
	pyBlock::work();
}