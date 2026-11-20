#pragma once
#define CNODEDIVISION_H

#include "cNode.h"
#include<vector>

class cNodeDivision : public cNode {
public:
	cNodeDivision(cNode* pcParent);
	cNodeDivision(cNodeDivision& cOther, cNode* pcNewParent);
	
	cNode* pcClone(cNode* pcNewParent);

	double dGetValue();
	int iGetArity();
	static int iGetArityStatic();

private:


};