#pragma once
#define CNODEPLUS_H

#include "cNode.h"
#include<vector>

class cNodePlus : public cNode {
public:
	cNodePlus(cNode* pcParent);
	cNodePlus(cNodePlus& cOther, cNode* pcNewParent);

	cNode* pcClone(cNode* pcNewParent);

	double dGetValue();
	int iGetArity();
	static int iGetArityStatic();

private:
	

};