#include "StdAfx.h"
#include "MemDcImpl.h"
#include "atlimage.h"
#include "Gdiplus.h"

CMemDcImpl::CMemDcImpl(void)
{
	m_logfont.lfHeight = 20;
	m_logfont.lfWidth = 12;
	wcscpy_s(m_logfont.lfFaceName,_T("宋体"));
	m_CharSpace = 1;
}


CMemDcImpl::~CMemDcImpl(void)
{
}

BOOL CMemDcImpl::bInitDc(ULONG p_ulWide, ULONG p_ulHigh, BOOL isAxis)
{
	m_ulHigh = p_ulHigh;
	m_ulWide = p_ulWide;

	//创建单像素单色DC
	m_poMemDC = new CDC;	
	m_poMemDC->CreateCompatibleDC(NULL);
	if (m_poMemDC == NULL)
	{
		//创建失败返回
		return FALSE;
	}

	//创建单色位图
	LPBYTE lpBits = new BYTE[p_ulWide * p_ulHigh];
	memset(lpBits, 0, p_ulWide * p_ulHigh);
	m_poMemBitMap = new CBitmap;
	m_poMemBitMap->CreateBitmap(p_ulWide, p_ulHigh, 1, 1, lpBits);
	delete []lpBits;
	if (m_poMemBitMap == NULL)
	{
		//创建失败返回
		return FALSE;
	}

	//把内存DC和位图绑定，并且记录旧的位图
	m_poOldMemBitMap = m_poMemDC->SelectObject(m_poMemBitMap);

	//初始化内存DC的一些相关设置，背景设为白色，字体颜色为黑色
	m_poMemDC->FillSolidRect(0, 0, p_ulWide, p_ulHigh, RGB(255, 255, 255));
	m_poMemDC->SetTextColor(RGB(0, 0, 0));
	if(TRUE == isAxis)
	{
		m_poMemDC->MoveTo(0, 0);
		m_poMemDC->TextOutW(0,0, _T("测试文本"));
		m_poMemDC->TextOutW(0,20, _T("测试文本"));
		m_poMemDC->TextOutW(0,40, _T("测试文本"));
		m_poMemDC->TextOutW(0,60, _T("测试文本"));
		m_poMemDC->TextOutW(0,80, _T("测试文本"));
		m_poMemDC->TextOutW(0,100, _T("测试文本"));
		m_poMemDC->TextOutW(0,120, _T("测试文本"));
		m_poMemDC->TextOutW(0,140, _T("测试文本"));
		m_poMemDC->TextOutW(0,160, _T("测试文本"));
		m_poMemDC->TextOutW(0,180, _T("测试文本"));
		m_poMemDC->TextOutW(0,200, _T("测试文本"));
		m_poMemDC->TextOutW(0,220, _T("测试文本"));
		m_poMemDC->TextOutW(0,240, _T("测试文本"));
		m_poMemDC->TextOutW(0,260, _T("测试文本"));
		m_poMemDC->TextOutW(0,280, _T("测试文本"));
		m_poMemDC->TextOutW(0,300, _T("测试文本"));
		m_poMemDC->TextOutW(0,320, _T("测试文本"));
		m_poMemDC->TextOutW(0,340, _T("测试文本"));
		m_poMemDC->TextOutW(0,360, _T("测试文本"));
		m_poMemDC->TextOutW(0,380, _T("测试文本"));
	}
	return TRUE;
}

/*
DT_LEFT            = 0;         {左对齐}
DT_CENTER          = 1;         {水平居中}
DT_RIGHT           = 2;         {右对齐}*/
BOOL CMemDcImpl::bSetTextHorizontalAlign(UINT fMode)
{
	if (fMode != DT_LEFT  && fMode != DT_CENTER  && fMode != DT_RIGHT)
	{
		return FALSE;
	}

	m_usAlignMode = fMode;

	return TRUE;
}

BOOL CMemDcImpl::bSetPosition(ULONG ulPosX, ULONG ulPosY)
{
	if (ulPosX > m_ulWide)
	{
		return FALSE;
	}

	if (ulPosY > m_ulHigh)
	{
		return FALSE;
	}

	m_poMemDC->MoveTo(ulPosX, ulPosY);

	return TRUE;
}
BOOL CMemDcImpl::bSetCharSpace(int num)
{
	m_CharSpace = num;
	return TRUE;
}
BOOL CMemDcImpl::bSetBold(BOOL isBold)
{   
	if(isBold == TRUE)
	{  
		m_logfont.lfWeight   =   FW_BOLD;   
	}
	else
	{
		m_logfont.lfWeight   =   FW_NORMAL;       
	}
	return TRUE;
}
BOOL CMemDcImpl::bSetWideHightTimes(int Htimes, int Wtimes)
{
	switch (Htimes)
	{
	case 2:
		m_logfont.lfHeight = m_logfont.lfHeight*2;
		break; 
	case 3:
		m_logfont.lfHeight = m_logfont.lfHeight*3;
		break;
	case 4:
		m_logfont.lfHeight = m_logfont.lfHeight*4;
		break;
	}
	switch (Wtimes)
	{
	case 2:
		m_logfont.lfWidth = m_logfont.lfWidth*2;
		break; 
	case 3:
		m_logfont.lfWidth = m_logfont.lfWidth*3;
		break;
	case 4:
		m_logfont.lfWidth = m_logfont.lfWidth*4;
		break;
	}
	return TRUE;
}
BOOL CMemDcImpl::bDrawText(LPCWSTR p_lpText, BOOL p_bTextAsAlign)
{
	CPoint l_oPositon = m_poMemDC->GetCurrentPosition();
	m_font.CreateFontIndirect(&m_logfont); 
	m_poMemDC->SelectObject(m_font);
	SetTextCharacterExtra(m_poMemDC->m_hDC, m_CharSpace);

	if (p_bTextAsAlign)//对齐模式打印
	{
		RECT l_sRect = {0};
		l_sRect.top = l_oPositon.y;
		l_sRect.bottom = m_ulHigh;
		l_sRect.left = 0;
		l_sRect.right = m_ulWide;
		DrawTextEx(m_poMemDC->m_hDC, (LPWSTR)p_lpText, -1, &l_sRect, m_usAlignMode | DT_WORDBREAK| DT_NOPREFIX, NULL);
	}
	else//非对齐模式打印
	{
		   CSize size = m_poMemDC->GetTextExtent(p_lpText);
		   BITMAP l_sBitMap;
		   ::GetObject((HBITMAP)m_poMemBitMap->m_hObject, sizeof(BITMAP), (LPBYTE)&l_sBitMap); 
		   //需要换行时，第一行使用TextOutW（不支持自动换行），剩余行使用DrawTextEx（支持自动换行）一次性输出
		   if((l_oPositon.x + size.cx) > l_sBitMap.bmWidth)
		   {
			   int index = 0;//搜索到p_lpText中第几个字符应该是本行的最后一个字符
			   while((l_oPositon.x + m_poMemDC->GetTextExtent(p_lpText,index).cx) <= l_sBitMap.bmWidth)
			   {
				   index++;
			   }
			   index--;//得到p_lpText中在本行最后一个字符的索引
			   int ExtraPos = index;//换行打印起始位置
			   LPWSTR pHeadLine = (LPWSTR)malloc(sizeof(LPWSTR)*index + 1);//pHeadLine保存首行数据
			   pHeadLine[index] = L'\0';
			   while(index)
			   {
				   pHeadLine[index -1] = p_lpText[index - 1];
				   index--;
			   }
			   //打印首行数据
			   m_poMemDC->TextOutW(l_oPositon.x, l_oPositon.y, pHeadLine);
			   //打剩余行数据
			   RECT l_sRect = {0};
			   l_sRect.top = l_oPositon.y + size.cy;//计算出下一行的y坐标
			   l_sRect.bottom = m_ulHigh;
			   l_sRect.left = 0;
			   l_sRect.right = m_ulWide;
			   DrawTextEx(m_poMemDC->m_hDC, (LPWSTR)(p_lpText + ExtraPos), -1, &l_sRect, DT_WORDBREAK| DT_NOPREFIX, NULL);
		   }
		   //不会换行直接TextOutW打印
		   else
		   {
			   m_poMemDC->TextOutW(l_oPositon.x, l_oPositon.y, p_lpText);
		   }
	}
	ZeroMemory(&m_logfont,sizeof(LOGFONT));
	m_font.DeleteObject();
	m_logfont.lfHeight = 20;
	m_logfont.lfWidth = 12;
	wcscpy_s(m_logfont.lfFaceName,_T("宋体"));
	return TRUE;
}

//p_ulSize >= p_ulWide*p_ulHigh否则失败
BOOL CMemDcImpl::bGetData(BYTE* p_byData, ULONG p_ulSize)
{
	BITMAP l_sBitMap = {0};
	HBITMAP l_hbmpBitMap = (HBITMAP)m_poMemBitMap->m_hObject;

	//获取内存位图的信息
	if (!::GetObject(l_hbmpBitMap, sizeof(BITMAP), (LPBYTE)&l_sBitMap))   
	{
		return FALSE; 
	}
	//构造位图信息,单色位图信息，采用调色板
	BITMAPINFO l_sBitMapInfo;   
	memset(&l_sBitMapInfo, 0, sizeof(BITMAPINFO));

	l_sBitMapInfo.bmiHeader.biSize = sizeof(l_sBitMapInfo.bmiHeader);   
	l_sBitMapInfo.bmiHeader.biWidth = l_sBitMap.bmWidth;   
	l_sBitMapInfo.bmiHeader.biHeight = l_sBitMap.bmHeight;   
	l_sBitMapInfo.bmiHeader.biPlanes = 1;   
	l_sBitMapInfo.bmiHeader.biBitCount = 1;    
	l_sBitMapInfo.bmiHeader.biCompression = BI_RGB;    
	::GetDIBits(m_poMemDC->m_hDC, l_hbmpBitMap, 0, l_sBitMap.bmHeight, NULL, &l_sBitMapInfo, DIB_PAL_COLORS);
	l_sBitMapInfo.bmiHeader.biClrUsed = 2;   
	l_sBitMapInfo.bmiHeader.biClrImportant = 0; 

	//提取位图数据
	if (!::GetDIBits(m_poMemDC->m_hDC, l_hbmpBitMap, 0, l_sBitMap.bmHeight, p_byData, &l_sBitMapInfo, DIB_PAL_COLORS))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CMemDcImpl::bGetDataPart1(BYTE* p_byData, ULONG p_ulSize)
{
	BITMAP l_sBitMap = {0};
	HBITMAP l_hbmpBitMap = (HBITMAP)m_poMemBitMap->m_hObject;

	//获取内存位图的信息
	if (!::GetObject(l_hbmpBitMap, sizeof(BITMAP), (LPBYTE)&l_sBitMap))   
	{
		return FALSE; 
	}
	//构造位图信息,单色位图信息，采用调色板
	BITMAPINFO l_sBitMapInfo;   
	memset(&l_sBitMapInfo, 0, sizeof(BITMAPINFO));

	l_sBitMapInfo.bmiHeader.biSize = sizeof(l_sBitMapInfo.bmiHeader);   
	l_sBitMapInfo.bmiHeader.biWidth = l_sBitMap.bmWidth;   
	l_sBitMapInfo.bmiHeader.biHeight = l_sBitMap.bmHeight;   
	l_sBitMapInfo.bmiHeader.biPlanes = 1;   
	l_sBitMapInfo.bmiHeader.biBitCount = 1;    
	l_sBitMapInfo.bmiHeader.biCompression = BI_RGB;    
	l_sBitMapInfo.bmiHeader.biSizeImage = l_sBitMap.bmWidth * l_sBitMap.bmHeight; 
	l_sBitMapInfo.bmiHeader.biClrUsed = 2;   
	l_sBitMapInfo.bmiHeader.biClrImportant = 0; 

	//提取位图数据
	if (!::GetDIBits(m_poMemDC->m_hDC, l_hbmpBitMap, l_sBitMap.bmHeight/2, l_sBitMap.bmHeight, p_byData, &l_sBitMapInfo, DIB_PAL_COLORS))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CMemDcImpl::bGetDataPart2(BYTE* p_byData, ULONG p_ulSize)
{
	BITMAP l_sBitMap = {0};
	HBITMAP l_hbmpBitMap = (HBITMAP)m_poMemBitMap->m_hObject;

	//获取内存位图的信息
	if (!::GetObject(l_hbmpBitMap, sizeof(BITMAP), (LPBYTE)&l_sBitMap))   
	{
		return FALSE; 
	}
	//构造位图信息,单色位图信息，采用调色板
	BITMAPINFO l_sBitMapInfo;   
	memset(&l_sBitMapInfo, 0, sizeof(BITMAPINFO));

	l_sBitMapInfo.bmiHeader.biSize = sizeof(l_sBitMapInfo.bmiHeader);   
	l_sBitMapInfo.bmiHeader.biWidth = l_sBitMap.bmWidth;   
	l_sBitMapInfo.bmiHeader.biHeight = l_sBitMap.bmHeight;   
	l_sBitMapInfo.bmiHeader.biPlanes = 1;   
	l_sBitMapInfo.bmiHeader.biBitCount = 1;    
	l_sBitMapInfo.bmiHeader.biCompression = BI_RGB;    
	l_sBitMapInfo.bmiHeader.biSizeImage = l_sBitMap.bmWidth * l_sBitMap.bmHeight; 
	l_sBitMapInfo.bmiHeader.biClrUsed = 2;   
	l_sBitMapInfo.bmiHeader.biClrImportant = 0; 

	//提取位图数据
	if (!::GetDIBits(m_poMemDC->m_hDC, l_hbmpBitMap, 0, l_sBitMap.bmHeight/2, p_byData, &l_sBitMapInfo, DIB_PAL_COLORS))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CMemDcImpl::bGetDataPart1of3(BYTE* p_byData, ULONG p_ulSize)
{
	BITMAP l_sBitMap = {0};
	HBITMAP l_hbmpBitMap = (HBITMAP)m_poMemBitMap->m_hObject;

	//获取内存位图的信息
	if (!::GetObject(l_hbmpBitMap, sizeof(BITMAP), (LPBYTE)&l_sBitMap))   
	{
		return FALSE; 
	}
	//构造位图信息,单色位图信息，采用调色板
	BITMAPINFO l_sBitMapInfo;   
	memset(&l_sBitMapInfo, 0, sizeof(BITMAPINFO));

	l_sBitMapInfo.bmiHeader.biSize = sizeof(l_sBitMapInfo.bmiHeader);   
	l_sBitMapInfo.bmiHeader.biWidth = l_sBitMap.bmWidth;   
	l_sBitMapInfo.bmiHeader.biHeight = l_sBitMap.bmHeight;   
	l_sBitMapInfo.bmiHeader.biPlanes = 1;   
	l_sBitMapInfo.bmiHeader.biBitCount = 1;    
	l_sBitMapInfo.bmiHeader.biCompression = BI_RGB;    
	l_sBitMapInfo.bmiHeader.biSizeImage = l_sBitMap.bmWidth * l_sBitMap.bmHeight; 
	l_sBitMapInfo.bmiHeader.biClrUsed = 2;   
	l_sBitMapInfo.bmiHeader.biClrImportant = 0; 

	//提取位图数据
	if (!::GetDIBits(m_poMemDC->m_hDC, l_hbmpBitMap, l_sBitMap.bmHeight*(2/3), l_sBitMap.bmHeight, p_byData, &l_sBitMapInfo, DIB_PAL_COLORS))
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CMemDcImpl::bGetDataPart2of3(BYTE* p_byData, ULONG p_ulSize)
{
	BITMAP l_sBitMap = {0};
	HBITMAP l_hbmpBitMap = (HBITMAP)m_poMemBitMap->m_hObject;

	//获取内存位图的信息
	if (!::GetObject(l_hbmpBitMap, sizeof(BITMAP), (LPBYTE)&l_sBitMap))   
	{
		return FALSE; 
	}
	//构造位图信息,单色位图信息，采用调色板
	BITMAPINFO l_sBitMapInfo;   
	memset(&l_sBitMapInfo, 0, sizeof(BITMAPINFO));

	l_sBitMapInfo.bmiHeader.biSize = sizeof(l_sBitMapInfo.bmiHeader);   
	l_sBitMapInfo.bmiHeader.biWidth = l_sBitMap.bmWidth;   
	l_sBitMapInfo.bmiHeader.biHeight = l_sBitMap.bmHeight;   
	l_sBitMapInfo.bmiHeader.biPlanes = 1;   
	l_sBitMapInfo.bmiHeader.biBitCount = 1;    
	l_sBitMapInfo.bmiHeader.biCompression = BI_RGB;    
	l_sBitMapInfo.bmiHeader.biSizeImage = l_sBitMap.bmWidth * l_sBitMap.bmHeight; 
	l_sBitMapInfo.bmiHeader.biClrUsed = 2;   
	l_sBitMapInfo.bmiHeader.biClrImportant = 0; 

	//提取位图数据
	if (!::GetDIBits(m_poMemDC->m_hDC, l_hbmpBitMap, l_sBitMap.bmHeight*(1/3), l_sBitMap.bmHeight*(2/3), p_byData, &l_sBitMapInfo, DIB_PAL_COLORS))
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CMemDcImpl::bGetDataPart3of3(BYTE* p_byData, ULONG p_ulSize)
{
	BITMAP l_sBitMap = {0};
	HBITMAP l_hbmpBitMap = (HBITMAP)m_poMemBitMap->m_hObject;

	//获取内存位图的信息
	if (!::GetObject(l_hbmpBitMap, sizeof(BITMAP), (LPBYTE)&l_sBitMap))   
	{
		return FALSE; 
	}
	//构造位图信息,单色位图信息，采用调色板
	BITMAPINFO l_sBitMapInfo;   
	memset(&l_sBitMapInfo, 0, sizeof(BITMAPINFO));

	l_sBitMapInfo.bmiHeader.biSize = sizeof(l_sBitMapInfo.bmiHeader);   
	l_sBitMapInfo.bmiHeader.biWidth = l_sBitMap.bmWidth;   
	l_sBitMapInfo.bmiHeader.biHeight = l_sBitMap.bmHeight;   
	l_sBitMapInfo.bmiHeader.biPlanes = 1;   
	l_sBitMapInfo.bmiHeader.biBitCount = 1;    
	l_sBitMapInfo.bmiHeader.biCompression = BI_RGB;    
	l_sBitMapInfo.bmiHeader.biSizeImage = l_sBitMap.bmWidth * l_sBitMap.bmHeight; 
	l_sBitMapInfo.bmiHeader.biClrUsed = 2;   
	l_sBitMapInfo.bmiHeader.biClrImportant = 0; 

	//提取位图数据
	if (!::GetDIBits(m_poMemDC->m_hDC, l_hbmpBitMap, 0, l_sBitMap.bmHeight*(1/3), p_byData, &l_sBitMapInfo, DIB_PAL_COLORS))
	{
		return FALSE;
	}
	return TRUE;
}
void CMemDcImpl::TransToMonoc(CString inputFileName,CString outBmpName,COLORREF dwdoor)   
{
	CImage image;    
	HRESULT d = image.Load(inputFileName);  //载入图片
	int i = GetLastError();
	int maxY = image.GetHeight();    //图片高度
	int	maxX = image.GetWidth();    //图片宽度
	// 创建bitmap
	CBitmap mybitmap;
	mybitmap.CreateBitmap(maxX,maxY,1,8,NULL);

	HBITMAP hbitmap = (HBITMAP)mybitmap.m_hObject;

	CImage imageOut; 
	imageOut.Attach(hbitmap);

	COLORREF pixel;
	//依次读取每个象素点，并作相应的转换
	int r,g,b,avg;
	//依次读取每个象素点，并作相应的转换
	for(int x=0;x < maxX;x++)
	{
		for(int y=0;y< maxY;y++)
		{
			pixel=image.GetPixel(x,y);  //获取象素点
			//得到R、G、B、的值
			r=GetRValue(pixel);
			g=GetGValue(pixel);
			b=GetBValue(pixel);
			//处理象素点
			avg=(int)((r+g+b)/3);
			if ( RGB(avg,avg,avg) >dwdoor )
			{
				imageOut.SetPixel(x,y,RGB(115, 110, 110));
			}
			else
			{
				imageOut.SetPixel(x,y,RGB(0,0,0));
			}
		}
	}

	//保存bitmap图片
	imageOut.Save(outBmpName);
}
BOOL CMemDcImpl::bLoadImage(LPCWSTR p_pcPath)
{
	CImage l_oShowImage;
	CPoint l_oPositon = m_poMemDC->GetCurrentPosition();
	//加载图片文件
	
	l_oShowImage.Load(p_pcPath);
	if(l_oShowImage.GetBPP() != 1)
	{
		l_oShowImage.Detach();
		TransToMonoc(p_pcPath, CString("Bmptmp.bmp"), RGB(125,125,125));
		l_oShowImage.Load(CString("Bmptmp.bmp"));
	}
	int iWide;
	int iHigh;
	if (l_oShowImage.GetWidth() > (m_ulWide - l_oPositon.x))
	{
		iWide = (m_ulWide - l_oPositon.x);
	}
	else
	{
		iWide = l_oShowImage.GetWidth();
	}

	if (l_oShowImage.GetHeight() > (m_ulHigh - l_oPositon.y))
	{
		iHigh = (m_ulHigh - l_oPositon.y);
	}
	else
	{
		iHigh = l_oShowImage.GetHeight();
	}

	l_oShowImage.StretchBlt(m_poMemDC->m_hDC, l_oPositon.x, l_oPositon.y, iWide, iHigh, SRCCOPY);

	return TRUE;
}

HDC CMemDcImpl::hGetHandle()
{
	return m_poMemDC->m_hDC;
}
CBitmap* CMemDcImpl::bGetBitMap()
{
	return m_poMemBitMap;
}
//************************************************//
//函数： AntiRotateBmp90D //
//功能：将单色 bmp 图像数据转化为打印机指令所需数据 //
//参数： pBmpData---源数据指针 //
// nPixelsOfWidth----图像宽度（点数） //
// nPixelsOfHeight---图像高度（点数） //
// pBmpDataRotated---目标数据指针 //
//返回值： 1:转化成功 0:参数错误 //
//************************************************//
int CMemDcImpl::AntiRotateBmp90D(
	char *pBmpData,
	const int nPixelsOfWidth,
	const int nPixelsOfHeight,
	char *pBmpDataRotated
	)
{
	//定义过程中的变量
	int nBytesOfWidth = 0, nBytesOfHeight = 0;
	int i=0, col=0, row=0, index = 0, colbyte = 0;
	char* midData;
	unsigned char tempdata = 0, colnum = 0, rownum = 0;
	unsigned char temp[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
	//参数判断
	if (pBmpData == NULL || pBmpDataRotated == NULL) return 0;
	if (nPixelsOfWidth <= 0 || nPixelsOfHeight <= 0) return 0;
	if ((nPixelsOfWidth % 8) != 0 || (nPixelsOfHeight % 8) != 0) return 0;
	//获得实际图像尺寸
	nBytesOfWidth = (nPixelsOfWidth+31)/32*4;
	nBytesOfHeight = nPixelsOfHeight / 8;
	//反色, BMP 的 1 为白色的底色,与打印机定义相反
	midData = (char*)malloc(nBytesOfWidth*nPixelsOfHeight+1);
	for(i=0;i<nBytesOfWidth*nPixelsOfHeight;i++){midData[i] = 0xff-pBmpData[i];}
	//旋转, BMP 为横向排列,打印机下载数据为纵向排列
	for (row = 0; row <nPixelsOfWidth; row++){
		for (colbyte = 0; colbyte < nBytesOfHeight; colbyte++){
			index = row * nBytesOfHeight + colbyte;
			pBmpDataRotated[index] = 0x00;
			for (col = 0; col < 8; col++){
				colnum = col % 8;
				rownum = row % 8;
				if(colnum >= rownum)
					tempdata = temp[col] & (midData[(nPixelsOfHeight-1-colbyte*8-col) * nBytesOfWidth
					+ row / 8] >> (colnum-rownum));
				else
					tempdata = temp[col] & (midData[(nPixelsOfHeight-1-colbyte*8-col) * nBytesOfWidth
					+ row / 8] << (rownum-colnum));
				pBmpDataRotated[index] |= tempdata;
			}
		}
	}
	//释放中间缓冲区
	free(midData);
	return 1;
}