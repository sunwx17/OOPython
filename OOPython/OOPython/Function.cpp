#include "Function.h"
#include "Block.h"

string pyFuncObject::getType() const{
	return "string";
}

pyObjectPtr pyFuncObject::call(vector<pyObjectPtr>& elems){
	return define->call(elems);
}

void pyFuncObject::print() const{
	cout << "<function>";
}
