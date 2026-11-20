#include <iostream>
#include <sstream>
#include<string>
#include "cInterface.h"

using namespace std;

int main()
{
    cInterface* pcInterface = new cInterface();
    string sInput;

    while (sInput != "exit" && getline(cin, sInput)) {
        cout << pcInterface->sRun(sInput);
    }

    delete pcInterface;
}

