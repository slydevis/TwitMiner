//============================================================================
// Name        : Phase2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
using namespace std;

namespace nsUtil
{
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

	float toFloat(string str)
	{
		stringstream is;
		float result;
		is.str(str);
		is >> result;
		return result;
	}

	int testmain() {
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

		unsigned i = nsUtil::toFloat("2");

		cout << i << endl;

		return 0;
	}

}
