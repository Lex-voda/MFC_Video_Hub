// MFC_TESTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Video_Hub_App.h"
#include "Video_Hub_Dlg.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_TESTDlg 对话框


CVideoHubDlg::CVideoHubDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIDEO_HUB_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVideoHubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVideoHubDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()	
	ON_WM_SETCURSOR()

	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCMOUSEMOVE()

	ON_MESSAGE(WM_OPENNEWDLG, OpenNewDlg)
END_MESSAGE_MAP()


// CMFC_TESTDlg 消息处理程序

//# 从资源加载图标函数 #
BOOL LoadImageFromResource(CImage *pImage, UINT nResID, LPCTSTR lpTyp)
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

BOOL CVideoHubDlg::OnInitDialog()
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
	temprect = { 0, 0, width,heigh };
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);
	
	m_Brush.CreateSolidBrush(RGB(0,0,0));
	//子窗口
	Log = nullptr;
	Reg = nullptr;
	User = nullptr;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVideoHubDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVideoHubDlg::OnPaint()
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
HCURSOR CVideoHubDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*************************************************************** 对 话 框 背 景 *************************************************************/

HBRUSH CVideoHubDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);
	return m_Brush;
	//HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	//return hbr;
}

/*************************************************************** 鼠 标 光 标 设 定 *************************************************************/

BOOL CVideoHubDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HCURSOR hcur = ::LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	::SetCursor(hcur);
	return TRUE;
	//return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


/*************************************************************** 自 绘 标 题 栏 相 关 函 数 *************************************************************/
//系统消息响应调用重绘函数
LRESULT CVideoHubDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT lrst = CDialog::DefWindowProc(message, wParam, lParam);
	if (!::IsWindow(m_hWnd))
		return lrst;

	if (
		message == WM_MOVE
		|| message == WM_PAINT
		|| message == WM_NCPAINT
		|| message == WM_NCACTIVATE
		|| message == WM_NOTIFY
		)
	{
		CDC* pWinDC = GetWindowDC();
		if (pWinDC) {
			DrawTitleBar(pWinDC);
			if (Log && !Log->m_bIsClose)
				return lrst;
			if (Reg && !Reg->m_bIsClose)
				return lrst;
			if (User && !User->m_bIsClose)
				return lrst;
			DrawMenuLogo(pWinDC);
			DrawButtle(pWinDC);
		}
		ReleaseDC(pWinDC);
	}
	return lrst;
}

// 重绘标题栏
void CVideoHubDlg::DrawTitleBar(CDC *pDC)
{
	if (m_hWnd)
	{
		CBrush Brush(RGB(0, 0, 0));
		CBrush* pOldBrush = pDC->SelectObject(&Brush);

		CRect rtWnd, rtTitle, rtButtons;
		GetWindowRect(&rtWnd);
		//取得标题栏的位置
		rtTitle.left = GetSystemMetrics(SM_CXFRAME);
		rtTitle.top = GetSystemMetrics(SM_CYFRAME);
		rtTitle.right = rtWnd.right - rtWnd.left - GetSystemMetrics(SM_CXFRAME);
		rtTitle.bottom = rtTitle.top + GetSystemMetrics(SM_CYSIZE);

		CPoint point;
		
		//绘制美化线条
		CBrush BrushLine(RGB(21, 18, 17));
		pDC->SelectObject(&BrushLine);
		point.x = rtWnd.Width() - 0;
		point.y = GetSystemMetrics(SM_CYSIZE) + GetSystemMetrics(SM_CYFRAME);
		pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
		pDC->SelectObject(pOldBrush);

		//准备画XP风格按钮
		CBitmap* pBitmap = new CBitmap;
		CBitmap* pOldBitmap;
		CDC* pDisplayMemDC = new CDC;
		pDisplayMemDC->CreateCompatibleDC(pDC);

		//重画关闭button
		rtButtons.left = rtTitle.right - 50;
		rtButtons.top = rtTitle.top;
		rtButtons.right = rtButtons.left + 50;
		rtButtons.bottom = rtButtons.top + 50;
		if (m_bCloseShow)
			pBitmap->LoadBitmap(IDB_BITMAP_CLOSE2);
		else
			pBitmap->LoadBitmap(IDB_BITMAP_CLOSE);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtExit = rtButtons;
		m_rtButtExit.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();

		//重画最大化/恢复button
		rtButtons.right = rtButtons.left - 2;
		rtButtons.left = rtButtons.right - 50;
		if (IsZoomed())//如果窗口已最大化，则返回值为非零；如果窗口未最大化，则返回值为零。
		{
			if (m_bMaxShow)
				pBitmap->LoadBitmap(IDB_BITMAP_SHRINK2);
			else
				pBitmap->LoadBitmap(IDB_BITMAP_SHRINK);
		}			
		else
		{
			if (m_bMaxShow)
				pBitmap->LoadBitmap(IDB_BITMAP_MAX2);
			else
				pBitmap->LoadBitmap(IDB_BITMAP_MAX);
		}
		
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtMax = rtButtons;
		m_rtButtMax.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();

		//重画最小化button
		rtButtons.right = rtButtons.left - 2;
		rtButtons.left = rtButtons.right - 50;
		if (m_bMiniShow)
			pBitmap->LoadBitmap(IDB_BITMAP_MINI2);
		else
			pBitmap->LoadBitmap(IDB_BITMAP_MINI);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtMin = rtButtons;
		m_rtButtMin.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();

		//重画caption
		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		rtTitle.left = 80;
		rtTitle.top = 4;
		rtTitle.bottom = rtTitle.top + 50;

		CFont font;
		font.CreateFont(50, 22, 0, 0, FW_THIN, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("AST"));          
		//自定义字体
		pDC->SelectObject(&font); //选上新的字体
		pDC->SetTextColor(RGB(194, 89, 136));	//修改颜色
		CString m_strTitle = "Video Hub";
		pDC->DrawText(m_strTitle, &rtTitle, DT_LEFT);
		pDC->SetBkMode(nOldMode);

		DeleteObject(&font);
		//图标
		rtButtons.left = 0;
		rtButtons.top = 4;
		rtButtons.right = rtButtons.left + 80;
		rtButtons.bottom = rtButtons.top + 50;
		pBitmap->LoadBitmap(IDB_BITMAP_LOGO);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		ReleaseDC(pDisplayMemDC);
		delete pDisplayMemDC;
		delete pBitmap;
	}
}

// 重绘关闭最小化按钮
void CVideoHubDlg::DrawCloseButton(CDC *pDC)
{
	if (m_hWnd)
	{
		CRect rtWnd, rtTitle, rtButtons;
		GetWindowRect(&rtWnd);
		//取得标题栏的位置
		rtTitle.left = GetSystemMetrics(SM_CXFRAME);
		rtTitle.top = GetSystemMetrics(SM_CYFRAME);
		rtTitle.right = rtWnd.right - rtWnd.left - GetSystemMetrics(SM_CXFRAME);
		rtTitle.bottom = rtTitle.top + GetSystemMetrics(SM_CYSIZE);

		//准备画XP风格按钮
		CBitmap* pBitmap = new CBitmap;
		CBitmap* pOldBitmap;
		CDC* pDisplayMemDC = new CDC;
		pDisplayMemDC->CreateCompatibleDC(pDC);

		//重画关闭button
		rtButtons.left = rtTitle.right - 50;
		rtButtons.top = rtTitle.top + 0;
		rtButtons.right = rtButtons.left + 50;
		rtButtons.bottom = rtButtons.top + 50;
		if (m_bCloseShow)
			pBitmap->LoadBitmap(IDB_BITMAP_CLOSE2);
		else
			pBitmap->LoadBitmap(IDB_BITMAP_CLOSE);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtExit = rtButtons;
		m_rtButtExit.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();

		//重画最小化button
		rtButtons.right = rtButtons.left - 50;
		rtButtons.left = rtButtons.right - 50;
		if (m_bMiniShow)
			pBitmap->LoadBitmap(IDB_BITMAP_MINI2);
		else
			pBitmap->LoadBitmap(IDB_BITMAP_MINI);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtMin = rtButtons;
		m_rtButtMin.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();

		ReleaseDC(pDisplayMemDC);
		delete pDisplayMemDC;
		delete pBitmap;
	}
}
/*************************************************************** 自 绘 用 户 区 相 关 函 数 *************************************************************/
// 绘制菜单Logo
void CVideoHubDlg::DrawMenuLogo(CDC* pDC) {
	if (m_hWnd)
	{
		//初始化LOGO区域
		CBrush BrushBack(RGB(0, 0, 0));
		pDC->SelectObject(&BrushBack);
		pDC->PatBlt(m_MeueLogo.TopLeft().x, m_MeueLogo.TopLeft().y, m_MeueLogo.Width(), m_MeueLogo.Height(), PATCOPY);

		GetWindowRect(&m_MeueLogo);
		ScreenToClient(&m_MeueLogo);
		m_MeueLogo.TopLeft().x += m_MeueLogo.Width() / 2 - 657;
		m_MeueLogo.TopLeft().y += m_MeueLogo.Height() * 0.25;

		CBitmap* pBitmap = new CBitmap;
		CBitmap* pOldBitmap;
		CDC* pDisplayMemDC = new CDC;
		pDisplayMemDC->CreateCompatibleDC(pDC);
		pBitmap->LoadBitmap(IDB_BITMAP_COVER);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(m_MeueLogo.left, m_MeueLogo.top, m_MeueLogo.Width(), m_MeueLogo.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();
		ReleaseDC(pDisplayMemDC);
		delete pDisplayMemDC;
		delete pBitmap;
	}
}
//绘制按钮
void CVideoHubDlg::DrawButtle(CDC* pDC) {
	if (m_hWnd) {
		//初始化按钮界面
		CBrush BrushBack(RGB(0, 0, 0));
		pDC->SelectObject(&BrushBack);
		pDC->PatBlt(m_rtButtLog.TopLeft().x, m_rtButtLog.TopLeft().y, m_rtButtLog.Width(), 360, PATCOPY);

		//绘制按钮
		CBrush HighLine(RGB(134, 52, 53));		//高亮笔刷
		CBrush BrushLine(RGB(194, 89, 136));	//常规笔刷
		//绘制登录按钮
		GetWindowRect(&m_rtButtLog);
		ScreenToClient(&m_rtButtLog);
		m_rtButtLog.TopLeft().x += m_rtButtLog.Width() / 3;
		m_rtButtLog.TopLeft().y += m_rtButtLog.Height() * 0.6;
		m_rtButtLog.BottomRight().x -= m_rtButtLog.TopLeft().x;
		m_rtButtLog.BottomRight().y = m_rtButtLog.TopLeft().y + 60;
		if (m_bLogShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_rtButtLog.TopLeft().x, m_rtButtLog.TopLeft().y, m_rtButtLog.Width(), m_rtButtLog.Height(), PATCOPY);
		pDC->SelectObject(&BrushLine);
		//绘制注册按钮
		m_rtButtRis = m_rtButtLog;
		m_rtButtRis.BottomRight().y += 100;
		m_rtButtRis.TopLeft().y += 100;
		if (m_bRisShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_rtButtRis.TopLeft().x, m_rtButtRis.TopLeft().y, m_rtButtRis.BottomRight().x - m_rtButtRis.TopLeft().x, 60, PATCOPY);
		pDC->SelectObject(&BrushLine);
		//绘制访客按钮
		m_rtButtVis = m_rtButtRis;
		m_rtButtVis.BottomRight().y += 100;
		m_rtButtVis.TopLeft().y += 100;
		if (m_bVisShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_rtButtVis.TopLeft().x, m_rtButtVis.TopLeft().y, m_rtButtVis.BottomRight().x - m_rtButtVis.TopLeft().x, 60, PATCOPY);
		pDC->SelectObject(&BrushLine);
		//绘制退出按钮
		m_rtButtExi = m_rtButtVis;
		m_rtButtExi.BottomRight().y += 100;
		m_rtButtExi.TopLeft().y += 100;
		if (m_bExiShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_rtButtExi.TopLeft().x, m_rtButtExi.TopLeft().y, m_rtButtExi.BottomRight().x - m_rtButtExi.TopLeft().x, 60, PATCOPY);
		pDC->SelectObject(&BrushLine);
		//输出按钮文字
		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		CFont font;
		font.CreateFont(50, 22, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("AST"));
		//自定义字体
		pDC->SelectObject(&font); //选上新的字体
		pDC->SetTextColor(RGB(255, 255, 255));	//修改颜色
		CString m_strButtle = "登 录";
		pDC->DrawText(m_strButtle, &m_rtButtLog, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "注 册";
		pDC->DrawText(m_strButtle, &m_rtButtRis, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "以 访 客 身 份 登 录";
		pDC->DrawText(m_strButtle, &m_rtButtVis, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "退 出";
		pDC->DrawText(m_strButtle, &m_rtButtExi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SetBkMode(nOldMode);

		DeleteObject(&font);
	}
}
//响应对话框的移动
LRESULT CVideoHubDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return HTCAPTION;
	return CDialogEx::OnNcHitTest(point);
}

//响应最大化、最小化、关闭消息
void CVideoHubDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_rtButtExit.PtInRect(point))
		SendMessage(WM_CLOSE);
	else if (m_rtButtMin.PtInRect(point))
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(point.x, point.y));
	else if (m_rtButtMax.PtInRect(point))
		if (IsZoomed())
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, MAKELPARAM(point.x, point.y));
		else
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, MAKELPARAM(point.x, point.y));
	//用户区按钮
	CRect Fixrect;
	GetWindowRect(Fixrect);
	CPoint Fixpoint;
	Fixpoint.x = point.x - Fixrect.TopLeft().x;
	Fixpoint.y = point.y - Fixrect.TopLeft().y;
	if (   m_rtButtLog.PtInRect(Fixpoint)
		|| m_rtButtRis.PtInRect(Fixpoint)
		|| m_rtButtVis.PtInRect(Fixpoint)) {
		OnNcButtonUser(nHitTest, Fixpoint);
	}
	else if (m_rtButtExi.PtInRect(Fixpoint))
		SendMessage(WM_CLOSE);
	CDialogEx::OnNcLButtonDown(nHitTest, point);
}

//在鼠标移动函数中判断是否选中按钮
void CVideoHubDlg::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_rtButtExit.PtInRect(point))
	{
		m_bCloseShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if(m_bCloseShow)
	{
		m_bCloseShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_rtButtMin.PtInRect(point))
	{
		m_bMiniShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if(m_bMiniShow)
	{
		m_bMiniShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_rtButtMax.PtInRect(point))
	{
		m_bMaxShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bMaxShow)
	{
		m_bMaxShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC);
		ReleaseDC(pWinDC);
	}

	if (Log && !Log->m_bIsClose) 
		return;
	if (Reg && !Reg->m_bIsClose) 
		return;
	if (User && !User->m_bIsClose)
		return;

	CRect Fixrect;
	GetWindowRect(Fixrect);
	CPoint Fixpoint;
	Fixpoint.x = point.x - Fixrect.TopLeft().x;
	Fixpoint.y = point.y - Fixrect.TopLeft().y;
	if (m_rtButtLog.PtInRect(Fixpoint)) {
		m_bLogShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bLogShow) {
		m_bLogShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_rtButtRis.PtInRect(Fixpoint)) {
		m_bRisShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bRisShow) {
		m_bRisShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_rtButtVis.PtInRect(Fixpoint)) {
		m_bVisShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bVisShow) {
		m_bVisShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_rtButtExi.PtInRect(Fixpoint )) {
		m_bExiShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bExiShow) {
		m_bExiShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	CDialogEx::OnNcMouseMove(nHitTest, point);
}

/********************************控件和功能************************************/
//响应菜单按钮，创建菜单的子窗口
void CVideoHubDlg::OnNcButtonUser(UINT nHitTest, CPoint point) {
	if (m_rtButtLog.PtInRect(point)) {
		if (Log) {
			delete[]Log;
			Log = nullptr;
		}
		Log = new CLoginDlg(this);
		Log->Create(IDD_LOGIN_DIALOG,this);
		Log->ShowWindow(SW_SHOW);
	}
	else if (m_rtButtRis.PtInRect(point)) {
		if (Reg) {
			delete[]Reg;
			Reg = nullptr;
		}
		Reg = new CRegisterDlg(this);
		Reg->Create(IDD_REGISTER_DIALOG, this);
		Reg->ShowWindow(SW_SHOW);
	}
	else if (m_rtButtVis.PtInRect(point)) {
		Interface New_User;
		New_User.initialize();
		string username = "访客";
		string userkey = "1";
		if (New_User.signIn(username, userkey)) {		//登录成功，账号密码合法
			m_VH_OnlineUserList = New_User;
			m_Log_User = "访客";
			::SendMessage(this->m_hWnd,WM_OPENNEWDLG, 0, 0);
		}
	}
}
//接受消息打开用户窗口
LRESULT CVideoHubDlg::OpenNewDlg(WPARAM wParam, LPARAM lParam) {
	if (User) {
		delete[]User;
		User = nullptr;
	}
	User = new CUserDlg(this);
	User->Create(IDD_USER_DIALOG, this);
	User->m_OnlineUserList = m_VH_OnlineUserList;
	User->ShowWindow(SW_SHOW);
	return 0;
}