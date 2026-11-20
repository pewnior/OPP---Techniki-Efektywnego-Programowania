#pragma once
#define CINTERFACE_H
#include "cTree.h"
#include<vector>

const string S_CMD_ENTER = "enter";
const string S_CMD_VARS = "vars";
const string S_CMD_PRINT = "print";
const string S_CMD_COMP = "comp";
const string S_CMD_JOIN = "join";
const string S_CMD_EXIT = "exit";

const string S_COMUNICATE_TOO_LITTLE_ARGUMENTS = "Too Little Arguments ";
const string S_COMUNICATE_TOO_MANY_ARGUMENTS = "Too Many Arguments ";
const string S_COMUNICATE_CREATED_TREE = "Created tree: ";
const string S_COMUNICATE_SUCCESSFULLY_VARIABLES = "Variables set successfully\nCalculated value: ";
const string S_COMUNICATE_TOO_LITTLE_VARIABLES = "Too Little Variables ";
const string S_COMUNICATE_TOO_MANY_VARIABLES = "Too Many Variables ";
const string S_COMUNICATE_UNKNOWN_COMMAND = "Unknown command ";
const string S_NEW_LINE = "\n";
const string S_COMUNICATE_DIVION_BY_0 = "Error: In tree is divison by 0 ";
const string S_COMUNICATE_EMPTY_TREE = "Error: Tree is empty ";
const string S_COMUNICATE_EMPTY_FORMULA = "Error: Formula is empty ";
const string S_COMUNICATE_INVALID_ARGUMENTS = "Error: Invalid arguments ";
const string S_COMUNICATE_CHANGES_VARIABLES = "Variables names changed \n";
const string S_COMUNICATE_INVALID_PLUS = "Error: Uncorrect + symbol on posiotion: ";

class cInterface {
public:
	cInterface();
	~cInterface();

	string sRun(vector<string>& vsCommand);
	string sRun(string& sCommand);
	static string sDoubleToString(double dValue);

private:
	cTree* pc_tree;

	bool bAreAllArgumentsNumbers(vector<string>& vsArguments);
	bool bIsLetter(char cSymbol);
	bool bIsOperator(string& sElement);
	string sRemoveInvalidSymbols(string& sElement);
	bool bCheckVariables(vector<string>& vsFormula);
	bool bIsDigit(char cSymbol);

	string sEnter(vector<string>& vsCommand);
	string sVars();
	string sPrint();
	string sComp(vector<string>& vsCommand);
	string sJoin(vector<string>& vsCommand);
};