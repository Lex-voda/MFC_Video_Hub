// CUserDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Video_Hub_App.h"
#include "Video_Hub_Dlg.h"
#include "CUserDlg.h"


// CUserDlg 对话框

CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_USER_DIALOG, pParent)
	, m_search_str(_T(""))
{	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsClose = FALSE;
}
void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USER_SEARCH, m_User_Search);	//编辑框控件的消息映射
	DDX_Text(pDX, IDC_USER_SEARCH, m_search_str);
}
BEGIN_MESSAGE_MAP(CUserDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()

	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()

	ON_WM_CHAR()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

BOOL UserDlg_LoadImageResource(CImage* pImage, UINT nResID, LPCTSTR lpTyp)
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

BOOL CUserDlg::OnInitDialog()
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
	GetWindowRect(&temprect);
	ScreenToClient(&temprect);
	temprect.BottomRight().x = temprect.TopLeft().x + width;
	temprect.BottomRight().y = temprect.TopLeft().y + heigh;
	temprect.TopLeft().y += 50;
	CWnd::SetWindowPos(NULL, temprect.TopLeft().x, temprect.TopLeft().y, temprect.Width(), temprect.Height(), SWP_NOZORDER);

	font.CreateFont(50, 22, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("AST"));

	m_Brush.CreateSolidBrush(RGB(0, 0, 0));
	//子窗口
	m_Video = nullptr;
	m_Launch = nullptr;
	m_Search = nullptr;
	//后端数据
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUserDlg::OnPaint()
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
HCURSOR CUserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*************************************************************** 对 话 框 背 景 *************************************************************/

HBRUSH CUserDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_USER_SEARCH) {
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkColor(RGB(194, 89, 136));
		pDC->SelectObject(&font); //选上新的字体 
	}
	return m_Brush;
}

/*************************************************************** 鼠 标 光 标 设 定 *************************************************************/

BOOL CUserDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HCURSOR hcur = ::LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	::SetCursor(hcur);
	return TRUE;
}

//系统消息响应调用重绘函数
LRESULT CUserDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
			DrawUserMenu(pWinDC);
			DrawButtle(pWinDC);
		}
		ReleaseDC(pWinDC);
	}
	return lrst;
}
//响应按钮消息
void CUserDlg::OnLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_crMyVideo.PtInRect(point)) {
		if (m_Launch != nullptr) {
			HWND hTemp = m_Launch->GetSafeHwnd();	//获得发布窗口的句柄;
			::SendMessage(hTemp, WM_CLOSE, 0, 0);		//关闭发布窗口
			delete[]m_Launch;
			m_Launch = nullptr;
		}
		if (m_Search != nullptr) {
			HWND hTemp = m_Search->GetSafeHwnd();	//获得搜索窗口的句柄;
			::SendMessage(hTemp, WM_CLOSE, 0, 0);		//关闭搜索窗口
			delete[]m_Search;
			m_Search = nullptr;
		}
		m_OnlineUserList.initialize();
		if (m_Video) {
			delete[]m_Video;
			m_Video = nullptr;
		}
		m_Video = new CVideoDlg(this);
		m_Video->m_OnlineUserList = m_OnlineUserList;
		m_Video->Create(IDD_VIDEO_DIALOG, this);
		m_Video->ShowWindow(SW_SHOW);
	}
	else if (m_crLaunch.PtInRect(point)) {
		if (m_Video != nullptr) {
			HWND hTemp = m_Video->GetSafeHwnd();	//获得视频窗口的句柄;
			::SendMessage(hTemp, WM_CLOSE, 0, 0);		//关闭视频窗口
			delete[]m_Video;
			m_Video = nullptr;
		}
		if (m_Search != nullptr) {
			HWND hTemp = m_Search->GetSafeHwnd();	//获得搜索窗口的句柄;
			::SendMessage(hTemp, WM_CLOSE, 0, 0);		//关闭搜索窗口
			delete[]m_Search;
			m_Search = nullptr;
		}
		if (m_Launch) {
			delete[]m_Launch;
			m_Launch = nullptr;
		}
		m_Launch = new CLaunchDlg(this);
		m_Launch->m_OnlineUserList = m_OnlineUserList;
		m_Launch->Create(IDD_LAUNCH_DLG, this);
		m_Launch->ShowWindow(SW_SHOW);
	}
	else if (m_crCan.PtInRect(point))
		SendMessage(WM_CLOSE);
	CDialogEx::OnLButtonDown(nHitTest, point);
}
//在鼠标移动函数中判断是否选中按钮
void CUserDlg::OnMouseMove(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_crCan.PtInRect(point))
	{
		m_bCanShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bCanShow)
	{
		m_bCanShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_crLaunch.PtInRect(point))
	{
		m_bLauShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bLauShow)
	{
		m_bLauShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	if (m_crMyVideo.PtInRect(point))
	{
		m_bMyVidShow = TRUE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	else if (m_bMyVidShow)
	{
		m_bMyVidShow = FALSE;
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawButtle(pWinDC);
		ReleaseDC(pWinDC);
	}
	CDialogEx::OnMouseMove(nHitTest, point);
}

void CUserDlg::OnClose()
{
	m_bIsClose = TRUE;
	CDialogEx::OnClose();
}
//绘制用户界面
void CUserDlg::DrawUserMenu(CDC* pDC) {
	if (m_hWnd) {
		CBrush BrushLine(RGB(194, 89, 136));	//常规笔刷
		GetWindowRect(&m_Line);
		ScreenToClient(&m_Line);
		m_Line.TopLeft().x += m_Line.Width() / 4;
		m_Line.BottomRight().x = m_Line.TopLeft().x + 10;
		m_Line.BottomRight().y;

		pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_Line.TopLeft().x, m_Line.TopLeft().y, m_Line.Width(), m_Line.Height(), PATCOPY);
		
		GetWindowRect(&m_crPort);
		ScreenToClient(&m_crPort);
		int middleline = (m_Line.TopLeft().x + temprect.TopLeft().x) / 2;
		int PortWidth = 300;
		m_crPort.TopLeft().x = middleline - PortWidth / 2;
		m_crPort.BottomRight().x = m_crPort.TopLeft().x + PortWidth;
		m_crPort.TopLeft().y = m_Line.Height() * 0.1;
		m_crPort.BottomRight().y = m_crPort.TopLeft().y + PortWidth ;
		//画头像
		CBitmap* pBitmap = new CBitmap;
		CBitmap* pOldBitmap;
		CDC* pDisplayMemDC = new CDC;
		pDisplayMemDC->CreateCompatibleDC(pDC);
		pBitmap->LoadBitmap(IDB_BITMAP_PORT);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(m_crPort.left, m_crPort.top, m_crPort.Width(), m_crPort.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();
		//用户名
		CVideoHubDlg* pParent = (CVideoHubDlg*)GetParent();
		CString UserName = pParent->m_Log_User;
		int NameWidth = UserName.GetLength();
		NameWidth *= 30;
		m_crUserName = m_crPort;
		m_crUserName.TopLeft().x = middleline - NameWidth / 2 - 10;
		m_crUserName.TopLeft().y = m_crPort.BottomRight().y + m_crPort.Height() * 0.2;
		m_crUserName.BottomRight().y = m_crUserName.TopLeft().y + 50;
		m_crUserName.BottomRight().x = middleline + NameWidth / 2 + 10;

		pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_crUserName.TopLeft().x, m_crUserName.TopLeft().y, m_crUserName.Width(), m_crUserName.Height(), PATCOPY);
		//画性别
		CRect crgender;
		crgender.TopLeft().x = m_crUserName.BottomRight().x +5 ;
		crgender.TopLeft().y = m_crUserName.TopLeft().y;
		crgender.BottomRight().x = crgender.TopLeft().x + 50;
		crgender.BottomRight().y = crgender.TopLeft().y + 50;

		if (m_OnlineUserList.online != Iterator<User>()) {
			pBitmap = new CBitmap;
			pDisplayMemDC = new CDC;
			pDisplayMemDC->CreateCompatibleDC(pDC);
			m_User_Gender = m_OnlineUserList.online->gender;
			if (m_User_Gender == "male")
				pBitmap->LoadBitmap(IDB_BITMAP_MALE);
			else if (m_User_Gender == "female")
				pBitmap->LoadBitmap(IDB_BITMAP_FEMALE);
			else if (m_User_Gender == "secret")
				pBitmap->LoadBitmap(IDB_BITMAP_SECRET);
			pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
			pDC->BitBlt(crgender.left, crgender.top, crgender.Width(), crgender.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
			pDisplayMemDC->SelectObject(pOldBitmap);
			pBitmap->DeleteObject();
		}
		//搜索框
		GetWindowRect(&m_crSearch);
		ScreenToClient(&m_crSearch);
		m_crSearch.TopLeft().x = m_Line.BottomRight().x + PortWidth;
		m_crSearch.BottomRight().y = m_crPort.TopLeft().y - 60;
		m_crSearch.TopLeft().y = m_crSearch.BottomRight().y - 60;
		m_crSearch.BottomRight().x -= PortWidth;
		CWnd* pWnd;
		pWnd = GetDlgItem(IDC_USER_SEARCH);    //获取控件指针
		if (pWnd) {
			pWnd->SetWindowPos(NULL, m_crSearch.TopLeft().x , m_crSearch.TopLeft().y, m_crSearch.Width(), m_crSearch.Height(), SWP_NOZORDER);
			//字体
			pWnd->SetFont(&font);
		}
		//搜索图标
		m_crbmpsearch.TopLeft().x = m_crSearch.TopLeft().x - 80;
		m_crbmpsearch.BottomRight().x = m_crbmpsearch.TopLeft().x + 50;
		m_crbmpsearch.TopLeft().y = m_crSearch.TopLeft().y;
		m_crbmpsearch.BottomRight().y = m_crbmpsearch.TopLeft().y + 50;

		pBitmap = new CBitmap;
		pDisplayMemDC = new CDC;
		pDisplayMemDC->CreateCompatibleDC(pDC);
		pBitmap->LoadBitmap(IDB_BITMAP_SEARCH);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(m_crbmpsearch.left, m_crbmpsearch.top, m_crbmpsearch.Width(), m_crbmpsearch.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&font); //选上新的字体
		pDC->SetTextColor(RGB(255, 255, 255));	//修改颜色
		pDC->SetBkColor(TRANSPARENT);
		pDC->DrawText(UserName, &m_crUserName, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SetBkMode(nOldMode);
	}
}
//自绘按钮
void CUserDlg::DrawButtle(CDC* pDC) {
	if (m_hWnd) {
		//绘制按钮
		CBrush HighLine(RGB(134, 52, 53));		//高亮笔刷
		CBrush BrushLine(RGB(194, 89, 136));	//常规笔刷
		//绘制退出按钮
	    GetWindowRect(&m_crCan);
		ScreenToClient(&m_crCan);
	
		m_crCan.BottomRight().y -= m_crUserName.Height()*3;
		m_crCan.TopLeft().y = m_crCan.BottomRight().y - m_crUserName.Height();
		m_crCan.TopLeft().x = m_crPort.TopLeft().x;
		m_crCan.BottomRight().x = m_crPort.BottomRight().x;

		pDC->SelectObject(&BrushLine);
		if(m_bCanShow)
			pDC->SelectObject(&HighLine);
		pDC->PatBlt(m_crCan.TopLeft().x, m_crCan.TopLeft().y, m_crCan.Width(), m_crCan.Height(), PATCOPY);
		//绘制发布按钮
		m_crLaunch = m_crCan;
		m_crLaunch.BottomRight().y = m_crCan.TopLeft().y - 2* m_crCan.Height();
		m_crLaunch.TopLeft().y = m_crLaunch.BottomRight().y - m_crCan.Height();
		m_crLaunch.TopLeft().x = m_crCan.TopLeft().x;
		m_crLaunch.BottomRight().x = m_crCan.BottomRight().x;

		pDC->SelectObject(&BrushLine);
		if (m_bLauShow)
			pDC->SelectObject(&HighLine);
		pDC->PatBlt(m_crLaunch.TopLeft().x, m_crLaunch.TopLeft().y, m_crLaunch.Width(), m_crLaunch.Height(), PATCOPY);
		//绘制我的视频
		m_crMyVideo = m_crLaunch;
		m_crMyVideo.BottomRight().y = m_crLaunch.TopLeft().y - 2 * m_crLaunch.Height();
		m_crMyVideo.TopLeft().y = m_crMyVideo.BottomRight().y - m_crLaunch.Height();
		m_crMyVideo.TopLeft().x = m_crLaunch.TopLeft().x;
		m_crMyVideo.BottomRight().x = m_crLaunch.BottomRight().x;

		pDC->SelectObject(&BrushLine);
		if (m_bMyVidShow)
			pDC->SelectObject(&HighLine);
		pDC->PatBlt(m_crMyVideo.TopLeft().x, m_crMyVideo.TopLeft().y, m_crMyVideo.Width(), m_crMyVideo.Height(), PATCOPY);

		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&font); //选上新的字体
		pDC->SetTextColor(RGB(255, 255, 255));	//修改颜色
		pDC->SetBkColor(TRANSPARENT);
		CString m_strButtle = "退 出";
		pDC->DrawText(m_strButtle, &m_crCan, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "发 布 视 频";
		pDC->DrawText(m_strButtle, &m_crLaunch, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_strButtle = "我 的 视 频";
		pDC->DrawText(m_strButtle, &m_crMyVideo, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SetBkMode(nOldMode);
	}
}

//重写虚函数PreTranslateMessage() 用于回车键确认
BOOL CUserDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_USER_SEARCH)//按下回车，如果当前焦点是在自己期望的控件上
		{
			UpdateData(true);
			if (m_Search) {
				delete[]m_Search;
				m_Search = nullptr;
			}
			m_Search = new CSearchDlg(this);
			m_Search->m_OnlineUserList = m_OnlineUserList;
			m_Search->m_serach = m_search_str;
			m_Search->Create(IDD_SEARCH_DLG, this);
			m_Search->ShowWindow(SW_SHOW);
		}
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
