#include "pch.h"
#include "DrawDlgCreator.h"
#include "DrawDialog.h"
#include <string>

using namespace std;

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

DrawDlgCreator::DrawDlgCreator()
{
}

bool DrawDlgCreator::CreatePieView(vector<int>& data, vector<string> label, string title)
{
	DrawDialog dlg;
	dlg.dialogType = PieView;
	dlg.data = data;
	dlg.label = label;
	std::wstring stemp = s2ws(title);
	dlg.title = stemp.c_str();
	dlg.DoModal();

	return true;
}

bool DrawDlgCreator::CreateBarplotView(vector<int>& data, string xlab, string ylab, string title)
{
	DrawDialog dlg;
	dlg.dialogType = BarplotView;
	dlg.data = data;
	dlg.xlabel = xlab;
	dlg.ylabel = ylab;
	std::wstring stemp = s2ws(title);
	dlg.title = stemp.c_str();
	dlg.DoModal();

	return true;
}

bool DrawDlgCreator::DrawDemoBarlotView()
{
	vector<int> data;
	data.push_back(10);
	data.push_back(15);
	data.push_back(8);
	data.push_back(4);
	data.push_back(6);
	data.push_back(7);

	CreateBarplotView(data, "fruit", "count", "fruit amount");
	return true;
}

bool DrawDlgCreator::DrawDemoPieView()
{
	vector<int> data;
	data.push_back(2);
	data.push_back(4);
	data.push_back(6);
	data.push_back(8);

	vector<string> label;
	label.push_back("banana");
	label.push_back("apple");
	label.push_back("tomato");
	label.push_back("mango");

	CreatePieView(data, label, "fruit amount");
	return true;
}