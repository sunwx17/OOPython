#include "Function.h"
#include "Block.h"

string pyFuncObject::getType() const{
	return "funcion";
}

pyObjectPtr pyFuncObject::call(Varmap& varmap, vector<pyObjectPtr>& elems){
	if (define != nullptr)
		return define->call(varmap, elems);
	else
		return (*buildInFunc)(elems);
}

void pyFuncObject::print() const{
	cout << "<function>";
}
