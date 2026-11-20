#pragma once
#define CNODEVARIABLE_H

#include "cNode.h"
#include<vector>

class cNodeVariable : public cNode {
public:
	cNodeVariable(cNode* pcParent, string& sName);
	cNodeVariable(cNodeVariable& cOther, cNode* pcNewParent);

	cNode* pcClone(cNode* pcNewParent);
	void vCollectVariables(cTree* pcTree);
	double dGetValue();
	int iGetArity();
	void vChangeValue(double dNewValue);
	static int iGetArityStatic();


private:
	string s_name;
};
