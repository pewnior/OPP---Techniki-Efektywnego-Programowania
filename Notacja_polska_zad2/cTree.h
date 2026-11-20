#pragma once
#define CTREE_H

#include "cNode.h"
#include "cVariable.h"
#include <string>
#include <vector>

using namespace std;

const string S_PLUS_SYMBOL = "+";
const string S_MINUS_SYMBOL = "-";
const string S_MULTIPLICATION_SYMBOL = "*";
const string S_DIVISION_SYMBOL = "/";
const string S_SIN_SYMBOL = "sin";
const string S_COS_SYMBOL = "cos";

const char C_FIRST_DIGIT = '0';
const char C_LAST_DIGIT = '9';
const char C_FIRST_SMALL_LETTER = 'a';
const char C_LAST_SMALL_LETTER = 'z';
const char C_FIRST_HIGH_LETTER = 'A';
const char C_LAST_HIGH_LETTER = 'Z';

const int I_CREATE_OK = 0;
const int I_CREATE_TOO_MANY = 1;
const int I_CREATE_TOO_LITTLE = -1;

class cTree {
public:
	cTree();
	cTree(const cTree& cOther);
	~cTree();

	cTree& operator=(const cTree& cOther);
	cTree operator+(const cTree& cOther) const;

	string sGetVariables();
	string sGetFormula();
	double dCalculateTree();
	void vSetVariables(vector<string>& vsVariablesValues);
	bool bIsDivision0();
	static int iGetSymbolArityStatic(string& sSymbol);
	int iCreateTree(vector<string>& vsFormula);
	int iGetVariablesAmount();
	static int iCalculateBilansStatic(vector<string>& vsFormula);
	bool bIsEmpty();
	void vCreateVariable(string& sName, cNodeVariable* pcNewNode);
	static bool bIsNumber(string& sElement);


private:
	cNode* pc_root;
	vector<cVariable*> vpc_variables;
	vector<string>vs_formula;

	cNode* pcCreateNode(string& sType, cNode* pcParent);
	
	void vRebuildVariables();
	void vRebuildFormula(const vector<string>& vsOtherFormula);
	const vector<string>& vsGetFormula() const;

	double dStringToNumber(string& sText);
	
	bool bCorrectFormuleIfTooManyArguments();
	bool bCorrectFormuleIfTooLittleArguments();

 };

