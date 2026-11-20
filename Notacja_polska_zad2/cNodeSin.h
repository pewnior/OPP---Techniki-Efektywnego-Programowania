#pragma once
#define CNODESIN_H

#include "cNode.h"
#include<vector>

class cNodeSin : public cNode {
public:
	cNodeSin(cNode* pcParent);
	cNodeSin(cNodeSin& cOther, cNode* pcNewParent);

	cNode* pcClone(cNode* pcNewParent);

	double dGetValue();
	int iGetArity();
	static int iGetArityStatic();

private:


};