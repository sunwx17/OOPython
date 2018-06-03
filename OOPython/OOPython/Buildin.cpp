#include "Buildin.h"
#include "Function.h"

pyObjectPtr range(vector<pyObjectPtr> elems) {
	pyObjectContainerPtr ocp = new pyObjectList;
	int start = dynamic_cast<pyObjectInt*>(elems[0])->operator int();
	int end = dynamic_cast<pyObjectInt*>(elems[1])->operator int();
	for (int i = start; i < end; i++) {
		pyObjectDataPtr odp = new pyObjectInt(i);
		ocp->pushBack(odp);
	}
	return ocp;
}

map<string, pyObjectPtr> getBuildInMap(){
	map<string, pyObjectPtr> bim;
	bim["range"] = (pyObject*)new pyFuncObject(range);
	return bim;
}
