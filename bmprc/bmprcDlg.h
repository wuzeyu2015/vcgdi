
// bmprcDlg.h : header file
//

#pragma once
#include "MemDcImpl.h"

// CbmprcDlg dialog
class CbmprcDlg : public CDialogEx
{
// Construction
public:
	CbmprcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BMPRC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CMemDcImpl m_Drawer;
	byte pData[1024*200];					//内存绘图数据流
	byte pFileData[1024*200];					//内存绘图数据流
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
