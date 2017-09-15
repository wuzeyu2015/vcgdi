#pragma once

class CMemDcImpl
{
public:
	CMemDcImpl(void);
	~CMemDcImpl(void);

public:
	BOOL bInitDc(ULONG p_ulWide, ULONG p_ulHigh, BOOL isAxis);

	/*DT_LEFT            = 0;         {左对齐}
	DT_CENTER          = 1;         {水平居中}
	DT_RIGHT           = 2;         {右对齐}*/
	BOOL bSetTextHorizontalAlign(UINT fMode);

	BOOL bSetPosition(ULONG ulPosX, ULONG ulPosY);

	//
	BOOL bDrawText(LPCWSTR p_lpText, BOOL p_bTextAsAlign = FALSE);

	//p_ulSize >= p_ulWide*p_ulHigh否则失败
	BOOL bGetData(BYTE* p_byData, ULONG p_ulSize);
	BOOL bGetDataPart1(BYTE* p_byData, ULONG p_ulSize);
	BOOL bGetDataPart2(BYTE* p_byData, ULONG p_ulSize);

	BOOL bGetDataPart1of3(BYTE* p_byData, ULONG p_ulSize);
	BOOL bGetDataPart2of3(BYTE* p_byData, ULONG p_ulSize);
	BOOL bGetDataPart3of3(BYTE* p_byData, ULONG p_ulSize);

	BOOL bLoadImage(LPCWSTR p_pcPath);

	void TransToMonoc(CString inputFileName,CString outBmpName,COLORREF dwdoor);
	HDC hGetHandle();

	CBitmap* bGetBitMap();
	int AntiRotateBmp90D(char *pBmpData, const int nPixelsOfWidth, const int nPixelsOfHeight, char *pBmpDataRotated);

	BOOL bSetBold(BOOL isBold);

	BOOL bSetWideHightTimes(int Htimes, int Wtimes);

	BOOL bSetCharSpace(int num);
public:
	CDC* m_poMemDC;                 //内存DC
	CBitmap* m_poMemBitMap;         //内存位图
	CBitmap* m_poOldMemBitMap;      

	ULONG m_ulWide;
	ULONG m_ulHigh;

	UINT m_usAlignMode;

	CFont m_font;
	LOGFONT m_logfont;
	int m_CharSpace;
};

