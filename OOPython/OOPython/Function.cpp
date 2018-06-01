#include "Function.h"
#include "Analyzer.h"

pyObjectPtr pyFuncObject::call(vector<pyObjectPtr>& elems){
	return define->call(elems);
}
