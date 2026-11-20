#pragma once
#define CVARIABLE_H

#include<string>
#include<vector>
#include"cNode.h"
#include"cNodeVariable.h"

using namespace std;

class cVariable {
public:
	cVariable(string& sName);

	string sGetName();
	double dGetValue();
	void vChangeValue(double dNewValue);
	void vAddNewUsingNode(cNodeVariable* pcNewNode);

private:
	string s_name;
	double d_value;
	vector<cNodeVariable*>vpc_using_nodes;
};

