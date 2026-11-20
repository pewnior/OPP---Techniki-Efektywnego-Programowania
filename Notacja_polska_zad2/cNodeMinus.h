#pragma once
#define CNODEMINUS_H

#include "cNode.h"
#include<vector>

class cNodeMinus : public cNode {
public:
	cNodeMinus(cNode* pcParent);
	cNodeMinus(cNodeMinus& cOther, cNode* pcNewParent);

	cNode* pcClone(cNode* pcNewParent);

	double dGetValue();
	int iGetArity();
	static int iGetArityStatic();

private:


};