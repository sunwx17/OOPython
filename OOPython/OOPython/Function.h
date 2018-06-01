#ifndef FUNCTION_H
#define FUNCTION_H
#include "Data.h"

class pyFuncObject : public pyObject {
public:
	pyFuncObject();
	string getType() const;
	void print();
};

typedef shared_ptr<pyFuncObject> pyFuncObjectPtr;

#endif // !FUNCTION_H
