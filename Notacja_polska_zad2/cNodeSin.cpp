#include"cNodeSin.h"
#include<cmath>

using namespace std;

cNodeSin::cNodeSin(cNode* pcParent)
	: cNode(pcParent) {

}

double cNodeSin::dGetValue() {
	if (!bIsCalculated()) {
		vSetValue(sin(vpcGetChildren()[0]->dGetValue()));
		vSetIsCalculated(true);
	}

	return dGetStoredValue();
}

int cNodeSin::iGetArity() {
	return I_ARITY_ONE;
}

int cNodeSin::iGetArityStatic() {
	return I_ARITY_ONE;
}

cNodeSin::cNodeSin(cNodeSin& cOther, cNode* pcNewParent)
	: cNode(cOther, pcNewParent) {
	const vector<cNode*>& vpcOtherChildren = cOther.vpcGetChildren();
	for (int i = 0; i < vpcOtherChildren.size(); ++i) {
		vAddChild(vpcOtherChildren[i]->pcClone(this));
	}
}

cNode* cNodeSin::pcClone(cNode* pcNewParent) {
	return new cNodeSin(*this, pcNewParent);
}