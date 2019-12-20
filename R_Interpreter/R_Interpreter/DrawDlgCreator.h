#pragma once
#include <vector>
#include <string>

using namespace std;

class DrawDlgCreator
{
public:
	DrawDlgCreator();
	bool CreatePieView(vector<string> data, vector<string> label, string title);
	bool CreateBarplotView(vector<int>& data, string xlab, string ylab, string title);
	bool DrawDemoBarlotView();

};

