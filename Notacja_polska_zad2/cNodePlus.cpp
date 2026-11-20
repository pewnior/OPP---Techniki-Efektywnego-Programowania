#include"cNodePlus.h"

using namespace std;

cNodePlus::cNodePlus(cNode* pcParent) 
	: cNode(pcParent) {

}

double cNodePlus::dGetValue() {
	if (!bIsCalculated()) {
		vSetValue(vpcGetChildren()[0]->dGetValue() + vpcGetChildren()[1]->dGetValue());
		vSetIsCalculated(true);
	}

	return dGetStoredValue();
}

int cNodePlus::iGetArity() {
	return I_ARITY_TWO;
}

int cNodePlus::iGetArityStatic() {
	return I_ARITY_TWO;
}

cNodePlus::cNodePlus(cNodePlus& cOther, cNode* pcNewParent)
	: cNode(cOther, pcNewParent) {
	const vector<cNode*>& vpcOtherChildren = cOther.vpcGetChildren();
	for (int i = 0; i < vpcOtherChildren.size(); ++i) {
		vAddChild(vpcOtherChildren[i]->pcClone(this));
	}
}

cNode* cNodePlus::pcClone(cNode* pcNewParent){
	return new cNodePlus(*this, pcNewParent);
}
