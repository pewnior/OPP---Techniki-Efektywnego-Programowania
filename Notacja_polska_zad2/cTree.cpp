#include"cTree.h"
#include"cNode.h"
#include"cNodeVariable.h"
#include"cNodePlus.h"
#include"cNodeValue.h"
#include"cNodeMinus.h"
#include"cNodeMultiplication.h"
#include"cNodeDivision.h"
#include"cNodeSin.h"
#include"cNodeCos.h"
#include"cInterface.h"
#include<vector>
#include<string>
#include<sstream>
#include <algorithm>

using namespace std;

cTree::cTree() {
	pc_root = NULL;
}

cTree::cTree(const cTree& cOther) {
	pc_root = NULL;
	vs_formula = cOther.vs_formula;

	if (cOther.pc_root != NULL) {
		pc_root = cOther.pc_root->pcClone(NULL);
		vRebuildVariables();
	}
}

cTree::~cTree() {
	if (pc_root != NULL) {
		delete pc_root;
	}
	while (!vpc_variables.empty()) {
		delete vpc_variables.back();
		vpc_variables.pop_back();
	}
}

void cTree::vRebuildVariables() {
	while (!vpc_variables.empty()) {
		delete vpc_variables.back();
		vpc_variables.pop_back();
	}

	if (pc_root != NULL) {
		pc_root->vCollectVariables(this);
	}
}

cTree& cTree::operator=(const cTree& cOther) {
	if (this != &cOther) {
		cTree cTemp(cOther);
		swap(pc_root, cTemp.pc_root);
		vpc_variables.swap(cTemp.vpc_variables);
		vs_formula.swap(cTemp.vs_formula);
	}
	
	return *this;
}

cTree cTree::operator+(const cTree& cOther) const {
	if (pc_root == NULL) { 
		return cOther;
	}
	if (cOther.pc_root == NULL) {
		return *this;
	}

	cTree cResult(*this);
	cNode* pcClonedOtherRoot = cOther.pc_root->pcClone(NULL);
	cNode* pcActualNode = cResult.pc_root;

	while (pcActualNode->vpcGetChildren().size() != 0) {
		pcActualNode = pcActualNode->vpcGetChildren()[0];
	}

	if (pcActualNode->pcGetParent() == NULL) {
		delete cResult.pc_root;
		cResult.pc_root = pcClonedOtherRoot;
	}
	else {
		pcActualNode = pcActualNode->pcGetParent();
		pcActualNode->vReplaceChild(0, pcClonedOtherRoot);

		while (pcActualNode != NULL) {
			pcActualNode->vSetIsCalculated(false);
			pcActualNode = pcActualNode->pcGetParent();
		}
	}

	cResult.vRebuildVariables();
	cResult.vRebuildFormula(cOther.vsGetFormula());
	return cResult;
}

void cTree::vRebuildFormula(const vector<string>& vsOtherFormula) {
	vector<string>vsResult;
	int i = 0;
	while (iGetSymbolArityStatic(vs_formula[i]) != I_ARITY_ZERO) {
		vsResult.push_back(vs_formula[i]);
		++i;
	}

	for (int j = 0;j < vsOtherFormula.size();++j) {
		vsResult.push_back(vsOtherFormula[j]);
	}

	++i;
	while (i < vs_formula.size()) {
		vsResult.push_back(vs_formula[i]);
		++i;
	}

	vs_formula = vsResult;

}

double cTree::dCalculateTree() {
	return pc_root->dGetValue();
}

int cTree::iCreateTree(vector<string>& vsFormula) {
	vs_formula = vsFormula;
	bool bTooManyArguments = false;
	bool bTooLittleArguments = false;
	int iResult = -1;

	if (!vs_formula.empty()) {

		bTooManyArguments = bCorrectFormuleIfTooManyArguments();

		if (!bTooManyArguments) {
			bTooLittleArguments = bCorrectFormuleIfTooLittleArguments();
		}
		
		pc_root = pcCreateNode(vs_formula[0], NULL);
		cNode* pcActualNode = pc_root;


		for (int i = 1;i < vs_formula.size();++i) {
			cNode* pcNewNode;
			while (pcActualNode->bIsComplete()) {
				pcActualNode = pcActualNode->pcGetParent();
			}

			pcNewNode = pcCreateNode(vs_formula[i], pcActualNode);
			pcActualNode->vAddChild(pcNewNode);
			pcActualNode = pcNewNode;
		}
		if (bTooManyArguments) {
			iResult = I_CREATE_TOO_MANY;
		}
		else if (bTooLittleArguments) {
			iResult = I_CREATE_TOO_LITTLE;
		}
		else{
			iResult = I_CREATE_OK;
		}
	}

	return iResult;
}

string cTree::sGetVariables() {
	string sResult="";
	for (int i = 0;i < vpc_variables.size();++i) {
		sResult += vpc_variables[i]->sGetName() + " ";
	}
	return sResult;
}

string cTree::sGetFormula() {
	string sResult = "";
	
	for (int i = 0;i < vs_formula.size();++i) {
		sResult += vs_formula[i] + " ";
	}

	return sResult;
}

const vector<string>& cTree::vsGetFormula() const {
	return vs_formula;
}



cNode* cTree::pcCreateNode(string& sType, cNode* pcParent){
	cNode* pcResult = NULL;
	if (sType == S_PLUS_SYMBOL) {
		pcResult = new cNodePlus(pcParent);
	}
	else if(sType == S_MINUS_SYMBOL) {
		pcResult = new cNodeMinus(pcParent);
	}
	else if (sType == S_MULTIPLICATION_SYMBOL) {
		pcResult = new cNodeMultiplication(pcParent);
	}
	else if (sType == S_DIVISION_SYMBOL) {
		pcResult = new cNodeDivision(pcParent);
	}
	else if (sType == S_SIN_SYMBOL) {
		pcResult = new cNodeSin(pcParent);
	}
	else if (sType == S_COS_SYMBOL) {
		pcResult = new cNodeCos(pcParent);
	}
	else if (bIsNumber(sType)) {
		double dValue = dStringToNumber(sType);
		pcResult = new cNodeValue(pcParent, dValue);
	}
	else {
		pcResult = new cNodeVariable(pcParent, sType);
		vCreateVariable(sType, (cNodeVariable*)pcResult);
	}
	
	return pcResult;
}

void cTree::vCreateVariable(string& sName, cNodeVariable* pcNewNode) {
	
	

	bool bIsNewVariable = true;
	int i = 0;
	while (i < vpc_variables.size() && bIsNewVariable) {
		if (vpc_variables[i]->sGetName() == sName) {
			bIsNewVariable = false;
		}
		++i;
	}
	--i;

	if (bIsNewVariable) {
		cVariable* pcNewVariable = new cVariable(sName);

		pcNewVariable->vAddNewUsingNode(pcNewNode);


		vpc_variables.push_back(pcNewVariable);

	
	}
	else {
		pcNewNode->vChangeValue(vpc_variables[i]->dGetValue());
		vpc_variables[i]->vAddNewUsingNode(pcNewNode);


	}

	
}

void cTree::vSetVariables(vector<string>& vsVariablesValues) {
	for (int i = 0;i < vpc_variables.size();++i) {
		double dNewValue = dStringToNumber(vsVariablesValues[i]);
		vpc_variables[i]->vChangeValue(dNewValue);
	}
}

bool cTree::bIsNumber(string& sElement) {
	bool bResult = true;

	int i = 0;
	while (i < sElement.size() && bResult) {
		if ((sElement[i] < C_FIRST_DIGIT || sElement[i] > C_LAST_DIGIT)) {
			bResult = false;
		}
		++i;
	}

	return bResult;
}

double cTree::dStringToNumber(string& sText) {
	double dResult;
	stringstream ss(sText);
	ss >> dResult;
	return dResult;
}

bool cTree::bIsDivision0() {
	return pc_root->bIsDivision0();
}

int cTree::iGetSymbolArityStatic(string& sSymbol) {
	int iResult;

	if (sSymbol == S_PLUS_SYMBOL) {
		iResult = cNodePlus::iGetArityStatic();
	}
	else if (sSymbol == S_MINUS_SYMBOL) {
		iResult = cNodeMinus::iGetArityStatic();
	}
	else if (sSymbol == S_MULTIPLICATION_SYMBOL) {
		iResult = cNodeMultiplication::iGetArityStatic();
	}
	else if (sSymbol == S_DIVISION_SYMBOL) {
		iResult = cNodeDivision::iGetArityStatic();
	}
	else if (sSymbol == S_SIN_SYMBOL) {
		iResult = cNodeSin::iGetArityStatic();
	}
	else if (sSymbol == S_COS_SYMBOL) {
		iResult = cNodeCos::iGetArityStatic();
	}
	else if (bIsNumber(sSymbol)) {
		iResult = cNodeValue::iGetArityStatic();
	}
	else {
		iResult = cNodeVariable::iGetArityStatic();
	}

	return iResult;
}

int cTree::iGetVariablesAmount() {
	return vpc_variables.size();
}

int cTree::iCalculateBilansStatic(vector<string>& vsFormula) {
	int iBilans = 1;
	for (int i = 0;i < vsFormula.size();++i) {
		iBilans += cTree::iGetSymbolArityStatic(vsFormula[i]) - 1;
	}

	return iBilans;
}

bool cTree::bCorrectFormuleIfTooManyArguments() {
	bool bResult = false;
	vector<string>vsNewFormule;
	int iBilans = 1;
	for (int i = 0;i < vs_formula.size();++i) {
		if (iBilans != 0) {
			iBilans += cTree::iGetSymbolArityStatic(vs_formula[i]) - 1;
			vsNewFormule.push_back(vs_formula[i]);
		}
		else {
			bResult = true;
		}
	}

	vs_formula = vsNewFormule;
	return bResult;
}

bool cTree::bCorrectFormuleIfTooLittleArguments() {
	bool bResult = false;
	int iBilans = cTree::iCalculateBilansStatic(vs_formula);
	while (iBilans != 0) {
		--iBilans;
		vs_formula.push_back(cInterface::sDoubleToString(D_VALUE_OF_DEFAULT_NODE));
		bResult = true;
	}

	return bResult;
}

bool cTree::bIsEmpty() {
	return pc_root == NULL;
}
