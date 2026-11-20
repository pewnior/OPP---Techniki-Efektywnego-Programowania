#pragma once
#define CNODE_H

#include<string>
#include<vector>

using namespace std;

class cTree;

const int I_ARITY_ZERO = 0;
const int I_ARITY_ONE = 1;
const int I_ARITY_TWO = 2;


class cNode {
public:
	cNode(cNode* pcParent);
	cNode(const cNode& cOther, cNode* pcNewParent);
	virtual ~cNode();

	virtual cNode* pcClone(cNode* pcNewParent) = 0;
	virtual void vCollectVariables(cTree* pcTree);

	void vReplaceChild(int iIndex, cNode* pcNewChild);

	virtual bool bIsCalculated();
	virtual bool bIsComplete();
	virtual void vAddChild(cNode* pcOtherNode);
	virtual cNode* pcGetParent();
	virtual vector<cNode*>& vpcGetChildren();
	virtual void vSetIsCalculated(bool bValue);
	virtual bool bIsDivision0();

	virtual int iGetArity() = 0;
	virtual double dGetValue() = 0;

protected:
	virtual void vSetParent(cNode* pcParent);
	virtual void vSetDivision0Flag(bool bFlag);
	virtual void vSetValue(double dValue);
	virtual double dGetStoredValue();

private:
	cNode* pc_parent;
	vector<cNode*>vpc_children;
	double d_value;
	bool b_is_calculated;
	bool b_division_0_flag;
};

