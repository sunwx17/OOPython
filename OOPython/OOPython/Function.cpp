#include "Function.h"
#include "Block.h"

string pyFuncObject::getType() const{
	return "string";
}

pyObjectPtr pyFuncObject::call(Varmap& varmap, vector<pyObjectPtr>& elems){
	return define->call(varmap, elems);
}

void pyFuncObject::print() const{
	cout << "<function>";
}
