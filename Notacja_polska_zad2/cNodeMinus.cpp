#include"cNodeMinus.h"

using namespace std;

cNodeMinus::cNodeMinus(cNode* pcParent)
	: cNode(pcParent) {

}

double cNodeMinus::dGetValue() {
	if (!bIsCalculated()) {
		vSetValue(vpcGetChildren()[0]->dGetValue() - vpcGetChildren()[1]->dGetValue());
		vSetIsCalculated(true);
	}

	return dGetStoredValue();
}

int cNodeMinus::iGetArity() {
	return I_ARITY_TWO;
}

int cNodeMinus::iGetArityStatic() {
	return I_ARITY_TWO;
}

cNodeMinus::cNodeMinus(cNodeMinus& cOther, cNode* pcNewParent)
	: cNode(cOther, pcNewParent) {
	const vector<cNode*>& vpcOtherChildren = cOther.vpcGetChildren();
	for (int i = 0; i < vpcOtherChildren.size(); ++i) {
		vAddChild(vpcOtherChildren[i]->pcClone(this));
	}
}

cNode* cNodeMinus::pcClone(cNode* pcNewParent) {
	return new cNodeMinus(*this, pcNewParent);
}