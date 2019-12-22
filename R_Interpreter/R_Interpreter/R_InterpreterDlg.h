
// R_InterpreterDlg.h: 头文件
//

#pragma once


// CRInterpreterDlg 对话框
class CRInterpreterDlg : public CDialogEx
{
// 构造
public:
	CRInterpreterDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_R_INTERPRETER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit InputMsg;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditInput();
	afx_msg void OnEnChangeEditOuptput();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedClean();
	afx_msg void OnBnClickedTransfer();

private:

public:
	afx_msg void OnBnClickedTransfer2();
	afx_msg void OnBnClickedTransfer3();
};
