// CSearchDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Video_Hub_App.h"
#include "CUserDlg.h"
#include "CSearchDlg.h"


// CSearchDlg 对话框

CSearchDlg::CSearchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SEARCH_DLG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsClose = FALSE;
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()

	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()

	ON_WM_CLOSE()
END_MESSAGE_MAP()

BOOL SearchDlg_LoadImageResource(CImage* pImage, UINT nResID, LPCTSTR lpTyp)
{
	if (pImage == NULL)
		return false;
	pImage->Destroy();
	// 查找资源
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL)
		return false;
	// 加载资源
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}
	// 锁定内存中的指定资源
	LPVOID lpVoid = ::LockResource(hImgData);
	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);
	// 解除内存中的指定资源
	::GlobalUnlock(hNew);
	// 从指定内存创建流对象
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if (ht != S_OK)
	{
		GlobalFree(hNew);
	}
	else
	{
		// 加载图片
		pImage->Load(pStream);
		GlobalFree(hNew);
	}
	// 释放资源
	::FreeResource(hImgData);
	return true;
}

BOOL CSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	//初始化窗口尺寸
	int width = GetSystemMetrics(SM_CXFULLSCREEN) * 4 / 5;
	int heigh = GetSystemMetrics(SM_CYFULLSCREEN) * 4 / 5;
	CUserDlg* pParent = (CUserDlg*)GetParent();
	CRect CrLine = pParent->m_Line;

	temprect.TopLeft().x = CrLine.BottomRight().x + 50;;
	temprect.TopLeft().y = CrLine.TopLeft().y + 150;
	temprect.BottomRight().x = temprect.TopLeft().x + width - CrLine.BottomRight().x - 100;
	temprect.BottomRight().y = temprect.TopLeft().y + heigh - 250;

	CWnd::SetWindowPos(NULL, temprect.TopLeft().x, temprect.TopLeft().y, temprect.Width(), temprect.Height(), SWP_NOZORDER);

	GetWindowRect(&temprect);
	ScreenToClient(&temprect);
	font.CreateFont(50, 22, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("AST"));

	m_Brush.CreateSolidBrush(RGB(0, 0, 0));

	//后端数据
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CSearchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*************************************************************** 对 话 框 背 景 *************************************************************/

HBRUSH CSearchDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return m_Brush;
}

BOOL CSearchDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HCURSOR hcur = ::LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	::SetCursor(hcur);
	return TRUE;
}
//系统消息响应调用重绘函数
LRESULT CSearchDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT lrst = CDialog::DefWindowProc(message, wParam, lParam);
	if (!::IsWindow(m_hWnd))
		return lrst;

	if (
		message == WM_MOVE
		|| message == WM_PAINT
		|| message == WM_NCACTIVATE
		|| message == WM_NOTIFY
		)
	{
		CDC* pWinDC = GetWindowDC();
		if (pWinDC) {
			DrawSearchMenu(pWinDC);
		}
		ReleaseDC(pWinDC);
	}
	return lrst;
}
void CSearchDlg::OnClose()
{
	m_bIsClose = TRUE;
	CDialogEx::OnClose();
}
//绘制用户界面
void CSearchDlg::DrawSearchMenu(CDC* pDC) {
	if (m_hWnd) {
		CBrush BrushLine(RGB(194, 89, 136));	//常规笔刷
		//设置视频块的大小和头位置
		m_rtResultHead.TopLeft().x = 50;
		m_rtResultHead.TopLeft().y = 50;
		m_rtResultHead.BottomRight().x = temprect.Width() - 150;
		m_rtResultHead.BottomRight().y = m_rtResultHead.TopLeft().y + temprect.Height() / 5 + 50;
		m_offset_value = m_rtResultHead.Height() + 50;		//间隔
		CRect crResultNext = m_rtResultHead;
		CRect rcResultText = { crResultNext.TopLeft().x + 50,crResultNext.TopLeft().y + 100,crResultNext.Width() - 50,50 };

		for (Iterator<User> it = m_OnlineUserList.returnUserList().begin(); it != m_OnlineUserList.returnUserList().end(); it++) {
			if (it->name == m_serach) {
				string titletext;
				CRect textrect = rcResultText;
				pDC->SelectObject(&BrushLine);
				pDC->PatBlt(crResultNext.TopLeft().x, crResultNext.TopLeft().y, crResultNext.Width(), crResultNext.Height(), PATCOPY);
				pDC->SelectObject(&font); //选上新的字体
				pDC->SetTextColor(RGB(255, 255, 255));	//修改颜色
				pDC->SetBkColor(RGB(194, 89, 136));
				titletext = "用户名：" + it->name;
				CString CSvideo_name = titletext.c_str();
				pDC->DrawText(CSvideo_name, &textrect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

				OffsetRect(textrect, 0, 80);

				titletext = "用户性别：" + it->gender;
				CString CSvideo_size = titletext.c_str();
				pDC->DrawText(CSvideo_size, &textrect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
				m_rtPortBMP.BottomRight().x = crResultNext.BottomRight().x - 200;
				m_rtPortBMP.BottomRight().y = crResultNext.BottomRight().y - 30;
				m_rtPortBMP.TopLeft().y = m_rtPortBMP.BottomRight().y - 300;
				m_rtPortBMP.TopLeft().x = m_rtPortBMP.BottomRight().x - 300;

				CBitmap* pBitmap = new CBitmap;
				CBitmap* pOldBitmap;
				CDC* pDisplayMemDC = new CDC;
				pDisplayMemDC->CreateCompatibleDC(pDC);
				pBitmap->LoadBitmap(IDB_BITMAP_PORT);
				pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
				pDC->BitBlt(m_rtPortBMP.left, m_rtPortBMP.top, m_rtPortBMP.Width(), m_rtPortBMP.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
				pBitmap->DeleteObject();
			}
			for (Iterator<Video> it2 = it->returnVideoList()->begin(); it2 != it->returnVideoList()->end(); it2++) {
				if (it2->showName() == m_serach) {
					// it2可以看作是指向找到video的指针
					string titletext;
					CRect textrect = rcResultText;
					pDC->SelectObject(&BrushLine);
					pDC->PatBlt(crResultNext.TopLeft().x, crResultNext.TopLeft().y, crResultNext.Width(), crResultNext.Height(), PATCOPY);
					pDC->SelectObject(&font); //选上新的字体
					pDC->SetTextColor(RGB(255, 255, 255));	//修改颜色
					pDC->SetBkColor(RGB(194, 89, 136));
					titletext = "视频名称：" + it2->video_name;
					CString CSvideo_name = titletext.c_str();
					pDC->DrawText(CSvideo_name, &textrect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

					OffsetRect(textrect, 0, 80);

					titletext = "视频大小：" + it2->video_size + "MB";
					CString CSvideo_size = titletext.c_str();
					pDC->DrawText(CSvideo_size, &textrect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

					OffsetRect(textrect, 0, 80);

					titletext = "视频时长：" + it2->video_time + "Min";
					CString CSvideo_time = titletext.c_str();
					pDC->DrawText(CSvideo_time, &textrect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

					OffsetRect(textrect, 0, 80);

					titletext = "视频发布者：" + it2->video_uploader;
					CString CSvideo_uploader = titletext.c_str();
					pDC->DrawText(CSvideo_uploader, &textrect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
					
					m_rtVideoBMP.BottomRight().x = m_rtResultHead.BottomRight().x - 200;
					m_rtVideoBMP.BottomRight().y = m_rtResultHead.BottomRight().y - 30;
					m_rtVideoBMP.TopLeft().y = m_rtResultHead.TopLeft().y + 30;
					m_rtVideoBMP.TopLeft().x = m_rtVideoBMP.BottomRight().x - 450;

					CBitmap* pBitmap = new CBitmap;
					CBitmap* pOldBitmap;
					CDC* pDisplayMemDC = new CDC;
					pDisplayMemDC->CreateCompatibleDC(pDC);
					pBitmap->LoadBitmap(IDB_BITMAP_VIDEO);
					pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
					pDC->BitBlt(m_rtVideoBMP.left, m_rtVideoBMP.top, m_rtVideoBMP.Width(), m_rtVideoBMP.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
					pBitmap->DeleteObject();
				}
			}
		}

	}
}
