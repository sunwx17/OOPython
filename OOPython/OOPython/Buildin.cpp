#include "Buildin.h"
#include "Function.h"

pyObjectPtr range(vector<pyObjectPtr> elems) {
	pyObjectContainerPtr ocp = (pyObjectContainerPtr)(pyObjectContainer*)new pyObjectList;
	int start = 0, end, len = 1;
	if (elems.size() >= 2) {
		start = dynamic_cast<pyObjectInt*>(elems[0].get())->operator int();
		end = dynamic_cast<pyObjectInt*>(elems[1].get())->operator int();
		if (elems.size() == 3) {
			len = dynamic_cast<pyObjectInt*>(elems[2].get())->operator int();
		}
	}
	else if (elems.size() == 1){
		end = dynamic_cast<pyObjectInt*>(elems[0].get())->operator int();
	}
	for (int i = start; i < end; i += len) {
		pyObjectPtr odp = (pyObjectPtr)(pyObject*)new pyObjectInt(i);
		ocp->pushBack(odp);
	}
	return ocp;
}

map<string, pyObjectPtr> getBuildInMap(){
	map<string, pyObjectPtr> bim;
	bim["range"] = (pyObjectPtr)(pyObject*)new pyFuncObject(range);
	return bim;
}
