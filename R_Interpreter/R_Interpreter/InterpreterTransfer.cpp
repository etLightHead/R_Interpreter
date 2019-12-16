#include "pch.h"
#include "InterpreterTransfer.h"

InterpreterTransfer::InterpreterTransfer()
{
}

string InterpreterTransfer::transferText(const string& inputMsg)
{
	// TODO: Deal with this string

	return inputMsg;
}

CString InterpreterTransfer::transferText(const CString& inputMsg)
{
	string str = CW2A(inputMsg);
	string result = getInstance()->transferText(str);
	CString resultCString(result.c_str());
	return resultCString;
}

InterpreterTransfer* InterpreterTransfer::instance = new InterpreterTransfer();
