#include<string>
#include"cInterface.h"
#include"cTree.h"
#include"cNodeValue.h"
#include <sstream>

using namespace std;

cInterface::cInterface(){
	pc_tree = new cTree();
}

cInterface::~cInterface() {
	if (pc_tree != NULL) {
		delete pc_tree;
	}
}

string cInterface::sRun(vector<string>& vsCommand) {
	string sResult;
	if (!vsCommand.empty()) {
		string sMainCommand = vsCommand[0];
		vsCommand.erase(vsCommand.begin());

		if (sMainCommand == S_CMD_ENTER) {
			sResult = sEnter(vsCommand);
		}

		else if (sMainCommand == S_CMD_VARS) {
			sResult = sVars();
		}

		else if (sMainCommand == S_CMD_PRINT) {
			sResult = sPrint();
		}

		else if (sMainCommand == S_CMD_COMP) {
			sResult = sComp(vsCommand);
		}

		else if (sMainCommand == S_CMD_JOIN) {
			sResult = sJoin(vsCommand);
		}
		else if (sMainCommand == S_CMD_EXIT) {
			sResult = "";
		}
		else {
			sResult = S_COMUNICATE_UNKNOWN_COMMAND;
		}
	}
	else {
		sResult = S_COMUNICATE_UNKNOWN_COMMAND;
	}
	return sResult + S_NEW_LINE;
}

string cInterface::sRun(string& sCommand) {
	istringstream iss(sCommand);
	vector<string> vsCommand;

	string sSingleToken;
	while (iss >> sSingleToken) {
		vsCommand.push_back(sSingleToken);
	}

	return sRun(vsCommand);
}

string cInterface::sEnter(vector<string>& vsCommand) {
	string sResult;
	if (bCheckVariables(vsCommand)) {
		sResult += S_COMUNICATE_CHANGES_VARIABLES;
	}
	if (!vsCommand.empty()) {
		int iCreateResult;
		delete pc_tree;
		pc_tree = new cTree();

		

		iCreateResult = pc_tree->iCreateTree(vsCommand);

		if (iCreateResult == I_CREATE_TOO_MANY) {
			sResult += S_COMUNICATE_TOO_MANY_ARGUMENTS;
		}
		else if (iCreateResult == I_CREATE_TOO_LITTLE) {
			sResult += S_COMUNICATE_TOO_LITTLE_ARGUMENTS;
		}

		sResult += S_COMUNICATE_CREATED_TREE + pc_tree->sGetFormula();
	}
	else {
		sResult += S_COMUNICATE_EMPTY_FORMULA;
	}
	return sResult;
}

string cInterface::sVars() {
	string sResult;
	if (pc_tree->bIsEmpty()) {
		sResult = S_COMUNICATE_EMPTY_TREE;
	}
	else {
		sResult = pc_tree->sGetVariables();
	}
	return sResult;
}

string cInterface::sPrint() {
	string sResult;
	if (pc_tree->bIsEmpty()) {
		sResult = S_COMUNICATE_EMPTY_TREE;
	}
	else {
		sResult = pc_tree->sGetFormula();
	}
	return sResult;
}

string cInterface::sComp(vector<string>& vsCommand) {
	string sResult;
	if (pc_tree->bIsEmpty()) {
		sResult = S_COMUNICATE_EMPTY_TREE;
	}
	else {
		int iVariablesAmount = pc_tree->iGetVariablesAmount();

		if (iVariablesAmount == vsCommand.size()) {
			if (bAreAllArgumentsNumbers(vsCommand)) {
				pc_tree->vSetVariables(vsCommand);
				string sTreeValue = sDoubleToString(pc_tree->dCalculateTree());
				if (!pc_tree->bIsDivision0()) {
					sResult = S_COMUNICATE_SUCCESSFULLY_VARIABLES + sTreeValue;
				}
				else {
					sResult = S_COMUNICATE_DIVION_BY_0;
				}
			}
			else {
				sResult = S_COMUNICATE_INVALID_ARGUMENTS;
			}
		}
		else if (iVariablesAmount > vsCommand.size()) {
			sResult = S_COMUNICATE_TOO_LITTLE_VARIABLES;
		}
		else {
			sResult = S_COMUNICATE_TOO_MANY_VARIABLES;
		}
	}
	return sResult;
}

string cInterface::sJoin(vector<string>& vsCommand) {
	string sResult;
	if (bCheckVariables(vsCommand)) {
		sResult += S_COMUNICATE_CHANGES_VARIABLES;
	}
	if (vsCommand.empty()) {
		sResult += S_COMUNICATE_EMPTY_FORMULA;
	}
	else {
		cTree cOtherTree;
		int iCreateResult;
		iCreateResult = cOtherTree.iCreateTree(vsCommand);

		if (iCreateResult == I_CREATE_TOO_MANY) {
			sResult += S_COMUNICATE_TOO_MANY_ARGUMENTS;
		}
		else if (iCreateResult == I_CREATE_TOO_LITTLE) {
			sResult += S_COMUNICATE_TOO_LITTLE_ARGUMENTS;
		}

		*pc_tree = *pc_tree + cOtherTree;

		sResult += S_COMUNICATE_CREATED_TREE + pc_tree->sGetFormula();
	}
	return sResult;
}

string cInterface::sDoubleToString(double dValue) {
	ostringstream oss;
	oss << dValue;
	return oss.str();
}

bool cInterface::bAreAllArgumentsNumbers(vector<string>& vsArguments){
	bool bAllValid = true;
	int i = 0;
	while (i < vsArguments.size() && bAllValid) {
		if (!cTree::bIsNumber(vsArguments[i])) {
			bAllValid = false;
		}
		++i;
	}
	return bAllValid;
}

bool cInterface::bIsLetter(char cSymbol) {
	bool bResult;
	if (cSymbol >= C_FIRST_HIGH_LETTER && cSymbol <= C_LAST_HIGH_LETTER) {
		bResult = true;
	}
	else if (cSymbol >= C_FIRST_SMALL_LETTER && cSymbol <= C_LAST_SMALL_LETTER) {
		bResult = true;
	}
	else {
		bResult = false;
	}

	return bResult;
}

bool cInterface::bIsOperator(string& sElement){
	return sElement == S_PLUS_SYMBOL
		|| sElement == S_MINUS_SYMBOL
		|| sElement == S_MULTIPLICATION_SYMBOL
		|| sElement == S_DIVISION_SYMBOL
		|| sElement == S_SIN_SYMBOL
		|| sElement == S_COS_SYMBOL;
}

bool cInterface::bIsDigit(char cSymbol) {
	bool bResult;
	if (cSymbol >= C_FIRST_DIGIT && cSymbol <= C_LAST_DIGIT) {
		bResult = true;
	}
	else {
		bResult = false;
	}
	return bResult;
}

string cInterface::sRemoveInvalidSymbols(string& sElement){
	string sResult = "";
	for (int i = 0; i < sElement.size(); ++i) {
		if (bIsLetter(sElement[i]) || bIsDigit(sElement[i])) {
			sResult += sElement[i];
		}
	}
	return sResult;
}

bool cInterface::bCheckVariables(vector<string>& vsFormula) {
	bool bModifiedAny = false;
	int i = 0;

	while (i < vsFormula.size()) {
		if (bIsOperator(vsFormula[i]) || cTree::bIsNumber(vsFormula[i])) {
			++i;
		}
		else {
			string sCleaned = sRemoveInvalidSymbols(vsFormula[i]);
			if (sCleaned != vsFormula[i]) {
				bModifiedAny = true;
				if (sCleaned.empty()) {
					vsFormula.erase(vsFormula.begin() + i);
				}
				else {
					vsFormula[i] = sCleaned;
					++i;
				}
			}
			else {
				++i;
			}
		}
	}

	return bModifiedAny;
}