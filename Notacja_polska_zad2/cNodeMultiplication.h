#pragma once
#define CNODEMULTIPLICATION_H

#include "cNode.h"
#include<vector>

class cNodeMultiplication: public cNode {
public:
	cNodeMultiplication(cNode* pcParent);
	cNodeMultiplication(cNodeMultiplication& cOther, cNode* pcNewParent);

	cNode* pcClone(cNode* pcNewParent);

	double dGetValue();
	int iGetArity();
	static int iGetArityStatic();

private:


};