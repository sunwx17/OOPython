#ifndef FUNCTION_H
#define FUNCTION_H
#include "Data.h"
#include "Varmap.h"

class pyDefBlock;

class pyFuncObject : public pyObject {
	pyDefBlock* define = nullptr;
	pyObjectPtr(*buildInFunc)(vector <pyObjectPtr>);
public:
	pyFuncObject(pyDefBlock* def);
	pyFuncObject(pyObjectPtr(*bif)(vector <pyObjectPtr>));
	string getType() const;
	pyObjectPtr call(Varmap&, vector<pyObjectPtr>&);
	void print() const;
};

typedef shared_ptr<pyFuncObject> pyFuncObjectPtr;

#endif // !FUNCTION_H
