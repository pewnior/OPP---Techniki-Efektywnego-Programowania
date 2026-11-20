#include "cNode.h"
#include "cNodePlus.h"
#include "cNodeValue.h"
#include<string>
#include<vector>

using namespace std;

cNode::cNode(cNode* pcParent) {
	pc_parent = pcParent;
	d_value = -1;
	b_is_calculated = false;
	b_division_0_flag = false;
	
}

cNode::cNode(const cNode& cOther, cNode* pcNewParent) {
	pc_parent = pcNewParent;
	d_value = cOther.d_value;
	b_is_calculated = cOther.b_is_calculated;
	b_division_0_flag = cOther.b_division_0_flag;
}

cNode::~cNode() {
	while (!vpc_children.empty()) {
		delete vpc_children.back();
		vpc_children.pop_back();
	}
}

cNode* cNode::pcGetParent() {
	return pc_parent;
}

bool cNode::bIsCalculated() {
	return b_is_calculated;
}
bool cNode::bIsComplete() {
	return iGetArity() == vpc_children.size();
}

void cNode::vAddChild(cNode* pcOtherNode) {
	if (!bIsComplete()) {
		vpc_children.push_back(pcOtherNode);
	}
}
vector<cNode*>& cNode::vpcGetChildren() {
	return vpc_children;
}

void cNode::vSetIsCalculated(bool bValue) {
	b_is_calculated = bValue;
}

bool cNode::bIsDivision0() {
	bool bResult = b_division_0_flag;
	int i = 0;

	while (i < vpc_children.size() && !bResult) {
		if (vpc_children[i]->bIsDivision0()) {
			bResult = true;
		}
		++i;
	}

	return bResult;
}

void cNode::vSetParent(cNode* pcParent) {
	pc_parent = pcParent;
}

void cNode::vSetDivision0Flag(bool bFlag) {
	b_division_0_flag = bFlag;
}

void cNode::vSetValue(double dVaule) {
	d_value = dVaule;
}

double cNode::dGetStoredValue() {
	return d_value;
}

void cNode::vCollectVariables(cTree* pcTree) {
	for (int i = 0; i < vpc_children.size(); ++i) {
		vpc_children[i]->vCollectVariables(pcTree);
	}
}

void cNode::vReplaceChild(int iIndex, cNode* pcNewChild) {
	if (iIndex >= 0 && iIndex < vpc_children.size()) {
		delete vpc_children[iIndex];
		vpc_children[iIndex] = pcNewChild;

		if (pcNewChild != NULL) {
			pcNewChild->vSetParent(this);
		}
	}
}