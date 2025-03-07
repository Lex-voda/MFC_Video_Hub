// CUpdateDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Video_Hub_App.h"
#include "CUserDlg.h"
#include "CLaunchDlg.h"


// CUpdateDlg 对话框

CLaunchDlg::CLaunchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LAUNCH_DLG, pParent)
	, m_Edit_VideoName(_T(""))
	, m_Edit_VideoSize(_T(""))
	, m_Edit_VideoTime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsClose = FALSE;
}

void CLaunchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LAUNCH_NAME, m_Edit_VideoName);
	DDX_Text(pDX, IDC_LAUNCH_SIZE, m_Edit_VideoSize);
	DDX_Text(pDX, IDC_LAUNCH_TIME, m_Edit_VideoTime);
}


BEGIN_MESSAGE_MAP(CLaunchDlg, CDialogEx)
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

BOOL CLaunchDlg_LoadImageResource(CImage* pImage, UINT nResID, LPCTSTR lpTyp)
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
BOOL CLaunchDlg::OnInitDialog()
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
void CLaunchDlg::OnPaint()
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
HCURSOR CLaunchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*************************************************************** 对 话 框 背 景 *************************************************************/

HBRUSH CLaunchDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_LAUNCH_NAME) {
		pDC->SetTextColor(RGB(194, 89, 136));
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SelectObject(&font); //选上新的字体 
	}
	if (pWnd->GetDlgCtrlID() == IDC_LAUNCH_SIZE) {
		pDC->SetTextColor(RGB(194, 89, 136));
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SelectObject(&font); //选上新的字体 
	}
	if (pWnd->GetDlgCtrlID() == IDC_LAUNCH_TIME) {
		pDC->SetTextColor(RGB(194, 89, 136));
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SelectObject(&font); //选上新的字体 
	}
	return m_Brush;
}
BOOL CLaunchDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	HCURSOR hcur = ::LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	::SetCursor(hcur);
	return TRUE;
}

//系统消息响应调用重绘函数
LRESULT CLaunchDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
			DrawUpdateMenu(pWinDC);
			DrawButtle(pWinDC);
		}
		ReleaseDC(pWinDC);
	}
	return lrst;
}
void CLaunchDlg::OnClose()
{
	m_bIsClose = TRUE;
	CDialogEx::OnClose();
}
//绘制发布界面
void CLaunchDlg::DrawUpdateMenu(CDC* pDC) {
	if (m_hWnd) {
		CBrush BrushLine(RGB(194, 89, 136));	//常规笔刷
		//绘制发布界面栏
		m_crLaunch_Flag.TopLeft().x = temprect.TopLeft().x + 50;
		m_crLaunch_Flag.TopLeft().y = temprect.TopLeft().y + 100;
		m_crLaunch_Flag.BottomRight().x = m_crLaunch_Flag.TopLeft().x + temprect.Width() / 8;
		m_crLaunch_Flag.BottomRight().y = m_crLaunch_Flag.TopLeft().y + 150;
		pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_crLaunch_Flag.TopLeft().x, m_crLaunch_Flag.TopLeft().y, m_crLaunch_Flag.Width(), m_crLaunch_Flag.Height(), PATCOPY);
		m_crLaunch_Flag.DeflateRect(10, 10);
		pDC->SelectObject(&m_Brush);
		pDC->PatBlt(m_crLaunch_Flag.TopLeft().x, m_crLaunch_Flag.TopLeft().y, m_crLaunch_Flag.Width(), m_crLaunch_Flag.Height(), PATCOPY);
		
		m_crLaunch_Table.TopLeft().x = m_crLaunch_Flag.TopLeft().x;
		m_crLaunch_Table.TopLeft().y = m_crLaunch_Flag.BottomRight().y + 150;
		m_crLaunch_Table.BottomRight().x = temprect.BottomRight().x - 150;
		m_crLaunch_Table.BottomRight().y = m_crLaunch_Table.TopLeft().y + temprect.Height() / 5 + 50;
		pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_crLaunch_Table.TopLeft().x, m_crLaunch_Table.TopLeft().y, m_crLaunch_Table.Width(), m_crLaunch_Table.Height(), PATCOPY);
		DeleteObject(BrushLine);
		//输入框位置
		//视频名称
		m_crVideo_Name.TopLeft().x = m_crLaunch_Table.TopLeft().x + 50;
		m_crVideo_Name.TopLeft().y = m_crLaunch_Table.TopLeft().y + 50;
		m_crVideo_Name.BottomRight().x = m_crLaunch_Table.BottomRight().x - 150;
		m_crVideo_Name.BottomRight().y = m_crVideo_Name.TopLeft().y + 50;
		//视频大小
		m_crVideo_Size.TopLeft().x = m_crVideo_Name.TopLeft().x;
		m_crVideo_Size.TopLeft().y = m_crVideo_Name.TopLeft().y + 100;
		m_crVideo_Size.BottomRight().x = m_crVideo_Name.BottomRight().x;
		m_crVideo_Size.BottomRight().y = m_crVideo_Size.TopLeft().y + 50;
		//视频上传时间
		m_crVideo_LaunchTime.TopLeft().x = m_crVideo_Size.TopLeft().x;
		m_crVideo_LaunchTime.TopLeft().y = m_crVideo_Size.TopLeft().y + 100;
		m_crVideo_LaunchTime.BottomRight().x = m_crVideo_Size.BottomRight().x;
		m_crVideo_LaunchTime.BottomRight().y = m_crVideo_LaunchTime.TopLeft().y + 50;

		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&font); //选上新的字体
		pDC->SetTextColor(RGB(194, 89, 136));	//修改颜色
		pDC->SetBkColor(TRANSPARENT);
		CString LaunchMenu = "发布视频";
		pDC->DrawText(LaunchMenu, &m_crLaunch_Flag, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SelectObject(&font); //选上新的字体
		pDC->SetTextColor(RGB(255, 255, 255));	//修改颜色
		LaunchMenu = "视频名称：";
		pDC->DrawText(LaunchMenu, &m_crVideo_Name, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		LaunchMenu = "视频大小：";
		pDC->DrawText(LaunchMenu, &m_crVideo_Size, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		LaunchMenu = "视频上传时间：";
		pDC->DrawText(LaunchMenu, &m_crVideo_LaunchTime, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		
		pDC->SetBkMode(nOldMode);
		//调整编辑框位置
		OffsetRect(&m_crVideo_Name, 250, 0);
		OffsetRect(&m_crVideo_Size, 250, 0);
		OffsetRect(&m_crVideo_LaunchTime, 350, 0);
		CWnd* pWnd;
		pWnd = GetDlgItem(IDC_LAUNCH_NAME);    //获取控件指针
		if (pWnd) {
			pWnd->SetWindowPos(NULL, m_crVideo_Name.TopLeft().x , m_crVideo_Name.TopLeft().y, m_crLaunch_Table.Width()-450, m_crVideo_Name.Height(), SWP_NOZORDER);
			//字体
			pWnd->SetFont(&font);
		}
		pWnd = GetDlgItem(IDC_LAUNCH_SIZE);    //获取控件指针
		if (pWnd) {
			pWnd->SetWindowPos(NULL, m_crVideo_Size.TopLeft().x , m_crVideo_Size.TopLeft().y, m_crLaunch_Table.Width() - 450, m_crVideo_Size.Height(), SWP_NOZORDER);
			//字体
			pWnd->SetFont(&font);
		}
		pWnd = GetDlgItem(IDC_LAUNCH_TIME);    //获取控件指针
		if (pWnd) {
			pWnd->SetWindowPos(NULL, m_crVideo_LaunchTime.TopLeft().x, m_crVideo_LaunchTime.TopLeft().y, m_crLaunch_Table.Width() - 550, m_crVideo_LaunchTime.Height(), SWP_NOZORDER);
			//字体
			pWnd->SetFont(&font);
		}

	}
}
//绘制按钮
void CLaunchDlg::DrawButtle(CDC* pDC) {
	if (m_hWnd) {
		CBrush BrushLine(RGB(194, 89, 136));	//常规笔刷
		CBrush HighLine(RGB(134, 52, 53));		//高亮笔刷

		m_crLaunchButton.TopLeft().x = m_crLaunch_Table.TopLeft().x;
		m_crLaunchButton.TopLeft().y = m_crLaunch_Table.BottomRight().y + 150;
		m_crLaunchButton.BottomRight().x = m_crLaunch_Table.Width() / 4;
		m_crLaunchButton.BottomRight().y = m_crLaunchButton.TopLeft().y + 70;

		m_crCancelButon = m_crLaunchButton;
		OffsetRect(&m_crCancelButon, m_crLaunchButton.Width()*1.5, 0);

		if(m_bLauShow)
			pDC->SelectObject(&HighLine);
		else
			pDC->SelectObject(&BrushLine);
		pDC->PatBlt(m_crLaunchButton.TopLeft().x, m_crLaunchButton.TopLeft().y, m_crLaunchButton.Width(), m_crLaunchButton.Height(), PATCOPY);
		if(m_bCanShow)
			pDC->SelectObject(&HighLine);
		else
		pDC->SelectObject(&BrushLine);
	pDC->PatBlt(m_crCancelButon.TopLeft().x, m_crCancelButon.TopLeft().y, m_crCancelButon.Width(), m_crCancelButon.Height(), PATCOPY);

		DeleteObject(BrushLine);
		DeleteObject(HighLine);
		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&font); //选上新的字体
		pDC->SetTextColor(RGB(255, 255, 255));	//修改颜色
		pDC->SetBkColor(TRANSPARENT);
		CString mButtom = "发 布";
		pDC->DrawText(mButtom, &m_crLaunchButton, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		mButtom = "退 出";
		pDC->DrawText(mButtom, &m_crCancelButon, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SetBkMode(nOldMode);
	}
}
//响应鼠标按下
void CLaunchDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_crLaunchButton.PtInRect(point)) {
		UpdateData(TRUE);
		if (m_OnlineUserList.online != Iterator<User>()) {
			string videoname = m_Edit_VideoName.GetBuffer(0);
			string videosize = m_Edit_VideoSize.GetBuffer(0);
			string videotime = m_Edit_VideoTime.GetBuffer(0);
			m_OnlineUserList.online->uploadVideo(videoname, videosize, videotime, 1);
			m_OnlineUserList.save();
			CUserDlg* pParent = (CUserDlg*)GetParent();	//父窗口指针
			pParent->m_OnlineUserList = m_OnlineUserList;
			MessageBox("发布成功！可以退出");
		}
	}
	else if (m_crCancelButon.PtInRect(point)) {
		SendMessage(WM_CLOSE);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

//响应鼠标瞄准
void CLaunchDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_crLaunchButton.PtInRect(point))
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
	if (m_crCancelButon.PtInRect(point))
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
}

BOOL CLaunchDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_LAUNCH_NAME)//按下回车，如果当前焦点是在视频名字框
		{
			UpdateData(true);
			GetDlgItem(IDC_LAUNCH_SIZE)->SetFocus();
			return TRUE;
		}
		if (GetFocus()->GetDlgCtrlID() == IDC_LAUNCH_SIZE)//按下回车，如果当前焦点是在视频尺寸框
		{
			UpdateData(true);
			GetDlgItem(IDC_LAUNCH_TIME)->SetFocus();
			return TRUE;
		}
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
