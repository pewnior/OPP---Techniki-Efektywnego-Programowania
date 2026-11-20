#pragma once
#define CNODECOS_H

#include "cNode.h"
#include<vector>

class cNodeCos : public cNode {
public:
	cNodeCos(cNode* pcParent);
	cNodeCos(cNodeCos& cOther, cNode* pcNewParent);

	cNode* pcClone(cNode* pcNewParent);

	double dGetValue();
	int iGetArity();
	static int iGetArityStatic();

private:


};