#include "pch.h"
#include "InterpreterTransfer.h"
#include "DrawDlgCreator.h"
#include <vector>
#include <map>
#include <iostream>

InterpreterTransfer::InterpreterTransfer()
{
}

struct Vec
{
	vector<string> vec;
};

struct Matrix
{
	vector<vector<string> > vec;
	int nrow, ncol;
};

// 1:number 2:vector 3:matrix
map<string, int> getType;
map<string, int> getIndex;
vector<string> dataContainer;
vector<Vec> vecContainer;
vector<Matrix> matrixContainer;
bool vis[10000];

vector<string> Split(const string& str, const string& delimiters)
{
	vector<string> ans;
	int lastPos = str.find_first_not_of(delimiters, 0);
	int pos = str.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos) {
		ans.emplace_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
	return ans;
}

Vec AddVec(const string& str) {
	vector<string> val = Split(str, ",");
	Vec v;
	for (auto s : val) {
		v.vec.emplace_back(s);
	}
	return v;
}

int GetNumber(const string& str, const string& tar) {
	int pos = str.find(tar) + tar.size();
	while (!isdigit(str[pos])) pos++;
	int ans = 0;
	while (isdigit(str[pos])) {
		ans = ans * 10 + str[pos] - '0';
		pos++;
	}
	return ans;
}

vector<vector<string> > Vec2Matrix(const vector<string>& vec, int row, int col) {
	vector<vector<string> > ans(row);
	for (int i = 0; i < row; i++) {
		for (int j = i; j < vec.size(); j += col) {
			ans[i].emplace_back(vec[j]);
		}
	}
	return ans;
}

int ToNum(string s) {
	int x = 0;
	for (int i = 0; i < s.size(); i++) x = x * 10 + s[i] - '0';
	return x;
}

void Print(string& outputMsg, string ss) {
	if (ss[0] == '"') {
		outputMsg += ss.substr(1, ss.size() - 2);
	}
	else if (ss.find("==") == string::npos) {
		if (ss.find('[') == string::npos) {
			int type = getType[ss], idx = getIndex[ss];
			if (type == 1) {
				outputMsg += dataContainer[idx];
				outputMsg += "\r\n";
			}
			else if (type == 2) {
				for (auto val : vecContainer[idx].vec) {
					outputMsg += val + " ";
				}
				outputMsg += "\r\n";
			}
			else if (type == 3) {
				Matrix m = matrixContainer[idx];
				int row = m.nrow, col = m.ncol;
				outputMsg += "      ";
				for (int i = 1; i <= col; i++) {
					outputMsg += "[," + to_string(i) + "]";
				}
				outputMsg += "\r\n";
				for (int i = 0; i < row; i++) {
					outputMsg += "[" + to_string(i + 1) + ",]";
					for (int j = 0; j < col; j++) {
						outputMsg += "    " + m.vec[i][j];
					}
					outputMsg += "\r\n";
				}
			}
		}
		else {
			int pos = ss.find('[');
			string name = ss.substr(0, pos);
			int type = getType[name];
			int l = pos + 1, r = ss.find(']') - 1;
			if (type == 2) {
				int idx = ToNum(ss.substr(l, r - l + 1));
				outputMsg += vecContainer[getIndex[name]].vec[idx - 1];
				outputMsg += "\r\n";
			}
			else if (type == 3) {
				int div = ss.find(',');
				int x = ToNum(ss.substr(l, div - l)), y = ToNum(ss.substr(div + 1, r - div));
				outputMsg += matrixContainer[getIndex[name]].vec[x - 1][y - 1];
				outputMsg += "\r\n";
			}
		}
	}
	else {
		int pos = ss.find("==");
		string left = ss.substr(0, pos);
		string right = ss.substr(pos + 2, ss.size() - pos - 2);
		if (getType[left] > 0) {
			left = dataContainer[getIndex[left]];
		}
		if (getType[right] > 0) {
			right = dataContainer[getIndex[right]];
		}
		if (left == right) {
			outputMsg += "TRUE";
			outputMsg += "\r\n";
		}
		else {
			outputMsg += "FALSE";
			outputMsg += "\r\n";
		}
	}
}

void DrawBarplot(string& outputMsg, string str) {
	int L = str.find("barplot") + 1;
	int R = str.find(")") - 1;
	string ss = str.substr(L, R - L + 1);
	vector<string> v = Split(ss, ",");
	vector<int> H;
	string xlab, ylab, main;
	for (auto val : v) {
		int pos = val.find("=") + 1;
		if (val.find("main") != string::npos) {
			main = val.substr(pos, val.size() - pos);
		}
		else if (val.find("xlab") != string::npos) {
			xlab = val.substr(pos, val.size() - pos);
		}
		else if (val.find("ylab") != string::npos) {
			ylab = val.substr(pos, val.size() - pos);
		}
		else {
			for (auto j : vecContainer[getIndex[val]].vec) {
				outputMsg += to_string(ToNum(j));
				outputMsg += "\r\n";
			}
			for (auto j : vecContainer[getIndex[val]].vec) H.emplace_back(ToNum(j));
		}
	}
	DrawDlgCreator ddc;
	ddc.CreateBarplotView(H, xlab, ylab, main);
}

void DrawPie(string& outputMsg, string str) {
	int L = str.find("pie") + 1;
	int R = str.find(")") - 1;
	string ss = str.substr(L, R - L + 1);
	vector<string> v = Split(ss, ",");
	vector<string> tp = vecContainer[getIndex[v[0]]].vec;
	vector<int> H, K;
	for (auto j : tp) H.emplace_back(ToNum(j));
	tp = vecContainer[getIndex[v[1]]].vec;
	L = str.find('"');
	for (int i = L + 1; i < str.size(); i++) {
		if (str[i] == '"') {
			R = i;
			break;
		}
	}
	string name = str.substr(L + 1, R - L - 1);
	DrawDlgCreator ddc;
	ddc.CreatePieView(H, tp, name);
}

void AddVal(string& outputMsg, string str) {
	int L = str.find("<-") - 1, R = L + 3;
	while (str[L] == ' ') L--;
	while (str[R] == ' ') R++;
	string name = str.substr(0, L + 1);
	string right = str.substr(R, str.size() - R);
	if (getType[right] > 0) {
		int type = getType[right];
		getType[name] = type;
		if (type == 1) {
			dataContainer.emplace_back(dataContainer[getIndex[right]]);
			getIndex[name] = dataContainer.size() - 1;
		}
		else if (type == 2) {
			vecContainer.emplace_back(vecContainer[getIndex[right]]);
			getIndex[name] = vecContainer.size() - 1;
		}
		else {
			matrixContainer.emplace_back(matrixContainer[getIndex[right]]);
			getIndex[name] = matrixContainer.size() - 1;
		}
	}
	else if (str[R] == 'c') {
		getType[name] = 2;
		vecContainer.emplace_back(AddVec(str.substr(R + 2, str.find(')') - R - 2)));
		getIndex[name] = vecContainer.size() - 1;
	}
	else if (str.substr(R, 6) == "matrix") {
		getType[name] = 3;
		int pos = str.find("matrix") + 6;
		while (str[pos] != 'c') pos++;
		Matrix newMatrix;
		newMatrix.nrow = GetNumber(str, "nrow");
		newMatrix.ncol = GetNumber(str, "ncol");
		newMatrix.vec = Vec2Matrix(AddVec(str.substr(pos + 2, str.find(')') - pos - 2)).vec, newMatrix.nrow, newMatrix.ncol);
		matrixContainer.emplace_back(newMatrix);
		getIndex[name] = matrixContainer.size() - 1;
	}
	else {
		getType[name] = 1;
		string val = str.substr(R, str.size() - R);
		dataContainer.emplace_back(val);
		getIndex[name] = dataContainer.size() - 1;
	}
}

void DealIf(string& outputMsg, const string& str, int idx, const vector<string>& inputVec, int end);
void DealElse(string& outputMsg, const string& str, int idx, const vector<string>& inputVec, int end);

void Work(string& outputMsg, const string& str, int idx, const vector<string>& inputVec) {
	if (vis[idx]) return;
	vis[idx] = true;
	if (str.find("barplot") != str.npos) {
		DrawBarplot(outputMsg, str);
	}
	else if (str.find("pie") != str.npos) {
		DrawPie(outputMsg, str);
	}
	else if (str.find("<-") != str.npos) {
		AddVal(outputMsg, str);
	}
	else if (str.find("if") != str.npos) {
		int L = str.find("(") + 1, R = str.find(")") - 1;
		string op;
		int pos, flag = 0;
		if (str.find("<") != string::npos) pos = str.find("<"), op = "<";
		else if (str.find(">") != string::npos) pos = str.find(">"), op = ">";
		else if (str.find("==") != string::npos) pos = str.find("=="), op = "==", flag++;
		string leftName = str.substr(L, pos - L), rightName = str.substr(pos + 1 + flag, R - pos - flag);
		int leftVal = getType[leftName] > 0 ? ToNum(dataContainer[getIndex[leftName]]) : ToNum(leftName);
		int rightVal = getType[rightName] > 0 ? ToNum(dataContainer[getIndex[rightName]]) : ToNum(rightName);
		int end = idx + 2;
		while (inputVec[end].find("}") == string::npos) end++;
		if (op == "<") {
			if (leftVal < rightVal) {
				DealIf(outputMsg, str, idx, inputVec, end);
			}
			else {
				DealElse(outputMsg, str, idx, inputVec, end);
			}
		}
		else if (op == ">") {
			if (leftVal > rightVal) {
				DealIf(outputMsg, str, idx, inputVec, end);
			}
			else {
				DealElse(outputMsg, str, idx, inputVec, end);
			}
		}
		else if (op == "==") {
			if (leftVal == rightVal) {
				DealIf(outputMsg, str, idx, inputVec, end);
			}
			else {
				DealElse(outputMsg, str, idx, inputVec, end);
			}
		}
	}
	else if (str.find("print") != str.npos) {
		int L = str.find("print") + 6, R = str.find(")") - 1;
		Print(outputMsg, str.substr(L, R - L + 1));
	}
	else {
		Print(outputMsg, str);
	}
}

void DealIf(string& outputMsg, const string& str, int idx, const vector<string>& inputVec, int end) {
	for (int i = idx + 2; inputVec[i].find("}") == string::npos; i++) {
		Work(outputMsg, inputVec[i], i, inputVec);
	}
	if (end + 1 < (int)inputVec.size() && inputVec[end + 1].find("else") != string::npos) {
		end += 2;
		while (inputVec[end].find("}") == string::npos) {
			vis[end] = true;
			end++;
		}
	}
}

void DealElse(string& outputMsg, const string& str, int idx, const vector<string>& inputVec, int end) {
	for (int i = idx + 2; inputVec[i].find("}") == string::npos; i++) {
		vis[i] = true;
	}
	if (end + 1 < (int)inputVec.size() && inputVec[end + 1].find("else") != string::npos) {
		end += 2;
		while (inputVec[end].find("}") == string::npos) {
			Work(outputMsg, inputVec[end], end, inputVec);
			end++;
		}
	}
}

string InterpreterTransfer::transferText(const string& inputMsg)
{
	memset(vis, false, sizeof(vis));
	vector<string> inputVec = Split(inputMsg, "\r\n");
	string outputMsg;
	for (int i = 0; i < inputVec.size(); i++) {
		string str = inputVec[i];
		vector<string> tmp = Split(str, " ");
		str.clear();
		for (auto ss : tmp) str += ss;
		Work(outputMsg, str, i, inputVec);
	}
	return outputMsg;
}

CString InterpreterTransfer::transferText(const CString& inputMsg)
{
	string str = CW2A(inputMsg);
	string result = getInstance()->transferText(str);
	CString resultCString(result.c_str());
	return resultCString;
}

InterpreterTransfer* InterpreterTransfer::instance = new InterpreterTransfer();


/*
a<-2
b<-4
if(a == 2)
{
	if(b==3)
	{
	 print("TRUE: a == 1")
	}
	else
	{
	print("false")
	}
}

*/