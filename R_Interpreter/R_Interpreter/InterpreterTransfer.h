#pragma once
#include <string>
using namespace std;
class InterpreterTransfer
{
public:
	static InterpreterTransfer* getInstance()
	{
		if (NULL == instance)
		{
			instance = new InterpreterTransfer();
		}
		return instance;
	}

	string transferText(const string& inputMsg);
	CString transferText(const CString& inputMsg);
private:
	InterpreterTransfer();
	static InterpreterTransfer* instance;

};

