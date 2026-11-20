#include"cVariable.h"
#include<vector>
#include<string>
#include"cNode.h"
#include"cNodeVariable.h"

using namespace std;

cVariable::cVariable(string& sName) {
	s_name = sName;
	d_value = -1;
}

string cVariable::sGetName() {
	return s_name;
}
double cVariable::dGetValue() {
	return d_value;
}
void cVariable::vChangeValue(double dNewValue) {
	d_value = dNewValue;
	for (int i = 0;i < vpc_using_nodes.size();++i) {
		vpc_using_nodes[i]->vChangeValue(dNewValue);
	}
}
void cVariable::vAddNewUsingNode(cNodeVariable* pcNewNode) {
	vpc_using_nodes.push_back(pcNewNode);
}