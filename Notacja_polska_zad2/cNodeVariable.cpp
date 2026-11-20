#include"cNodeVariable.h"
#include"cVariable.h"
#include"cNode.h"
#include"cTree.h"

using namespace std;

cNodeVariable::cNodeVariable(cNode* pcParent, string& sName)
	: cNode(pcParent) {
	s_name = sName;
}

double cNodeVariable::dGetValue() {
	return dGetStoredValue();;
}
int cNodeVariable::iGetArity() {
	return I_ARITY_ZERO;
}

void cNodeVariable::vChangeValue(double dNewValue) {
	vSetValue(dNewValue);
	vSetIsCalculated(true);

	cNode* pcActualNode = pcGetParent();
	while (pcActualNode != NULL) {
		pcActualNode->vSetIsCalculated(false);
		pcActualNode = pcActualNode->pcGetParent();
	}
}

int cNodeVariable::iGetArityStatic() {
	return I_ARITY_ZERO;
}

cNodeVariable::cNodeVariable(cNodeVariable& cOther, cNode* pcNewParent)
	: cNode(cOther, pcNewParent) {
	s_name = cOther.s_name;
}

cNode* cNodeVariable::pcClone(cNode* pcNewParent){
	return new cNodeVariable(*this, pcNewParent);
}

void cNodeVariable::vCollectVariables(cTree* pcTree) {
	pcTree->vCreateVariable(s_name, this);
}