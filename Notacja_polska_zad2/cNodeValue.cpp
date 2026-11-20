#include"cNodeValue.h"

using namespace std;

cNodeValue::cNodeValue(cNode* pcParent, double dValue)
	: cNode(pcParent) {
	vSetIsCalculated(true);
	vSetValue(dValue);

}

cNodeValue::cNodeValue(cNode* pcParent)
	: cNode(pcParent) {
	vSetIsCalculated(true);
	vSetValue(D_VALUE_OF_DEFAULT_NODE);
}

double cNodeValue::dGetValue() {
	return dGetStoredValue();
}
int cNodeValue::iGetArity() {
	return I_ARITY_ZERO;
}

int cNodeValue::iGetArityStatic() {
	return I_ARITY_ZERO;
}

cNodeValue::cNodeValue(cNodeValue& cOther, cNode* pcNewParent)
	: cNode(cOther, pcNewParent) {
}

cNode* cNodeValue::pcClone(cNode* pcNewParent){
	return new cNodeValue(*this, pcNewParent);
}