#pragma once
#include <vector>
#include <string>

using namespace std;

enum DialogType {
	PieView, BarplotView
};


// DrawDialog 对话框
class DrawDialog : public CDialogEx
{
	DECLARE_DYNAMIC(DrawDialog)

public:
	DrawDialog(CWnd* pParent = nullptr);   // 标准构造函数
	DialogType dialogType;
	virtual ~DrawDialog();
	vector<string> xlab;
	string xlabel, ylabel;
	LPCTSTR title;
	vector<int> data;

	int dlgWidth, dlgHeight;
	const int STANDARDWIDTH = 800;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DRAW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	virtual void OnEraseBkGnd();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaticDrawPic();
	afx_msg void OnPaint();
	afx_msg BOOL OnInitDialog();

	void DrawPieView(CPaintDC& content);

	void UpdateDlgSize();

	void DrawBarplotView(CPaintDC& content);

	int GetMaxData();

	void PaintDemo(CPaintDC& content)
	{
		LOGFONT log;
		CFont font;
		log.lfHeight = 0;
		log.lfEscapement = 0;
		log.lfItalic = 0;
		log.lfUnderline = 0;
		log.lfStrikeOut = 0;

		//    dc.SelectObject(&font); 
		font.CreateFontIndirect(&log);
		//画笔
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		content.SelectObject(&pen);
		//    *OldPen = dc.SelectObject(&pen);//旧画笔


			//逻辑坐标
		SetViewportOrgEx(content, 50, 500, NULL);
		content.SetMapMode(MM_LOMETRIC);//0.1毫米

		//纵坐标
		content.MoveTo(0, 0);
		content.LineTo(0, 1000);//高1000
		content.LineTo(-10, 980);
		content.MoveTo(0, 1000);
		content.LineTo(10, 980);
		//纵坐标循环
		CString str;
		int i;
		for (i = 1; i < 10; i++)
		{
			str.Format(L"%d", i * 10);

			content.TextOut(-30, i * 100, str);
		}
		content.TextOut(-50, 1050, L"%");
		//横坐标
		content.MoveTo(0, 0);
		content.LineTo(850, 0);
		content.LineTo(830, 10);
		content.MoveTo(850, 0);
		content.LineTo(830, -10);

		int x1, y1, x2, y2, y3, x3;
		float zhuan = 0.4, ben = 0.3, shuo = 0.2, bo = 0.1;
		int h = 1000, r = 400;



		//画柱子

		content.SelectObject(&font);     //修改字体

		CRect r1(100, zhuan * h * 2, 200, 0);
		CBrush br1(RGB(253, 51, 67));
		content.FillRect(r1, &br1);//矩形，颜色
		content.TextOut(130, -10, L"专科");//横坐标的说明文字

		CRect r2(300, ben * h, 400, 0);
		CBrush br2(RGB(250, 164, 51));
		content.FillRect(r2, &br2);
		content.TextOut(330, -10, L"本科");

		CRect r3(500, shuo * h, 600, 0);
		CBrush br3(RGB(139, 197, 51));
		content.FillRect(r3, &br3);
		content.TextOut(530, -10, L"硕士");

		CRect r4(700, bo * h, 800, 0);
		CBrush br4(RGB(3, 141, 216));
		content.FillRect(r4, &br4);
		content.TextOut(730, -10, L"博士");


		//    dc.SetBkColor(RGB(0,0,0));
		//    dc.Rectangle(100,zhuan*h,200,0);
		//    dc.Rectangle(300,ben*h,400,0);
		//    dc.Rectangle(500,shuo*h,600,0);
		//    dc.Rectangle(700,bo*h,800,0);

			//画饼图，利用cos，sin函数计算顶点值，颜色沿用之前已经定义了的brush
		content.SelectObject(&br1);
		x1 = int(r * cos(zhuan * 3.14 * 2)) + 1400;
		y1 = int(r * sin(zhuan * 3.14 * 2) + 400);
		content.Pie(1000, 800, 1800, 0, 1800, 400, x1, y1);


		content.SelectObject(&br2);
		x2 = int(r * cos((ben + zhuan) * 3.14 * 2)) + 1400;
		y2 = int(r * sin((ben + zhuan) * 3.14 * 2)) + 400;
		content.Pie(1000, 800, 1800, 0, x1, y1, x2, y2);

		content.SelectObject(&br3);
		x3 = int(r * cos((ben + zhuan + shuo) * 3.14 * 2)) + 1400;
		y3 = int(r * sin((ben + zhuan + shuo) * 3.14 * 2)) + 400;
		content.Pie(1000, 800, 1800, 0, x2, y2, x3, y3);
		CBrush   br9(RGB(125, 30, 227));
		content.SelectObject(&br9);

		content.SelectObject(&br4);
		content.Pie(1000, 800, 1800, 0, x3, y3, 1800, 400);

		//在园外右上角画图例，加上说明文字
		CRect r5(2000, 1000, 2080, 1060);
		content.FillRect(r5, &br1);
		content.TextOut(2100, 1040, L"专科");

		CRect r6(2000, 900, 2080, 960);
		content.FillRect(r6, &br2);
		content.TextOut(2100, 940, L"本科");

		CRect r7(2000, 800, 2080, 860);
		content.FillRect(r7, &br3);
		content.TextOut(2100, 840, L"硕士");

		CRect r8(2000, 700, 2080, 760);
		content.FillRect(r8, &br4);
		content.TextOut(2100, 740, L"博士");
	}

};
