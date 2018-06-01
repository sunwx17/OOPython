#include "Function.h"
#include "Block.h"

pyObjectPtr pyFuncObject::call(vector<pyObjectPtr>& elems){
	return define->call(elems);
}
