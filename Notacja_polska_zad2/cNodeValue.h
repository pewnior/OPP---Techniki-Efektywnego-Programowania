#pragma once
#define CNODEVALUE_H

#include "cNode.h"
#include<vector>

const double D_VALUE_OF_DEFAULT_NODE = 1;

class cNodeValue : public cNode {
public:
	cNodeValue(cNode* pcParent, double dValue);
	cNodeValue(cNode* pcParent);
	cNodeValue(cNodeValue& cOther, cNode* pcNewParent);

	cNode* pcClone(cNode* pcNewParent);

	double dGetValue();
	int iGetArity();
	static int iGetArityStatic();

private:

};
