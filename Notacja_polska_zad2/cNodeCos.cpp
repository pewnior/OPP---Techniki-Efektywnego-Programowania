#include"cNodeCos.h"
#include<cmath>

using namespace std;

cNodeCos::cNodeCos(cNode* pcParent)
	: cNode(pcParent) {

}

double cNodeCos::dGetValue() {
	if (!bIsCalculated()) {
		vSetValue(cos(vpcGetChildren()[0]->dGetValue()));
		vSetIsCalculated(true);
	}

	return dGetStoredValue();
}

int cNodeCos::iGetArity() {
	return I_ARITY_ONE;
}

int cNodeCos::iGetArityStatic() {
	return I_ARITY_ONE;
}

cNodeCos::cNodeCos(cNodeCos& cOther, cNode* pcNewParent)
	: cNode(cOther, pcNewParent) {
	const vector<cNode*>& vpcOtherChildren = cOther.vpcGetChildren();
	for (int i = 0; i < vpcOtherChildren.size(); ++i) {
		vAddChild(vpcOtherChildren[i]->pcClone(this));
	}
}

cNode* cNodeCos::pcClone(cNode* pcNewParent) {
	return new cNodeCos(*this, pcNewParent);
}