#include"cNodeMultiplication.h"

using namespace std;

cNodeMultiplication::cNodeMultiplication(cNode* pcParent)
	: cNode(pcParent) {

}

double cNodeMultiplication::dGetValue() {
	if (!bIsCalculated()) {
		vSetValue(vpcGetChildren()[0]->dGetValue() * vpcGetChildren()[1]->dGetValue());
		vSetIsCalculated(true);
	}

	return dGetStoredValue();
}

int cNodeMultiplication::iGetArity() {
	return I_ARITY_TWO;
}

int cNodeMultiplication::iGetArityStatic() {
	return I_ARITY_TWO;
}

cNodeMultiplication::cNodeMultiplication(cNodeMultiplication& cOther, cNode* pcNewParent)
	: cNode(cOther, pcNewParent) {
	const vector<cNode*>& vpcOtherChildren = cOther.vpcGetChildren();
	for (int i = 0; i < vpcOtherChildren.size(); ++i) {
		vAddChild(vpcOtherChildren[i]->pcClone(this));
	}
}

cNode* cNodeMultiplication::pcClone(cNode* pcNewParent) {
	return new cNodeMultiplication(*this, pcNewParent);
}