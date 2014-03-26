//============================================================================
// Name        : Phase2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

namespace nsUtil
{
	// E A C F
	bool contains(string str, string strCompar)
	{
		if(strCompar.size() > str.size()) return false;
		for(unsigned i = 0; i < str.size(); ++i)
		{
			for(unsigned j = 0; j < strCompar.size(); ++j)
			{
				if(str[i] != strCompar[j]) break;
				i++;
				if(j+1 == strCompar.size()) return true;
			}
		}
		return false;
	}
}
int main() {
	bool result;

	result = nsUtil::contains("EACF", "AC");
	if(result)
		cout << "It's work" << endl;
	else
		cout << "Don't work" << endl;

	result = nsUtil::contains("EACF", "ABC");
		if(result)
			cout << "It's work" << endl;
		else
			cout << "Don't work" << endl;

	result = nsUtil::contains("EACF", "ACF");
		if(result)
			cout << "It's work" << endl;
		else
			cout << "Don't work" << endl;

	return 0;
}
