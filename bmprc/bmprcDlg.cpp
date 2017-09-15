
// bmprcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bmprc.h"
#include "bmprcDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CbmprcDlg dialog




CbmprcDlg::CbmprcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CbmprcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(pFileData,0,1024*200);
    memset(pData,0,1024*200);
}

void CbmprcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CbmprcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CbmprcDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CbmprcDlg message handlers

BOOL CbmprcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CbmprcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CbmprcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CbmprcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CbmprcDlg::OnBnClickedButton1()
{
	//1.文件I/O分析bitmap文件
// 	HANDLE hFile = CreateFile(_T("D:\\flower.bmp"),GENERIC_WRITE|GENERIC_READ, 0, NULL,OPEN_EXISTING, NULL, NULL);
// 	DWORD DwRead;
// 	LARGE_INTEGER fileSize;
// 	GetFileSizeEx(hFile, &fileSize);
// 	//获取位图属性
// 	LPRGBQUAD colorTable = {0};  
// 	BITMAPFILEHEADER fileHeader = {0};
// 	BITMAPINFOHEADER infoHeader = {0};
// 	ReadFile(hFile, &fileHeader, sizeof(BITMAPFILEHEADER), &DwRead, NULL);
// 	ReadFile(hFile, &infoHeader, sizeof(BITMAPINFOHEADER), &DwRead, NULL);
// 	if(infoHeader.biBitCount==8)//if colorTable exist,read colorTable  
// 	{  
// 		colorTable=new RGBQUAD[256];
// 		ReadFile(hFile, &colorTable, sizeof(RGBQUAD)*256, &DwRead, NULL);
// 	}  
// 	//获取图像数据
// 	byte dataBuf[80000] = {0};
// 	ReadFile(hFile, &dataBuf, infoHeader.biSizeImage, &DwRead, NULL); 
///////////////////////////////////////////////////////////////
	//2.类加载分析bitmap文件
// 	CBitmap Cbitmap;
// 	Cbitmap.LoadBitmap(IDB_BITMAP5);
// 	CDC mdc;
// 	mdc.CreateCompatibleDC(this->GetDC());
// 	mdc.SelectObject(&Cbitmap);
// 	int i = this->GetDC()->BitBlt(200, 0, 200, 400, &mdc, 0, 0, SRCCOPY);
// 	BITMAP BitMap = {0};
// 	HBITMAP hBitMap = (HBITMAP)Cbitmap.m_hObject;
// 	//获取位图属性
// 	if (!::GetObject(hBitMap, sizeof(BITMAP), (LPBYTE)&BitMap))   
// 	{
// 		return; 
// 	}
// 	BITMAPINFO BitMapInfo;   
// 	memset(&BitMapInfo, 0, sizeof(BITMAPINFO));
// 	BitMapInfo.bmiHeader.biSize = sizeof(BitMapInfo.bmiHeader);   
// 	BitMapInfo.bmiHeader.biWidth = BitMap.bmWidth;   
// 	BitMapInfo.bmiHeader.biHeight = BitMap.bmHeight;   
// 	BitMapInfo.bmiHeader.biPlanes = 1;   
// 	BitMapInfo.bmiHeader.biBitCount = 24;    
// 	BitMapInfo.bmiHeader.biCompression = BI_RGB;    
// 	::GetDIBits(mdc.m_hDC, hBitMap, 0, BitMap.bmHeight, NULL, &BitMapInfo, DIB_PAL_COLORS);
// 	BitMapInfo.bmiHeader.biClrUsed = 2;   
// 	BitMapInfo.bmiHeader.biClrImportant = 0; 
// 	//获取图像数据
// 	if (!::GetDIBits(mdc.m_hDC, hBitMap, 0, BitMap.bmHeight, pData, &BitMapInfo, DIB_PAL_COLORS))
// 	{
// 		return;
// 	}

	m_Drawer.TransToMonoc(CString("D:\\flower.bmp"), CString("Bmptmp.bmp"), RGB(125,125,125));
//////////////////////////////////////////////////////////
	//3.生成和分析DIBbitmap数据
// 	m_Drawer.bInitDc(200,400,TRUE);
// 	this->GetDC()->BitBlt(0, 0, 200, 400, m_Drawer.m_poMemDC, 0, 0, SRCCOPY);
// 	m_Drawer.bGetData(pData, 0);

};
