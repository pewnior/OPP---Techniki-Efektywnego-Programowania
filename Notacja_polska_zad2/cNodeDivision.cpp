#include"cNodeDivision.h"

using namespace std;

cNodeDivision::cNodeDivision(cNode* pcParent)
	: cNode(pcParent) {

}

double cNodeDivision::dGetValue() {
	if (!bIsCalculated()) {
		if (vpcGetChildren()[1]->dGetValue() == 0) {
			vSetValue(0);
			vSetDivision0Flag(true);
		}
		else {
			vSetValue(vpcGetChildren()[0]->dGetValue() / vpcGetChildren()[1]->dGetValue());
			if (bIsDivision0()) {
				vSetDivision0Flag(false);
			}
		}
		vSetIsCalculated(true);
	}

	return dGetStoredValue();
}

int cNodeDivision::iGetArity() {
	return I_ARITY_TWO;
}

int cNodeDivision::iGetArityStatic() {
	return I_ARITY_TWO;
}

cNodeDivision::cNodeDivision(cNodeDivision& cOther, cNode* pcNewParent)
	: cNode(cOther, pcNewParent) {
	const vector<cNode*>& vpcOtherChildren = cOther.vpcGetChildren();
	for (int i = 0; i < vpcOtherChildren.size(); ++i) {
		vAddChild(vpcOtherChildren[i]->pcClone(this));
	}
}

cNode* cNodeDivision::pcClone(cNode* pcNewParent) {
	return new cNodeDivision(*this, pcNewParent);
}